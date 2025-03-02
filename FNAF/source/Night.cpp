#include "Night.h"

using Name = Animatronic::Name;
using namespace Animatronics;
using namespace Cameras;

void Night::start()
{
	Night::setup();

	// Reference to the '1987' secret in the original FNAF game
	if (freddy.getAILevel() == 1 &&
		bonnie.getAILevel() == 9 &&
		chica.getAILevel() == 8 &&
		foxy.getAILevel() == 7)
	{
		for (int i{ 0 }; i < 100000; ++i)
			std::cout << 'A';

		std::exit(0);
	}

	// Now it really begins!

	Line::display();
	OutputDelay::println("The night has begun...");
	Pause::pauseForMiliseconds(500);

	// This is used to prevent the player from abusing the 'Do Nothing' option (with both doors closed)
	// on nights with low animatronic AI levels
	int doNothingAmount{ 0 };
	CamNumber previousCameraChecked{ 0 };

	int iteration{ 1 };
	while (true)
	{
		bool didPlayerAct{ false };
		bool wasFoxyCheckedOn{ false };

		std::cout << std::string(50, '\n');

		if (GameTime::is6AM())
		{
			OutputDelay::println("You have made it to 6 AM! Your shift is over!");
			Pause::pauseForSeconds(1);
			OutputDelay::println("The animatronics have stopped moving, but you make your way to the exit cautiously anyway.");
			Pause::pauseForSeconds(1);
			OutputDelay::println("You decide to quit working here and search for another job.");
			Pause::pauseForSeconds(1);
			OutputDelay::println("YAAAY!", 100);
			std::exit(0);
		}

		Office::checkDoorsForAnimatronics();
		Night::displayStats();

		std::cout << "\n======OPTIONS======\n";
		std::cout << "1) Check Cameras\n";
		std::cout << "2) Open/Close Doors\n";
		std::cout << "3) Turn On/Off Lights\n";
		std::cout << "4) Do Nothing\n";
		std::cout << "Choose an option: ";
		int optionNumber{ Input::getValidatedIntInputInRange(1, 4) };
		std::cout << '\n';
		switch (optionNumber)
		{
		case 1: // Cameras
		{
			std::cout << '\n';

			if (previousCameraChecked != 0)
			{
				std::cout << "Camera #" << previousCameraChecked << " was checked previously, " <<
					"so it will be checked again first.\n";

				Pause::pauseForMiliseconds(750);
				Cameras::checkCamera(previousCameraChecked);
				Pause::pauseForMiliseconds(1500);
				std::cout << '\n';
			}

			Map::display();
			std::cout << '\n';
			std::cout << "Select a camera to check (0 to cancel): ";
			CamNumber cameraNumber{ Input::getValidatedIntInputInRange(0, Cameras::totalCameras) };

			if (cameraNumber == 0) break; // Don't count as a turn

			Cameras::checkCamera(cameraNumber);
			Pause::pauseForSeconds(2);
			if (cameraNumber == foxy.getCurrentLocation())
			{

				wasFoxyCheckedOn = true;

				if (foxy.getCurrentLocation() != Map::pirateCove)
				{
					std::cout << "Foxy has returned to his cove!\n";
					Pause::pauseForMiliseconds(850);
				}
			}

			didPlayerAct = true;
			previousCameraChecked = cameraNumber;
			break;
		}
		case 2: // Doors
		{
			std::cout << std::boolalpha;
			std::cout << "Left door is ";
			std::cout << (Office::isLeftDoorOpen ? "open." : "closed.");
			std::cout << '\n';

			std::cout << "Right door is ";
			std::cout << (Office::isRightDoorOpen ? "open." : "closed.");
			std::cout << '\n';

			std::cout << '\n';

			std::cout << "1) Open/Close Left Door\n";
			std::cout << "2) Open/Close Right Door\n";
			std::cout << "3) Open Both Doors\n";
			std::cout << "4) Close Both Doors\n";
			std::cout << "5) Cancel\n";

			std::cout << "Choose an option: ";
			int choice{ Input::getValidatedIntInputInRange(1, 5) };
			if (choice == 5) break; // Don't count as a turn
			switch (choice)
			{
			case 1:
				Office::changeDoorStatus(Map::leftHallEnd);
				break;
			case 2:
				Office::changeDoorStatus(Map::rightHallEnd);
				break;
			case 3:
				Office::isLeftDoorOpen = Office::isRightDoorOpen = true;
				std::cout << "Both doors were opened.\n";
				break;
			case 4:
				Office::isLeftDoorOpen = Office::isRightDoorOpen = false;
				std::cout << "Both doors were closed.\n";
				break;
			}
			std::cout << std::noboolalpha;
			Pause::pauseForMiliseconds(1500);
			didPlayerAct = true;
			break;
		}
		case 3: // Lights
		{
			std::cout << std::boolalpha;
			std::cout << "Left light is ";
			std::cout << (Office::isLeftLightOn ? "on." : "off.");
			std::cout << '\n';

			std::cout << "Right light is ";
			std::cout << (Office::isRightLightOn ? "on." : "off.");
			std::cout << '\n';

			std::cout << '\n';

			std::cout << "1) Turn On/Off Left Light\n";
			std::cout << "2) Turn On/Off Right Light\n";
			std::cout << "3) Turn On Both Lights\n";
			std::cout << "4) Turn Off Both Lights\n";
			std::cout << "5) Cancel\n";

			std::cout << "Choose an option: ";
			int choice{ Input::getValidatedIntInputInRange(1, 5) };
			if (choice == 5) break; // Don't count as a turn
			switch (choice)
			{
			case 1:
				Office::changeLightStatus(Map::leftHallEnd);
				break;
			case 2:
				Office::changeLightStatus(Map::rightHallEnd);
				break;
			case 3:
				Office::isLeftLightOn = Office::isRightLightOn = true;
				std::cout << "Both lights were turned on.\n";
				break;
			case 4:
				Office::isLeftLightOn = Office::isRightLightOn = false;
				std::cout << "Both lights were turned off.\n";
				break;
			}
			std::cout << std::noboolalpha;
			Pause::pauseForMiliseconds(1500);
			didPlayerAct = true;
			break;
		}
		case 4: // Nothing
			didPlayerAct = true;
			++doNothingAmount;
			break;
		}

		if (didPlayerAct)
		{
			Night::updateState(wasFoxyCheckedOn);

			if (Random::get(1, 4) == 1 && iteration >= 5)
			{
				Night::displaySpookyMessage();
				Pause::pauseForMiliseconds(500);
				std::cout << '\n';
			}
		}

		++iteration;
	}
}

void Night::setup()
{
	int optionNumber{};
	while (true)
	{
		std::cout << "======MENU======\n";
		std::cout << "1) Start Night (Good luck!)\n";
		std::cout << "2) Set Animatronic AI Levels (5 by default)\n";
		std::cout << "3) Read Game Mechanics (Very long, but highly reccomended)\n";
		std::cout << "4) Quit\n";
		std::cout << "Choose an option: ";
		optionNumber = Input::getValidatedIntInputInRange(1, 4);

		switch (optionNumber)
		{
		case 1:
			return; // Go back to 'Night::start()'
		case 2:
			Line::display();
			Night::setAnimatronicAILevels();
			Line::display();
			break;
		case 3:
			Line::display();
			TextFiles::displayTextFromFile("gameMechanics.txt");
			Line::display();
			break;
		case 4:
			std::exit(0);
		}
	}
}

void Night::setAnimatronicAILevels()
{
	std::cout << "======ANIMATRONICS' AI LEVELS======\n";
	std::cout << std::setw(10) << std::left << "Freddy: " << freddy.getAILevel() << '\n';
	std::cout << std::setw(10) << std::left << "Bonnie: " << bonnie.getAILevel() << '\n';
	std::cout << std::setw(10) << std::left << "Chica: " << chica.getAILevel() << '\n';
	std::cout << std::setw(10) << std::left << "Foxy: " << foxy.getAILevel() << '\n';

	std::cout << '\n';

	std::cout << "1) Set Specifc AI Level\n";
	std::cout << "2) Set All AI Levels\n";
	std::cout << "3) Cancel\n";
	int optionNumber{};
	while (true)
	{
		std::cout << "Choose an option: ";
		optionNumber = Input::getValidatedIntInputInRange(1, 3);
		break;
	}

	if (optionNumber == 1)
	{
		std::cout << "1) Freddy\n";
		std::cout << "2) Bonnie\n";
		std::cout << "3) Chica\n";
		std::cout << "4) Foxy\n";
		int animatronicChoice{};
		while (true)
		{
			std::cout << "Which animatronic's AI level will be changed?: ";
			animatronicChoice = Input::getValidatedIntInputInRange(1, 4);
			break;
		}

		int aiLevel{};
		while (true)
		{
			std::cout << "Enter the new AI level (Max is " << Animatronic::s_aiMaxLevel << "): ";
			aiLevel = Input::getValidatedIntInputInRange(0, Animatronic::s_aiMaxLevel);
			break;
		}

		switch (animatronicChoice)
		{
		case 1: freddy.setAILevel(aiLevel); break;
		case 2: bonnie.setAILevel(aiLevel); break;
		case 3: chica.setAILevel(aiLevel); break;
		case 4: foxy.setAILevel(aiLevel); break;
		}
		std::cout << "The AI level has been changed to " << aiLevel << ".\n";
	}
	else if (optionNumber == 2)
	{
		int aiLevel{};
		while (true)
		{
			std::cout << "Enter the new AI level (Max is " << Animatronic::s_aiMaxLevel << "): ";
			aiLevel = Input::getValidatedIntInputInRange(0, Animatronic::s_aiMaxLevel);
			break;
		}
		freddy.setAILevel(aiLevel);
		bonnie.setAILevel(aiLevel);
		chica.setAILevel(aiLevel);
		foxy.setAILevel(aiLevel);
		std::cout << "All the animatronics' AI levels have been changed to " << aiLevel << ".\n";
	}
	else
		return;
}

void Night::displayStats()
{
	std::cout << std::boolalpha;
	std::cout << "======STATS======\n";
	std::cout << std::setw(22) << std::left << "Time: " << GameTime::currentTime << '\n';
	std::cout << std::setw(22) << std::left << "Battery (%): " << Office::battery << '\n';
	std::cout << std::setw(22) << std::left << "Left Door Is Open: " << Office::isLeftDoorOpen << '\n';
	std::cout << std::setw(22) << std::left << "Right Door Is Open: " << Office::isRightDoorOpen << '\n';
	std::cout << std::setw(22) << std::left << "Left Light Is On: " << Office::isLeftLightOn << '\n';
	std::cout << std::setw(22) << std::left << "Right Light Is On: " << Office::isRightLightOn << '\n';
	std::cout << std::noboolalpha;
}

void Night::displaySpookyMessage()
{
	switch (Random::get(1, 14))
	{
	case 1:  std::cout << "WHY DID YOU TAKE THIS JOB?\n"; break;
	case 2:  std::cout << "THEY ARE WATCHING YOU\n"; break;
	case 3:  std::cout << "[Whisper] COME CLOSER\n"; break;
	case 4:  std::cout << "[Faint carnival music playing]\n"; break;
	case 5:  std::cout << "SOMEONE IS BEHIND YOU\n"; break;
	case 6:  std::cout << "IT'S ME\n"; break;
	case 7:  std::cout << "CHILDREN SCREAM IN THE BACKGROUND\n"; break;
	case 8:  std::cout << "SOMETHING MOVES AT THE CORNER OF YOUR EYE\n"; break;
	case 9:  std::cout << "A COLD CHILL RUNS DOWN YOUR SPINE\n"; break;
	case 10: std::cout << "[Distorted] YOU CAN'T HIDE FOREVER\n"; break;
	case 11: std::cout << "DO NOT KEEP THE DOORS CLOSED\n"; break;
	case 12: std::cout << "THE VOICES ARE BECOMING LOUDER\n"; break;
	case 13: std::cout << "A MENACING LAUGH COMES FROM OUTSIDE\n"; break;
	case 14: std::cout << "[Distorted] YOU WILL NEVER LEAVE\n"; break;
	}
}

void Night::updateState(bool wasFoxyCheckedOn)
{
	Office::drainBattery();
	if (Office::battery == 0)
	{
		OutputDelay::println("The power went out, and Freddy comes dashing in with glowing red eyes to brutally maul you.");
		OutputDelay::println("Blood splatters everywhere, and you keep screaming and screaming for help.");
		OutputDelay::println("The other animatronics arrive and stare down at you with glowing red eyes.");
		OutputDelay::println("Nobody else can hear your screams");
		Pause::pauseForMiliseconds(200);
		OutputDelay::println("...", 200);
		OutputDelay::println("You are barely breathing, and the animatronics take you to stuff you in an animatronic suit.");
		Pause::pauseForMiliseconds(500);
		OutputDelay::println("GAME OVER!", 100);
		std::exit(0);
	}

	GameTime::update();

	AnimFuncs::decrementDoorWaitCountdowns();

	AnimFuncs::move(freddy);
	AnimFuncs::move(bonnie);
	AnimFuncs::move(chica);
	AnimFuncs::moveFoxy(wasFoxyCheckedOn);

	AnimFuncs::checkForOfficeEntry(freddy);
	AnimFuncs::checkForOfficeEntry(bonnie);
	AnimFuncs::checkForOfficeEntry(chica);
	AnimFuncs::checkForOfficeEntry(foxy);
}
