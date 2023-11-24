#include "SDL2/SDL_pixels.h"
#include "SDL2/SDL_stdinc.h"
#include "window.hpp"
#include "shapes.hpp"
#include <iostream>
#include "SDL2/SDL_timer.h"


SDL_Color color_select(const char* arg);
int main([[gnu::unused]]int argc, char* argv[])
{

	SDL_Color color = {};
	std::string file = "mesh-files/";

	if(argc < 3)
	{
		std::cout << "Required object file input or color input" << std::endl;
		std::exit(EXIT_FAILURE);
	}	


	file += argv[1];

	color = color_select(argv[2]);
	std::cout << file << std::endl;


	printf("%d, %d, %d, %d\n",color.r,color.g,color.b,color.a);

	Window window(600,600);
	bool running = true;
	Uint64 start;
	Uint64 end;
	float elapsedMS;

	Shape3D obj(300,300,0,50,50,window.get_renderer(), file.c_str());

	float x = 0.f;
	float y = 0.f;
	float z = 0.f;

	while(running)
	{
		start = SDL_GetPerformanceCounter();

		obj.set_color(color);
		obj.rotate(x,y,z);
		obj.draw();

		window.update();
		window.poll_events(running,x,y,z);

		end = SDL_GetPerformanceCounter();
		elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
		
		// Cap to 60 FPS
		SDL_Delay(floor(16.666f - elapsedMS));

	}
	return 0;
}

SDL_Color color_select(const char* arg)
{
	if(!strcmp(arg,"WHITE"))		return {WHITE};
	else if(!strcmp(arg,"RED"))		return {RED};
	else if(!strcmp(arg,"CYAN"))	return {CYAN};
	else if(!strcmp(arg,"GREEN"))	return {GREEN};
	else if(!strcmp(arg,"PINK"))	return {PINK};
	else 							return {WHITE};
}
