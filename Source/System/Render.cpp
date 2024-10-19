#include "System/Render.h"
#include "System/theLab.h"

Render::~Render ()
{

}

void Render::audioDeviceAboutToStart ([[maybe_unused]] AudioIODevice* device)
{

}

void Render::audioDeviceIOCallbackWithContext (
    [[maybe_unused]] InputChannelData    inputChannelData,
    [[maybe_unused]] int                 numInputChannels,
                     OutputChannelData   outputChannelData,
                     int                 numOutputChannels,
                     int                 numSamples,
    [[maybe_unused]] ContextDelegate     context )
{
    MidiBuffer incomingMidi;
    theLab::instance().midiCollector.removeNextBlockOfMessages (incomingMidi, numSamples);
    theLab::instance().keyboard.processNextMidiBuffer (incomingMidi, 0, numSamples, true);

    for (int i = 0; i < numOutputChannels; ++i)
    {
        zeromem (outputChannelData[i], (size_t) numSamples * sizeof (float));
    }

    AudioBuffer<float> buffer (outputChannelData, numOutputChannels, numSamples);
    theLab::instance().synth.renderNextBlock (buffer, incomingMidi, 0, numSamples);
}

void Render::audioDeviceStopped()
{

}

void Render::audioDeviceError ([[maybe_unused]] const String& errorMessage)
{
    jassertfalse;
}