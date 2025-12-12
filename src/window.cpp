#include "Window.h"

Window::Window(const char* t, float x, float y)
{
	window = SDL_CreateWindow(
		t, 
		x,
		y,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);
	if (window == NULL)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, 
			"Error", "Failed to initialize window.", nullptr);
	}
}