#pragma once

#include <JuceHeader.h>

struct Config
{
    struct Gui
    {
        struct Keyboard
        {
            static const int height;
            static const int pad;
        };

        struct Window
        {
            static const int width;
            static const int height;
        };
    };

    struct Application
    {
        static const String name;
        static const String version;
        static const int    inputChannelsNum;
        static const int    outputChannelsNum;
    };
};
