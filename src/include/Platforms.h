#pragma once
#include <SDL3/SDL.h>

class Platforms
{
	public:
		Platforms(float x, float y, float w, float h);

		void render(SDL_Renderer* renderer);

		const SDL_FRect& getPlatformRectObj() const { return platformRect; }
	private:
		SDL_FRect platformRect;
};