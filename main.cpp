#include "Core.h"

int main(int, char**)
{
	Core::init("");

	while (Core::running)
	{
		Core::event();
		Core::draw();
	}

	Core::quit();

	return 0;
}