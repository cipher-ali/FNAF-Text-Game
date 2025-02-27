#ifndef CAMERAS_H
#define CAMERAS_H

#include "TextFileFunctions.h"
#include "OutputDelay.h"
#include "Pause.h"

#include "Animatronic.h"
#include "CamNumber.h"
#include "Map.h"

using namespace Animatronics;

namespace Cameras
{
	const int totalCameras{ 11 };

	inline void showAnimatronicsAtCamera(CamNumber cameraNumber)
	{
		bool isAnimatronicAtCamera{ false };

		if (freddy.getCurrentLocation() == cameraNumber)
		{
			std::cout << "Freddy is here.\n";
			isAnimatronicAtCamera = true;
		}

		if (bonnie.getCurrentLocation() == cameraNumber)
		{
			std::cout << "Bonnie is here.\n";
			isAnimatronicAtCamera = true;
		}

		if (chica.getCurrentLocation() == cameraNumber)
		{
			std::cout << "Chica is here.\n";
			isAnimatronicAtCamera = true;
		}

		if (foxy.getCurrentLocation() == cameraNumber)
		{
			std::cout << "Foxy is here.\n";
			isAnimatronicAtCamera = true;
		}

		if (!isAnimatronicAtCamera) std::cout << "Nobody is here.\n";
	}

	inline void checkCamera(CamNumber cameraNumber)
	{
		std::cout << "Checking camera #" << cameraNumber;
		Pause::pauseForMiliseconds(200);
		OutputDelay::println("...", 200);

		showAnimatronicsAtCamera(cameraNumber);
	}
}

#endif