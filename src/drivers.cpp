#include "Drivers.h"

void callVideoDrivers()
{
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, 
			"Error","Failed to initialize video drivers.", nullptr);
	}
}