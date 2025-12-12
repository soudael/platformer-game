#pragma once

#include <SDL3/SDL.h>

class Window
{
	public:
		Window(const char* t, float x, float y);

		SDL_Window* getWindowObj() const { return window; }
	private:
		SDL_Window* window = nullptr;
};