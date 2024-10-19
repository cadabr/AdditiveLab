#include <JuceHeader.h>

#include "AppBase/Application.h"
#include "Core/Config.h"
#include "System/theLab.h"

const String Application::getApplicationName ()
{
    return Config::Application::name;
}

const String Application::getApplicationVersion ()
{
    return Config::Application::version;
}

void Application::initialise (const String&)
{
    theLab::singleton.reset (new theLab);

    auto systemQuitRequest = [this] () { this->systemRequestedQuit(); };
    const String title     = Config::Application::name;

    mainWindow.reset (new MainWindow (title, systemQuitRequest));
}

void Application::shutdown ()
{
    mainWindow        = nullptr;
    theLab::singleton = nullptr;
}

START_JUCE_APPLICATION (Application)
