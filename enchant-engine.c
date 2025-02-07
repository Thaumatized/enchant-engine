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

	void usleep(int microseconds)
	{
		Sleep(microseconds / 1000);
	}
#endif

#include "version.h"
#include "input.c"
#include "physics.c"
#include "../game.h"
#include "CONSTANTS.h"

char entities[OBJECT_LIMIT];
int currentEntityIndex = 0;
int createEntity()
{
	int entitiesGoneTrough = 0;
	while(entities[currentEntityIndex] != 0 && entitiesGoneTrough < OBJECT_LIMIT)
	{
		currentEntityIndex++;
		entitiesGoneTrough++;
		if(currentEntityIndex >= OBJECT_LIMIT)
		{
			currentEntityIndex -= OBJECT_LIMIT;
		}
	}

	if(entities[currentEntityIndex] != 0)
	{
		printf("ERROR: RAN OUT OF ENTITY SLOTS");
		exit(1);
	}

	entities[currentEntityIndex] = 1;
	return currentEntityIndex;
}

void closeGame()
{
	cleanUp();
	exit(0);
}

int main(int argc, char* argv[])
{
	printf("initializing engine, version %s\n", ENGINE_VERSION);
	
	initializeInputs();

	int frameRate = 60;
	int clocksPerFrame = CLOCKS_PER_SEC / frameRate;
	int frame = 0;

	printf("initializing game\n");
	initialize(argc, argv);
	
	while(1)
	{
		clock_t FrameStartClock = clock();


		inputZero();
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					printf("event quit\n");
					closeGame();
					break;
				case SDL_KEYDOWN:
				case SDL_KEYUP:
					inputEvent(event);
					break;
			}
		}
		inputCheck();

		physicsUpdate();
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