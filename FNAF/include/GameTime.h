#ifndef TIME_H
#define TIME_H

#include <string>

namespace GameTime
{
	extern std::string currentTime;
	extern int hoursPassed;
	extern int minutesPassed; // must be a factor of 60

	void update();
	bool is6AM();
};

#endif