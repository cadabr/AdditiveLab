#include "Gui/HorizontalKeyboard.h"
#include "System/theLab.h"

HorizontalKeyboard::HorizontalKeyboard ()
: MidiKeyboardComponent (theLab::instance().keyboard, Orientation::horizontalKeyboard)
{
}
