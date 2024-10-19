#include "AppBase/MainWindow.h"
#include "AppBase/RootComponent.h"
#include "Gui/Utils.h"

MainWindow::MainWindow (const String& name, const EventHandler& closeAppCallback)
: DocumentWindow (name, backgroundColour(), DocumentWindow::allButtons)
, onCloseButtonPressed (closeAppCallback)
{
    setUsingNativeTitleBar (true);
    setContentOwned (new RootComponent, true);
    setResizable (false, false);
    centreWithSize (getWidth(), getHeight());
    setVisible (true);
}

void MainWindow::closeButtonPressed()
{
    onCloseButtonPressed ();
}
