#ifndef OFFICE_H
#define OFFICE_H

#include <iostream>

#include "TextFileFunctions.h"

#include "Animatronic.h"
#include "Map.h"

namespace Office
{
	extern int battery; // as a percentage

	extern bool isLeftDoorOpen;
	extern bool isRightDoorOpen;

	extern bool isLeftLightOn;
	extern bool isRightLightOn;
	
	void changeDoorStatus(int doorPosition);
	void changeLightStatus(int lightPosition);
	void drainBattery();
	void checkDoorsForAnimatronics();
};

#endif