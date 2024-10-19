#pragma once

#include <JuceHeader.h>

#include "AppBase/Application.h"
#include "System/Render.h"

class theLab
{
public:
    theLab (const theLab&) = delete;

    theLab& operator = (const theLab&) = delete;

    ~theLab();

    static theLab& instance();

public:
    AudioDeviceManager     audioDeviceManager;
    MidiKeyboardState      keyboard;
    MidiMessageCollector   midiCollector;
    Synthesiser            synth;
    Render                 render;

private:
    friend class Application;

    theLab();

    static std::unique_ptr<theLab> singleton;
};

