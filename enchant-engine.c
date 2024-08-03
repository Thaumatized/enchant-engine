#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <math.h>

#ifdef __linux__
	#include <unistd.h>
#endif

#ifdef __MINGW32__
	//for printf
	#include <stdio.h>
	// for sleep
	#include <windows.h>

	int usleep(int microseconds)
	{
		Sleep(microseconds / 1000);
	}
#endif

#include "version.h"
#include "../game.h"

int main(int argc, char* argv[])
{
	printf("initializing engine, version %s\n", ENGINE_VERSION);

	int frameRate = 60;
	int clocksPerFrame = CLOCKS_PER_SEC / frameRate;
	int frame = 0;

	printf("initializing game\n");
	initialize(argc, argv);

	
	while(1)
	{
		clock_t FrameStartClock = clock();
		update(frame);
		
		//Sleep until we have taken up enough time.
		int ClocksThisFrame = clock()-FrameStartClock;
		int ClocksToSleep = clocksPerFrame - ClocksThisFrame;
		if(ClocksToSleep > 0)
		{
			usleep((int)(((double)ClocksToSleep) / CLOCKS_PER_SEC * 1000000));
		}
		else
		{
			printf("LAG FRAME!\n");
		}

		frame++;
	}
}

void closeGame()
{
	cleanUp();
	exit(0);
}