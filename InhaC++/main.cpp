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
		std::cout << "�� �ɸ� �ð� = " << fTime << std::endl;
	}


	return 0;
}