#include <iostream>
#include "Chapter9.h"
#include "Timer.h"

int main()
{
	while (true)
	{
		Timer timer;
		Chapter9::Question4();
		float fTime = timer.GetTime();
		std::cout << "ÃÑ °É¸° ½Ã°£ = " << fTime << std::endl;
	}


	return 0;
}