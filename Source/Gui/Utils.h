#pragma once

#include <JuceHeader.h>

const auto backgroundColour = [] ()
{
    return juce::Desktop::getInstance().getDefaultLookAndFeel().findColour (ResizableWindow::backgroundColourId);
};
