#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <stdlib.h>
#include <atltime.h>
using namespace std;
#pragma warning(disable : 4996)
int main(int argc, char *argv[])
{
	bool closed = false;

	// SDL init
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		perror("Failed to init sdl\n");

	// init window, renderer and texture ptr
	SDL_Window* window = SDL_CreateWindow("Dam Clock", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,800,800,SDL_WINDOW_SHOWN);
	SDL_Surface* screen = SDL_GetWindowSurface(window);
	SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) perror("Failed to create a new renderer.\n"); 

	SDL_Texture* _texture1;
	SDL_Texture* _texture2;
	SDL_Texture* _texture3;
	SDL_Texture* _texture4;

	// load png
	SDL_Surface* Hour = IMG_Load("../res/hourNid_png.png");
	if (Hour == NULL) cerr << "Error in loading hour niddle\n";
	SDL_Surface* Minute = IMG_Load("../res/minNid_png.png");
	if (Minute == NULL) cerr << "Error in loading minute niddle\n";
	SDL_Surface* Clock = IMG_Load("../res/clock_png.png");
	if (Clock == NULL) cerr << "Error in loading base clock\n";
	SDL_Surface* Second = IMG_Load("../res/secNid_png.png");
	if (Second == NULL) cerr << "Error in loading second niddle\n";

	// clock looping
	while (!closed)
	{
		// create texture for clock
		_texture1 = SDL_CreateTextureFromSurface(renderer, Clock);

		// create texture for min niddle
		_texture2 = SDL_CreateTextureFromSurface(renderer, Minute);

		// create texture for hour niddle
		_texture3 = SDL_CreateTextureFromSurface(renderer, Hour);

		// create texture for second niddle
		_texture4 = SDL_CreateTextureFromSurface(renderer, Second);
		// merge all texture
		//SDL_Texture* target_Texture = SDL_CreateTexture(renderer);
		time_t now = time(0);
		//tm* current_time = localtime(&now);
		struct tm current_time;
		localtime_s(&current_time,&now);
		double hour = current_time.tm_hour%12;
		double min = current_time.tm_min;
		double sec = current_time.tm_sec;
		//cout << "Hour: " << hour << " Minute: " << min << endl;
		double min_deg = min / 60 * 360;
		double hour_deg_offset = min / 60 * 30;
		double hour_deg = hour / 12 * 360 + hour_deg_offset;
		double sec_deg = sec / 60 * 360;
		SDL_RenderCopy(renderer,_texture1,NULL,NULL);
		SDL_RenderCopyEx(renderer,_texture2,NULL,NULL,min_deg,NULL,SDL_FLIP_NONE);
		SDL_RenderCopyEx(renderer, _texture3, NULL, NULL,hour_deg , NULL, SDL_FLIP_NONE);
		SDL_RenderCopyEx(renderer,_texture4,NULL,NULL,sec_deg,NULL,SDL_FLIP_NONE);
		//SDL_SetRenderTarget(renderer, NULL);
		SDL_RenderPresent(renderer);
		SDL_Delay(500);
		//free(current_time);
		SDL_Event e;
		if (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
			{
				closed = true;
				break;
			}
			default:
				break;
			}
		}
		SDL_RenderClear(renderer);
		SDL_DestroyTexture(_texture1);
		SDL_DestroyTexture(_texture2);
		SDL_DestroyTexture(_texture3);
		SDL_DestroyTexture(_texture4);
	}
	return 0;
}
