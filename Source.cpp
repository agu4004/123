#include "dependencies.h"
#include "LTexture.h"
#include "LTimer.h"
#include "Snake.h"

//stuff from selfmade header
//Scene textures
LTexture gTextTexture;

//head
LTexture gHead;

//Tail
LTexture gTail;

//food 
LTexture gFood;




LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile(std::string path)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

#ifdef _SDL_TTF_H
bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface != NULL)
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
	else
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}


	//Return success
	return mTexture != NULL;
}
#endif

void LTexture::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}



LTimer::LTimer()
{
	//Initialize the variables
	mStartTicks = 0;
	mPausedTicks = 0;

	mPaused = false;
	mStarted = false;
}

void LTimer::start()
{
	//Start the timer
	mStarted = true;

	//Unpause the timer
	mPaused = false;

	//Get the current clock time
	mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
}

void LTimer::stop()
{
	//Stop the timer
	mStarted = false;

	//Unpause the timer
	mPaused = false;

	//Clear tick variables
	mStartTicks = 0;
	mPausedTicks = 0;
}

void LTimer::pause()
{
	//If the timer is running and isn't already paused
	if (mStarted && !mPaused)
	{
		//Pause the timer
		mPaused = true;

		//Calculate the paused ticks
		mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
	}
}

void LTimer::unpause()
{
	//If the timer is running and paused
	if (mStarted && mPaused)
	{
		//Unpause the timer
		mPaused = false;

		//Reset the starting ticks
		mStartTicks = SDL_GetTicks() - mPausedTicks;

		//Reset the paused ticks
		mPausedTicks = 0;
	}
}

Uint32 LTimer::getTicks()
{
	//The actual timer time
	Uint32 time = 0;

	//If the timer is running
	if (mStarted)
	{
		//If the timer is paused
		if (mPaused)
		{
			//Return the number of ticks when the timer was paused
			time = mPausedTicks;
		}
		else
		{
			//Return the current time minus the start time
			time = SDL_GetTicks() - mStartTicks;
		}
	}

	return time;
}

bool LTimer::isStarted()
{
	//Timer is running and paused or unpaused
	return mStarted;
}

bool LTimer::isPaused()
{
	//Timer is running and paused
	return mPaused && mStarted;
}



void FoodUpdate()
{
	srand(time(0));
	a = rand() % 28 + 1;
	b = rand() % 28 + 1;
	food = { a*scl,b*scl,scl,scl };
}

//dot define  = done
Snake::Snake()
{
	//strarting point 
	pos.x = scl;
	pos.y = scl;

	//starting velocity
	vel.x = 0;
	vel.y = 0;



}

//dot key press even = done
void Snake::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			if (vel.y == -SNAKE_VEL || vel.y == SNAKE_VEL)
			{
				break;
			}
			else
			{
				vel.x = 0;
				vel.y -= SNAKE_VEL;
			}
			break;
		case SDLK_DOWN:
			if (vel.y == -SNAKE_VEL || vel.y == SNAKE_VEL)
			{
				break;
			}
			else
			{
				vel.x = 0;
				vel.y += SNAKE_VEL;
			}
			break;
		case SDLK_LEFT:
			if (vel.x == -SNAKE_VEL || vel.x == SNAKE_VEL)
			{
				break;
			}
			else
			{
				vel.x -= SNAKE_VEL;
				vel.y = 0;
			}
			break;
		case SDLK_RIGHT:
			if (vel.x == -SNAKE_VEL || vel.x == SNAKE_VEL)
			{
				break;
			}
			else
			{
				vel.x += SNAKE_VEL;
				vel.y = 0;
			}
			break;
		}
	}
}

//dot move around = done
void Snake::move()
{
	tail[tail_end % tail_max] = pos;
	tail_start++;
	tail_end++;	

	//Move the dot left or right
	pos.x += vel.x;

	//setup border left or right
	if (pos.x < scl)
	{
		//Move back
		pos.x += 560;
	}
	if (pos.x + SNAKE_WIDTH > 580)
	{
		//Move back
		pos.x -= 560 ;
	}

	//Move the dot up or down
	pos.y += vel.y;

	//setup border up and down
	if (pos.y < scl)
	{
		//Move back
		pos.y += 560;
	}
	if (pos.y + SNAKE_HEIGHT > 580)
	{
		//Move back
		pos.y -= 560;
	}

	//eat the food
	if (pos.x == food.x && pos.y == food.y)
	{
		tail_length++;
		tail_start--;
		FoodUpdate();
	}

	//logic of the tail
	for (int i = 0; i < tail_length; i++)
	{
		//this things setup all the tail tiles
		sth& tail_pos = tail[(tail_start + i) % tail_max];
		if (tail_pos.x == pos.x && tail_pos.y == pos.y)
		{
			tail_length = 0;
			tail_start = tail_end;
		}
	}

}

//done
void Snake::render()
{
	//Show the head
	gHead.render(pos.x, pos.y);
	
	//And the tail
	for (int i = 0; i < tail_length; i++)
	{
		sth& tail_pos = tail[(tail_start + i) % tail_max];
		gTail.render(tail_pos.x , tail_pos.y);
	}

	gFood.render(food.x, food.y);
	
}


//done this
#include "EVERYTHING.h"

void screen()
{
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
	SDL_RenderFillRect(gRenderer, &box);
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(gRenderer, &playground);
}


int main(int argc, char* args[])
{
	//khoi tao
	if (!init()){printf("Failed to initialize!\n");}

	else{
		//Load media
		if (!loadMedia()){printf("Failed to load media!\n");}

		else{
			bool running = true;
			SDL_Event e;
			//done 

			//The dot that will be moving around on the screen
			Snake snake;

			//The frames per second timer
			LTimer fpsTimer;

			//The frames per second cap timer
			LTimer capTimer;

			//Start counting frames per second
			int countedFrames = 0;
			fpsTimer.start();

			//While application is running
			while (running)
			{
				//Start cap timer
				capTimer.start();

				//move the dot when press button = done
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						running = false;
					}

					//Handle input for the dot
					snake.handleEvent(e);
				}

				//Calculate and correct fps
				float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
				if (avgFPS > 2000000)
				{
					avgFPS = 0;
				}

				//Move the snake = done 
				snake.move();

			
				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
				SDL_RenderClear(gRenderer);

				//render screen
				screen();
				
				//Render objects
				snake.render();
	
				//Update screen
				SDL_RenderPresent(gRenderer);
				++countedFrames;

				//If frame finished early
				int frameTicks = capTimer.getTicks();
				if (frameTicks < SCREEN_TICK_PER_FRAME)
				{
					//Wait remaining time
					SDL_Delay(SCREEN_TICK_PER_FRAME - frameTicks);
				}
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}