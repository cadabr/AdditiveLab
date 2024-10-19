#include "Synth/SineVoice.h"
#include "Synth/PolyphonicSound.h"

bool SineVoice::canPlaySound (SynthesiserSound* sound)
{
    return dynamic_cast<PolyphonicSound*> (sound) != nullptr;
}

void SineVoice::startNote (int midiNoteNumber, float velocity, SynthesiserSound*, int /*currentPitchWheelPosition*/)
{
    currentAngle = 0.0;
    level = velocity * 0.15;
    tailOff = 0.0;

    auto cyclesPerSecond = MidiMessage::getMidiNoteInHertz (midiNoteNumber);
    auto cyclesPerSample = cyclesPerSecond / getSampleRate();

    angleDelta = cyclesPerSample * MathConstants<double>::twoPi;
}

void SineVoice::stopNote (float /*velocity*/, bool allowTailOff)
{
    if (allowTailOff)
    {
        if (approximatelyEqual (tailOff, 0.0))
            tailOff = 1.0;
    }
    else
    {
        clearCurrentNote ();
        angleDelta = 0.0;
    }
}

void SineVoice::pitchWheelMoved (int /*newValue*/)
{
}

void SineVoice::controllerMoved (int /*controllerNumber*/, int /*newValue*/)
{
}

void SineVoice::renderNextBlock (AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    if (! approximatelyEqual (angleDelta, 0.0))
    {
        if (tailOff > 0.0)
        {
            while (--numSamples >= 0)
            {
                auto currentSample = (float) (std::sin (currentAngle) * level * tailOff);

                for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
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
            while (--numSamples >= 0)
            {
                auto currentSample = (float) (std::sin (currentAngle) * level);

                for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                    outputBuffer.addSample (i, startSample, currentSample);

                currentAngle += angleDelta;
                ++startSample;
            }
        }
    }
}

void SineVoice::renderNextBlock (AudioBuffer<double>&, int, int)
{
    jassertfalse;
}
