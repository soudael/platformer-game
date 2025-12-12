#include "Platforms.h"

Platforms::Platforms(float x, float y, float w, float h)
{
	platformRect.x = x;
	platformRect.y = y;
	platformRect.w = w;
	platformRect.h = h;
}

void Platforms::render(SDL_Renderer* renderer, float cameraXOffset, float cameraYOffset)
{
	SDL_FRect ghostPlatform = platformRect;
	ghostPlatform.x -= cameraXOffset;
	ghostPlatform.y -= cameraYOffset;
	
    SDL_SetRenderDrawColor(renderer, 120, 120, 120, 255);
    SDL_RenderFillRect(renderer, &ghostPlatform);
}