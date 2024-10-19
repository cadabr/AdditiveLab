#pragma once

#include <JuceHeader.h>

struct Render final : public AudioIODeviceCallback
{
    using InputChannelData  = const float* const*;
    using OutputChannelData = float* const*;
    using ContextDelegate   = const AudioIODeviceCallbackContext &;

    ~Render() override;

    void audioDeviceAboutToStart (AudioIODevice* device) override;

    void audioDeviceIOCallbackWithContext (
        InputChannelData    inputChannelData,
        int                 numInputChannels,
        OutputChannelData   outputChannelData,
        int                 numOutputChannels,
        int                 numSamples,
        ContextDelegate     context ) override;

    void audioDeviceStopped () override;

    void audioDeviceError (const String& errorMessage) override;
};
