#include "SawVoice.h"
#include "Synth/PolyphonicSound.h"

namespace
{
    constexpr float epsilon = 1e-6f;
}

bool SawVoice::canPlaySound (SynthesiserSound* sound)
{
    return dynamic_cast<PolyphonicSound*> (sound) != nullptr;
}

void SawVoice::startNote (int midiNoteNumber, float velocity, SynthesiserSound*, int /*currentPitchWheelPosition*/)
{
    currentAngle = 0.0;
    angleDelta = MathConstants<double>::twoPi * MidiMessage::getMidiNoteInHertz(midiNoteNumber) / getSampleRate();
    level = velocity * 0.15;
    tailOff = 0.0;

    fundamentalFrequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);

    generateHarmonics(fundamentalFrequency);
}

void SawVoice::stopNote (float /*velocity*/, bool allowTailOff)
{
    if (allowTailOff)
    {
        if (std::abs(tailOff) < epsilon)
            tailOff = 1.0;
    }
    else
    {
        clearCurrentNote();
        angleDelta = 0.0;
    }
}

void SawVoice::pitchWheelMoved (int /*newValue*/)
{

}

void SawVoice::controllerMoved (int /*controllerNumber*/, int /*newValue*/)
{

}

void SawVoice::renderNextBlock (AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    if (std::abs(angleDelta) >= epsilon)
    {
        if (tailOff > 0.0)
        {
            while (--numSamples >= 0)
            {
                const float currentSample = (float) (level * tailOff * std::sin (currentAngle));
                for (int i = outputBuffer.getNumChannels(); --i >= 0;)
                    outputBuffer.addSample (i, startSample, currentSample);

                currentAngle += angleDelta;
                ++startSample;

                tailOff *= 0.99;
                if (tailOff <= 0.005)
                {
                    clearCurrentNote();
                    angleDelta = 0.0;
                    break;
                }
            }
        }
        else
        {
            fillBufferWithSawWave(outputBuffer, startSample, numSamples);
        }
    }
}

void SawVoice::generateHarmonics(double frequency)
{
    //const int sampleRate = getSampleRate();
    const size_t maxHarmonics = 20000 / frequency;
    harmonics.clear();
    harmonics.resize(maxHarmonics);

    for (size_t n = 1; n <= maxHarmonics; ++n)
    {
        float amplitude = 1.0f / n;
        harmonics[n-1] = amplitude;
    }
}

void SawVoice::fillBufferWithSawWave(AudioBuffer<float>& buffer, int startSample, int numSamples)
{
    const int fftSize = 1024;

    std::vector<float> freqs(2 * fftSize, 0.0f);

    for (size_t i = 0; i < fftSize; ++i)
    {
        freqs[2*i] = harmonics[i];
    }

    fft.performRealOnlyInverseTransform(freqs.data());

    for (int sample = 0; sample < numSamples; ++sample)
    {
        float currentSample = freqs[(unsigned)sample] * level;
        for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
        {
            buffer.addSample(channel, startSample + sample, currentSample);
        }
    }
}

void SawVoice::renderNextBlock (AudioBuffer<double>&, int, int)
{
    jassertfalse;
}
