#pragma once

bool screen()
{
	bool success = true;
	//SDL co hay ko
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL could not initialize! SDL_Error: %s\n" << SDL_GetError();
		success = false;
	}

	else
	{
		//tao window
		window = SDL_CreateWindow("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
		if (window == NULL)
		{
			std::cout << "Window could not be created! SDL_Error: %s\n" << SDL_GetError();
			success = false;
		}

		else
		{
			//render window
			background = SDL_CreateRenderer(window, -1, 0);
			
		}
	}
	return success;
}


void close()
{

	//Deallocate render
	SDL_RenderClear(background);
	background = NULL;

	//Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}
