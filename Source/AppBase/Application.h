#pragma once

#include <JuceHeader.h>

#include "AppBase/MainWindow.h"

class Application final : public JUCEApplication
{
public:
    Application () = default;

    const String getApplicationName () override;

    const String getApplicationVersion () override;

    void initialise (const String&) override;

    void shutdown () override;

private:
    using MainWindowPtr = std::unique_ptr<MainWindow>;
    MainWindowPtr mainWindow;
};
