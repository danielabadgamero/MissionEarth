#ifndef CONTROL_ROOM_H
#define CONTROL_ROOM_H

#include "Planet.h"

class ControlRoom
{
private:
	Planet* SOI{};
public:
	ControlRoom();
	void draw() const;
};

#endif