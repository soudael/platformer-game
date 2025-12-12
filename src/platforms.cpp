#include "Platforms.h"

Platforms::Platforms(float x, float y, float w, float h)
{
	platformRect.x = x;
	platformRect.y = y;
	platformRect.w = w;
	platformRect.h = h;
}

void Platforms::render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 140, 140, 140, 255);
    SDL_RenderFillRect(renderer, &platformRect);
}