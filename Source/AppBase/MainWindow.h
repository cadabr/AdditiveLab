#pragma once

#include <JuceHeader.h>

class MainWindow final : public DocumentWindow
{
public:
    using EventHandler = std::function<void()>;

    MainWindow (const String& name, const EventHandler& closeAppCallback);

    void closeButtonPressed () override;

private:
    EventHandler onCloseButtonPressed;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
};
