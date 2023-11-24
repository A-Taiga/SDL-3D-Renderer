#include "window.hpp"
#include "shapes.hpp"
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include "SDL2/SDL_timer.h"



int main([[gnu::unused]]int argc, char* argv[])
{

	if(argc < 2)
	{
		std::cout << "Required object file input" << std::endl;
		std::exit(EXIT_FAILURE);
	}


	std::string file = "object-files/";
	file += argv[1];



	std::cout << file << std::endl;

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

		obj.set_color(LIME);
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
