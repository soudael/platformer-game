#pragma once

#include <SDL3/SDL.h>

class Renderer
{
	public:
		Renderer(SDL_Window* window);

		SDL_Renderer* getRendererObj() const { return renderer; }
	private:
		SDL_Renderer* renderer = nullptr;
};