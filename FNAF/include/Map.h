#ifndef MAP_H
#define MAP_H

#include "CamNumber.h"

// All of the variables represent locations.
// Their values are the camera where they can be seen.
namespace Map
{
	const CamNumber showStage{ 1 };
	const CamNumber pirateCove{ 2 };
	const CamNumber arcade{ 3 };
	const CamNumber cafeteria{ 4 };
	const CamNumber restrooms{ 5 };

	const CamNumber leftHallStart{ 6 };
	const CamNumber leftHallMiddle{ 7 };
	const CamNumber leftHallEnd{ 8 }; // Left door position
	
	const CamNumber rightHallStart{ 9 };
	const CamNumber rightHallMiddle{ 10 };
	const CamNumber rightHallEnd{ 11 }; // Right door position

	inline void display()
	{
		// The map looks fine when viewed in Notepad and in the text game
		// But it looks terrible when viewed in Visual Studio
		TextFiles::displayTextFromFile("map.txt");
	}
}

#endif
