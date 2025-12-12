#include "Renderer.h"

Renderer::Renderer(SDL_Window* window)
{
	renderer = SDL_CreateRenderer(window, NULL);
	if (renderer == NULL)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, 
			"Error", "Failed to initialize renderer.", nullptr);
	}
}