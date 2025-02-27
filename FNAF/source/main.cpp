// ***"user action" refers to when the user checks the cameras, opens/closes doors, turns on/off lights within the game, or just does nothing

#include <iostream>

#include "Random.h"
#include "TextFileFunctions.h"
#include "DisplayLine.h"
#include "OutputDelay.h"
#include "Pause.h"
#include "InputValue.h"

#include "Animatronic.h"
#include "Office.h"
#include "Night.h"
#include "GameTime.h"

int main()
{
	OutputDelay::println("Welcome to Freddy Fazbear's Pizzeria!");
	Pause::pauseForMiliseconds(250);
	OutputDelay::println("You will be working as a night guard.");
	Pause::pauseForMiliseconds(250);
	OutputDelay::print("Make sure the animatronics don't get too quirky");
	Pause::pauseForMiliseconds(200);
	OutputDelay::println("...", 200);
	Line::display();

	Night::start();

	return 0;
}