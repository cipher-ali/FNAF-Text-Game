#include "Animatronic.h"

using Name = Animatronic::Name;
using namespace Animatronics;

Animatronic Animatronics::freddy{ Name::freddy, 5 };
Animatronic Animatronics::bonnie{ Name::bonnie, 5 };
Animatronic Animatronics::chica{ Name::chica, 5 };
Animatronic Animatronics::foxy{ Name::foxy, 5 };

const int Animatronic::s_aiMaxLevel = 20;

Animatronic::Animatronic(Name name, int aiLevel)
	: m_name{ name }, m_aiLevel{ aiLevel },
	m_attackCountdown{ calculateAttackCountdown(name, aiLevel) },
	m_path{ calculatePathLocations(name), 0 }
{
}

Animatronic::Animatronic(Name name)
	: m_name{ name }, m_aiLevel{ 0 },
	m_attackCountdown{ 0 }, m_path{ calculatePathLocations(name), 0}
{
}

int Animatronic::calculateAttackCountdown(Name animatronicName, int animatronicAILevel)
{
	int countdown{ 0 };

	if (animatronicAILevel != 0)
	{
		switch (animatronicName)
		{
		case Name::freddy:
			countdown = Random::get(6, 8) - static_cast<int>(0.2f * animatronicAILevel);
			break;
		case Name::bonnie:
		case Name::chica:
			countdown = 8 - static_cast<int>(0.3f * animatronicAILevel);
			break;
		case Name::foxy:
			countdown = 0;
			break;
		}
	}		

	return countdown;
}

std::vector<CamNumber> Animatronic::calculatePathLocations(Name animatronicName)
{
	std::vector<CamNumber> pathLocations{};

	switch (animatronicName)
	{
	case Name::freddy:
	{
		CamNumber endLocation{ (Random::get(1, 2) == 1) ? Map::leftHallEnd : Map::rightHallEnd };

		if (endLocation == Map::leftHallEnd)
			pathLocations = { Map::showStage, Map::arcade, Map::leftHallStart, Map::leftHallMiddle, endLocation };
		else if (endLocation == Map::rightHallEnd)
			pathLocations = { Map::showStage, Map::cafeteria, Map::rightHallStart, Map::rightHallMiddle, endLocation };

		break;
	}

	case Name::bonnie:
		pathLocations = { Map::showStage, Map::pirateCove, Map::arcade, Map::leftHallStart, Map::leftHallMiddle, Map::leftHallEnd };
		break;

	case Name::chica:
		pathLocations = { Map::showStage, Map::cafeteria, Map::restrooms, Map::rightHallStart, Map::rightHallMiddle, Map::rightHallEnd };
		break;

	case Name::foxy:
		pathLocations = { Map::pirateCove, Map::arcade, Map::leftHallStart, Map::leftHallMiddle, Map::leftHallEnd };
		break;
	}

	return pathLocations;
}

void AnimFuncs::move(Animatronic& animatronic)
{
	assert(animatronic.getName() != Name::foxy);

	if (AnimFuncs::isAtOfficeDoor(animatronic) && animatronic.getAttackCountdown() > 0)
		return;

	bool didPositionChange{ Random::get(0, 29) < animatronic.getAILevel() };
	if (!didPositionChange) return;

	else if (AnimFuncs::isAtOfficeDoor(animatronic) && animatronic.getAttackCountdown() == 0)
	{
		// Animatronic basically gets reset
		animatronic.resetAttackCountdown();
		animatronic.resetLocation();
		return;
	}

	if (animatronic.getPathIndex() < animatronic.getPath().size() - 1)
		animatronic.moveToNextLocation();
}

void AnimFuncs::moveFoxy(bool wasFoxyCheckedOn)
{
	if (wasFoxyCheckedOn)
	{
		foxy.resetLocation();
		return;
	}

	if (Random::get(0, 29) < foxy.getAILevel() && foxy.getPathIndex() < foxy.getPath().size() - 1)
		foxy.moveToNextLocation();
}

void AnimFuncs::decrementDoorWaitCountdowns()
{
	if (AnimFuncs::isAtOfficeDoor(freddy)) freddy.decrementAttackCountdown();
	if (AnimFuncs::isAtOfficeDoor(bonnie)) bonnie.decrementAttackCountdown();
	if (AnimFuncs::isAtOfficeDoor(chica))  chica.decrementAttackCountdown();
	if (AnimFuncs::isAtOfficeDoor(foxy))   foxy.decrementAttackCountdown();
}

// Animatronic office entry is the same as an animatronic attack, really.
void AnimFuncs::checkForOfficeEntry(const Animatronic& animatronic)
{
	if (animatronic.getName() == Name::foxy && AnimFuncs::isAtOfficeDoor(foxy))
	{
		if (Office::isLeftDoorOpen)
		{
			std::cout << "Foxy dashes into the office, and slashes you with his hook while yelling \"ARRRRGH!\"\n";
			Pause::pauseForMiliseconds(500);
			std::cout << "Large amounts of your blood splatter everywhere.\n";
			Pause::pauseForMiliseconds(500);
		}
		else if (!Office::isLeftDoorOpen)
		{
			std::cout << "Foxy dashes into the left door at full force, and he breaks down the door!\n";
			Pause::pauseForMiliseconds(500);
			std::cout << "Large amounts of your blood splatter everywhere.\n";
			Pause::pauseForMiliseconds(500);
			std::cout << "He enters the office to slash you with his hook while yelling \"ARRRRGH!\"\n";
			Pause::pauseForMiliseconds(500);
		}

		std::cout << "Foxy takes you to stuff you in an animatronic suit.\n";
		Pause::pauseForMiliseconds(500);
		OutputDelay::println("GAME OVER!", 100);
		std::exit(0);
	}

	CamNumber officeDoorPosition{ (animatronic.getEndLocation() == Map::leftHallEnd) ? Map::leftHallEnd : Map::rightHallEnd };
	bool isDoorOpen{ (officeDoorPosition == Map::leftHallEnd) ? Office::isLeftDoorOpen : Office::isRightDoorOpen };

	bool canAnimatronicEnter{ animatronic.getCurrentLocation() == animatronic.getEndLocation() &&
							isDoorOpen && animatronic.getAttackCountdown() == 0 };

	if (canAnimatronicEnter)
	{
		std::cout << getNameAsStringView(animatronic.getName()) << " enters the office, " <<
			"and jumps at you with a shriek!\n";
		Pause::pauseForMiliseconds(500);
		std::cout << getNameAsStringView(animatronic.getName()) << " continuously bites and scratches you violently.\n";
		Pause::pauseForMiliseconds(500);
		std::cout << "Eventually, you get painfully stuffed into an animatronic suit.\n";
		Pause::pauseForMiliseconds(500);
		OutputDelay::println("GAME OVER!", 100);
		std::exit(0);
	}
}

bool AnimFuncs::isAtOfficeDoor(const Animatronic& animatronic)
{
	return (animatronic.getCurrentLocation() == Map::leftHallEnd ||
			animatronic.getCurrentLocation() == Map::rightHallEnd) ? true : false;
}