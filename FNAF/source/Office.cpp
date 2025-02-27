#include "Office.h"

using namespace Animatronics;

namespace Office
{
	int battery{ 100 }; // as a percentage

	bool isLeftDoorOpen{ true };
	bool isRightDoorOpen{ true };

	bool isLeftLightOn{ false };
	bool isRightLightOn{ false };
}

void Office::changeDoorStatus(int doorPosition)
{
	if (doorPosition == Map::leftHallEnd)
	{
		switch (isLeftDoorOpen)
		{
		case true:
			isLeftDoorOpen = false;
			std::cout << "The left door was closed.\n";
			return;
		case false:
			isLeftDoorOpen = true;
			std::cout << "The left door was opened.\n";
			return;
		}
	}
	else if (doorPosition  == Map::rightHallEnd)
	{
		switch (isRightDoorOpen)
		{
		case true:
			isRightDoorOpen = false;
			std::cout << "The right door was closed.\n";
			return;
		case false:
			isRightDoorOpen = true;
			std::cout << "The right door was opened.\n";
		}
	}
}

void Office::changeLightStatus(int lightPosition)
{
	if (lightPosition == Map::leftHallEnd)
	{
		switch (isLeftLightOn)
		{
		case true:
			isLeftLightOn = false;
			std::cout << "The left light was turned off.\n";
			return;
		case false:
			isLeftLightOn = true;
			std::cout << "The left light was turned on.\n";
			return;
		}
	}
	else if (lightPosition == Map::rightHallEnd)
	{
		switch (isRightLightOn)
		{
		case true:
			isRightLightOn = false;
			std::cout << "The right light was turned off.\n";
			return;
		case false:
			isRightDoorOpen = true;
			std::cout << "The right light was turned on.\n";
		}
	}
}

void Office::drainBattery()
{
	if (!isLeftDoorOpen) battery -= 4;
	if (!isRightDoorOpen) battery -= 4;
	if (isLeftLightOn) battery -= 3;
	if (isRightLightOn) battery -= 3;

	if (battery < 0) battery = 0;
}

void Office::checkDoorsForAnimatronics()
{
	if (isLeftLightOn)
	{
		bool isFreddyWaitingAtDoor{ freddy.getCurrentLocation() == Map::leftHallEnd && freddy.getAttackCountdown() > 0};
		bool isFreddyLeavingDoor{ freddy.getCurrentLocation() == Map::leftHallEnd && freddy.getAttackCountdown() == 0 && !isLeftDoorOpen };
		if (isFreddyWaitingAtDoor)
		{
			std::cout << "Freddy is waiting at the left door!\n";
			std::cout << "Countdown for Freddy's attack attempt: " << freddy.getAttackCountdown() << '\n';
		}
		else if (isFreddyLeavingDoor)
			std::cout << "Freddy is leaving from the left door!\n";
		std::cout << '\n';


		bool isBonnieWaitingAtDoor{ bonnie.getCurrentLocation() == Map::leftHallEnd && bonnie.getAttackCountdown() > 0 };
		bool isBonnieLeavingDoor{ bonnie.getCurrentLocation() == Map::leftHallEnd && bonnie.getAttackCountdown() == 0 && !isLeftDoorOpen };
		if (isBonnieWaitingAtDoor)
		{
			std::cout << "Bonnie is waiting at the left door!\n";
			std::cout << "Countdown for Bonnies's attack attempt: " << bonnie.getAttackCountdown() << '\n';
		}
		else if (isBonnieLeavingDoor)
			std::cout << "Bonnie is leaving from the left door!\n";
		std::cout << '\n';

		// Chica does not go to the left door.
		// Foxy does go to the left door, but he enters instantly.
	}
	if (isRightLightOn)
	{
		bool isFreddyWaitingAtDoor{ freddy.getCurrentLocation() == Map::rightHallEnd && freddy.getAttackCountdown() > 0};
		bool isFreddyLeavingDoor{ freddy.getCurrentLocation() == Map::rightHallEnd && freddy.getAttackCountdown() == 0 && !isRightDoorOpen };
		if (isFreddyWaitingAtDoor)
		{
			std::cout << "Freddy is waiting at the right door!\n";
			std::cout << "Countdown for Freddy's attack attempt: " << freddy.getAttackCountdown() << '\n';
		}
		else if (isFreddyLeavingDoor)
			std::cout << "Freddy is leaving from the right door!\n";
		std::cout << '\n';


		bool isChicaWaitingAtDoor{ chica.getCurrentLocation() == Map::rightHallEnd && chica.getAttackCountdown() > 0 };
		bool isChicaLeavingDoor{ chica.getCurrentLocation() == Map::rightHallEnd && chica.getAttackCountdown() == 0 && !isRightDoorOpen };
		if (isChicaWaitingAtDoor)
		{
			std::cout << "Chica is waiting at the right door!\n";
			std::cout << "Countdown for Chica's attack attempt: " << chica.getAttackCountdown() << '\n';
		}
		else if (isChicaLeavingDoor)
			std::cout << "Chica is leaving the from right door!\n";
		std::cout << '\n';

		// Bonnie does not go to right door.
		std::cout << '\n';
	}
}