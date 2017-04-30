#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <iostream>

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;
const int SCREEN_FPS = 10;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;
char lame[100];
const int tail_max = 900;
int a = rand() % 28 + 1;
int b = rand() % 28 + 1;
const int scl = 20;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Globally used font
TTF_Font* gFont = NULL;

//rect
SDL_Rect box = { 0,0,600,600 };
SDL_Rect playground = { 20,20,560,560 };
SDL_Rect food = { a*scl,b*scl,20,20 };
SDL_Rect tail = { 0,0,20,20 };

