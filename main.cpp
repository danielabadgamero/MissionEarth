#include "Core.h"

int main(int, char**)
{
	Core::init("Mission Earth");

	while (Core::running)
	{
		Core::event();
		Core::draw();
	}

	Core::quit();

	return 0;
}