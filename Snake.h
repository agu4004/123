#pragma once
//done a point
struct sth
{
	int x;
	int y;
};

sth AddIn(const sth& a, const sth& b)
{
	return sth{ a.x + b.x , a.y + b.y };
}

void Place(sth& a, const sth& b)
{
	a.x += b.x;
	a.y += b.y;
}

class Snake
{
public:
	//length of the tail: done
	sth tail[tail_max] ;
	int tail_start = 0;
	int tail_end = 0;
	int tail_length = 0;


	//The dimensions of the dot
	static const int SNAKE_WIDTH = scl;
	static const int SNAKE_HEIGHT = scl;

	//Maximum axis velocity of the dot
	static const int SNAKE_VEL = scl;

	//Initializes the variables
	Snake();


	//Takes key presses and adjusts the dot's velocity
	void handleEvent(SDL_Event& e);

	//Moves the dot
	void move();

	//Shows the dot on the screen
	void render();


private:
	//toa do moi done
	sth pos; // vi tri
	sth vel; // van toc
};
