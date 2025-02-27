#ifndef NIGHT_H
#define NIGHT_H

#include <iostream>
#include <iomanip>
#include <string>

#include "InputValue.h"
#include "DisplayLine.h"
#include "OutputDelay.h"
#include "Pause.h"

#include "Animatronic.h"
#include "Office.h"
#include "GameTime.h"
#include "Cameras.h"
#include "CamNumber.h"
#include "Map.h"

namespace Night
{
	void start();

	void setup();
	void setAnimatronicAILevels();
	void displayStats();
	void displaySpookyMessage();
	void updateState(bool wasFoxyCheckedOn);
};

#endif