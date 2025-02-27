#ifndef ANIMATRONIC_H
#define ANIMATRONIC_H

#include <string>
#include <vector>
#include <cmath>
#include <cassert>

#include "Random.h"
#include "Pause.h"
#include "OutputDelay.h"

#include "Office.h"
#include "Map.h"
#include "CamNumber.h"

/*
* 'getCurrentLocation()' and 'getPathIndex()' may seem to do the same thing, but that's not really true.
* 'getCurrentLocation()' returns what camera number the animatronic is currently located at 
* 'getPathIndex()' returns the current index for the animatronic's path locations
*/
class Animatronic
{
public:
	enum class Name
	{
		freddy,
		bonnie,
		chica,
		foxy,
	};

private:
	Name m_name{};
	int m_aiLevel{};
	int m_attackCountdown{}; // How long an animatronic will stay at an office door before attempting to enter. Decrements after each user action.

	struct Path
	{
		std::vector<CamNumber> locations{};
		int pathIndex{}; // Tracks current location in the path
	};
	Path m_path{};

	static int calculateAttackCountdown(Name animatronicName, int animatronicAILevel);
	static std::vector<CamNumber> calculatePathLocations(Name animatronicName);

public:
	static const int s_aiMaxLevel;

	Animatronic(Name name, int aiLevel);

	Animatronic(Name name);

	Name getName() const { return m_name; }
	int getAILevel() const { return m_aiLevel; }
	int getAttackCountdown() const { return m_attackCountdown; }
	auto getPath() const { return m_path.locations; }

	CamNumber getStartLocation() const { return m_path.locations[0]; }
	CamNumber getCurrentLocation() const { return m_path.locations[m_path.pathIndex]; }
	CamNumber getEndLocation() const { return m_path.locations[m_path.locations.size() - 1]; }
	int getPathIndex() const { return m_path.pathIndex; }

	void setAILevel(int aiLevel) { m_aiLevel = aiLevel; resetAttackCountdown(); }
	void setPathIndex(int pathIndex) { m_path.pathIndex = pathIndex; }

	void resetLocation() { m_path.pathIndex = 0; }
	void resetAttackCountdown() { m_attackCountdown = calculateAttackCountdown(m_name, m_aiLevel); }
	void decrementAttackCountdown() { --m_attackCountdown; }
	void moveToNextLocation() { ++m_path.pathIndex; }
};

namespace Animatronics
{
	extern Animatronic freddy, bonnie, chica, foxy;
}

// Anim is short for Animatronic
namespace AnimFuncs
{
	void move(Animatronic& animatronic);
	void moveFoxy(bool wasFoxyCheckedOn); // Foxy has unique mechanics, so he has his own function for changing his position! :D
	void decrementDoorWaitCountdowns();
	void checkForOfficeEntry(const Animatronic& animatronic);
	bool isAtOfficeDoor(const Animatronic& animatronic);

	constexpr std::string_view getNameAsStringView(const Animatronic::Name animatronicName)
	{
		switch (animatronicName)
		{
		case Animatronic::Name::freddy: return "Freddy";
		case Animatronic::Name::bonnie: return "Bonnie";
		case Animatronic::Name::chica:  return "Chica";
		case Animatronic::Name::foxy:   return "Foxy";
		default: return "animatronicName IS NOT A VALID ENUM\n";
		}
	}
}

#endif