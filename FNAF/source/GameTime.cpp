#include "GameTime.h"

std::string GameTime::currentTime{ "12 AM" };
int GameTime::hoursPassed{ 0 };
int GameTime::minutesPassed{ 0 };

void GameTime::update()
{
	minutesPassed += 12;

	if (minutesPassed == 60)
	{
		++hoursPassed;
		minutesPassed = 0;
		switch (hoursPassed)
		{
		case 1: currentTime = "1 AM"; break;
		case 2: currentTime = "2 AM"; break;
		case 3: currentTime = "3 AM"; break;
		case 4: currentTime = "4 AM"; break;
		case 5: currentTime = "5 AM"; break;
		case 6: currentTime = "6 AM"; break;
		}
	}
}

bool GameTime::is6AM()
{
	return (hoursPassed == 6) ? true : false;
}