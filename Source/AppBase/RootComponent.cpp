#include "AppBase/RootComponent.h"
#include "Core/Config.h"

RootComponent::RootComponent ()
{
    addAndMakeVisible (keyboardComponent);
    setOpaque (true);
    setSize (Config::Gui::Window::width, Config::Gui::Window::height);
}

void RootComponent::paint (Graphics& g)
{
    const auto wndBkg     = LookAndFeel_V4::ColourScheme::UIColour::windowBackground;
    const auto fillColour = LookAndFeel_V4::getDarkColourScheme().getUIColour (wndBkg);

    g.fillAll (fillColour);
}

void RootComponent::resized ()
{
    const int pad    = Config::Gui::Keyboard::pad;
    const int height = Config::Gui::Keyboard::height;

    const int width  = getWidth() - 2 * pad;
    const int x      = pad;
    const int y      = getHeight() - height - pad;

    keyboardComponent.setBounds (x, y, width, height);
}
