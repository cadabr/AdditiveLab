#include "Core/Config.h"
#include "System/theLab.h"
#include "Synth/PolyphonicSound.h"
#include "Synth/SawVoice.h"
#include "Synth/SineVoice.h"

std::unique_ptr<theLab> theLab::singleton = nullptr;

theLab::theLab()
{
    jassert(!singleton);

    audioDeviceManager.initialise (
        Config::Application::inputChannelsNum,
        Config::Application::outputChannelsNum,
        nullptr, true, {}, nullptr );

    auto sampleRate = audioDeviceManager.getCurrentAudioDevice()->getCurrentSampleRate();
    synth.setCurrentPlaybackSampleRate (sampleRate);
    synth.addSound (new PolyphonicSound());
    synth.addVoice (new SineVoice());
    audioDeviceManager.addAudioCallback (&render);
    midiCollector.reset (sampleRate);
    audioDeviceManager.addMidiInputDeviceCallback ({}, &midiCollector);
}

theLab::~theLab()
{
    audioDeviceManager.removeMidiInputDeviceCallback ({}, &midiCollector);
    audioDeviceManager.removeAudioCallback (&render);
}

theLab& theLab::instance()
{
    jassert(singleton);
    return *singleton.get();
}
