#pragma once

#include <JuceHeader.h>

class SawVoice : public SynthesiserVoice
{
public:
    SawVoice() = default;

    bool canPlaySound (SynthesiserSound* sound) override;

    void startNote (int midiNoteNumber, float velocity, SynthesiserSound*, int /*currentPitchWheelPosition*/) override;

    void stopNote (float /*velocity*/, bool allowTailOff) override;

    void pitchWheelMoved (int /*newValue*/) override;

    void controllerMoved (int /*controllerNumber*/, int /*newValue*/) override;

    void renderNextBlock (AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

    void renderNextBlock (AudioBuffer<double>&, int, int) override;

private:
    void generateHarmonics(double frequency);

    void fillBufferWithSawWave(AudioBuffer<float>& buffer, int startSample, int numSamples);

    double currentAngle = 0.0, angleDelta = 0.0, level = 0.0, tailOff = 0.0;
    double fundamentalFrequency = 440.0;
    std::vector<float> harmonics;
    dsp::FFT fft { 10 };
};
