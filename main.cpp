#include <SDL.h>
#include <iostream>
#include <Windows.h>


const int height = 600;
const int width = 800;
SDL_Window* window;
SDL_Renderer* background;
SDL_Rect snake;
const int scl = 20;

#include "screen.h"

void update(int x, int y, int xspeed, int yspeed)
{
	snake.x = snake.x + xspeed;
	snake.y = snake.y + yspeed;
}


void SnakeDelColor()
{
	SDL_SetRenderDrawColor(background, 0, 0, 0, 0);
	SDL_RenderFillRect(background, &snake);
	SDL_SetRenderDrawColor(background, 0, 0, 0, 0);
	SDL_RenderDrawRect(background, &snake);

}

void SnakeColor()
{
	SDL_SetRenderDrawColor(background, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(background, &snake);
	SDL_SetRenderDrawColor(background, 255, 255, 255, 255);
	SDL_RenderDrawRect(background, &snake);
	//SnakeDelColor();
	//Sleep(1000);
	//snake.x = snake.x + xspeed;
	//snake.y = snake.y + yspeed;
	//SDL_RenderClear(background);
	//SDL_RenderPresent(background);
}


void Snake()
{
	snake.x = 0;
	snake.y = 0;
	snake.w = scl;
	snake.h = scl;
	int xspeed = scl;
	int yspeed = 0;
	SnakeColor();
	//SDL_RenderPresent(background);
	//update(snake.x, snake.y, xspeed, yspeed);


}

void show()
{
	SDL_SetRenderDrawColor(background, 255, 255, 255, 255);
	SDL_RenderClear(background);
	SDL_Delay(1000);
	Snake();
	SDL_RenderPresent(background);
}


int main(int argc, char* argv[])
{	
	if (!screen())
	{
		std::cout << "Failed to initialize!\n";
	}
	else
	{
			bool quit = false;
			SDL_Event e;
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
				}

				//render 
				show();
		}
	}
	
	
	//clean up
	close();

	return 0;
}