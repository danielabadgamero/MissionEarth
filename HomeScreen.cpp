#include "Core.h"
#include "HomeScreen.h"
#include "Label.h"

void HomeScreen::draw() const
{
	Label::setFont("C:\\Windows\\Fonts\\AGENCYR.TTF", 32);
	Label::draw("Hello, world!", { Core::monitor.w / 2, Core::monitor.h / 2 }, { 0xff, 0xff, 0xff }, { 0.5, 0.5 });
}