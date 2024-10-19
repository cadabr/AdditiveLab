#pragma once

#include <JuceHeader.h>

#include "Gui/HorizontalKeyboard.h"

//==============================================================================
class RootComponent final : public Component
{
public:
    RootComponent ();

    void paint (Graphics& g) override;

    void resized () override;

private:
    HorizontalKeyboard keyboardComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RootComponent)
};
