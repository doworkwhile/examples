#ifndef SDL_gameh_h_
#define SDL_gameh_h_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "sdl_gameh_quitflag.h"
#include "sdl_gameh_colors.h"
#include "sdl_gameh_timelock.h"
#include "sdl_gameh_text.h"

typedef struct {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;
	Timelock fpsLock;
	Timelock upsLock;
	Timelock fpsCountLock;
	Timelock upsCountLock;
	bool shouldWaitForEvent;
	bool firstRender;
} GameH;

GameH engine;

void eventQuitFlag() {
  quitFlag = (
    engine.event.type == SDL_QUIT ||
    (
      engine.event.type == SDL_WINDOWEVENT &&
      engine.event.window.event == SDL_WINDOWEVENT_CLOSE
    )
  );
}

// these are the functions the engine calls
void gameSetup();
void gameEventing();
void gameUpdating();
void gameRendering();
void gameFree();


void engineSetup(int w, int h, int fps, int ups)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("failed to init sdl2\n");
		return;
	}

	enableText(20);

	engine.window = SDL_CreateWindow("Test",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		w, h,
		SDL_WINDOW_SHOWN
	);
	engine.renderer = SDL_CreateRenderer
	(
		engine.window, -1, SDL_RENDERER_ACCELERATED
	);

	Timelock_Init(&engine.fpsCountLock, 1000);
	Timelock_Init(&engine.upsCountLock, 1000);

	if (fps < 1) {
		engine.shouldWaitForEvent = true;
		Timelock_Init(&engine.fpsLock, 16);
	} else {
		Timelock_Init(&engine.fpsLock, fps);
	}
	if (ups < 1) {
		engine.shouldWaitForEvent = true;
		Timelock_Init(&engine.upsLock, 16);
	} else {
		Timelock_Init(&engine.upsLock, ups);
	}

	engine.firstRender = true;

	gameSetup();
}

void engineRenderCall()
{
	SDL_SetRenderDrawColor(engine.renderer, 255, 255, 255, 255);
	SDL_RenderClear(engine.renderer);
	gameRendering();
	SDL_RenderPresent(engine.renderer);
	Timelock_Unlock(&engine.fpsLock);
}

void engineEventCall()
{
	eventQuitFlag();
	if (!quitFlag)
		gameEventing();
}

void engineLoop()
{
	while(!quitFlag) {
		// Eventing
		if (engine.shouldWaitForEvent) {
			SDL_WaitEvent(&engine.event);
			engineEventCall();
		} else {
			while (SDL_PollEvent(&engine.event)) {
				engineEventCall();
			}
		}

		// Updating
		if (!quitFlag && Timelock_IsLocked(&engine.upsLock)) {
			gameUpdating();
			Timelock_Unlock(&engine.upsLock);
		}

		// Rendering
		if (!quitFlag && Timelock_IsLocked(&engine.fpsLock)) {
			engineRenderCall();			
		}

		// FPS Counter
		if (Timelock_IsLocked(&engine.fpsCountLock)) {
			Timelock_Recount(&engine.fpsLock);
			Timelock_Unlock(&engine.fpsCountLock);
		}

		// UPS Counter
		if (Timelock_IsLocked(&engine.upsCountLock)) {
			Timelock_Recount(&engine.upsLock);
			Timelock_Unlock(&engine.upsCountLock);
		}

		// Delay(1) or WaitEvent
		SDL_Delay(1);
	}
}

void engineFree()
{
	gameFree();
	disableText();
	SDL_DestroyWindow(engine.window);
	SDL_Quit();
}

void start(int width, int height, int fps, int ups) {
	engineSetup(width, height, fps, ups);
	engineRenderCall();
	engineLoop();
	engineFree();
}

#endif