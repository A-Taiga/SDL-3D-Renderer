#include "SDL2/SDL_events.h"
#include "SDL2/SDL_pixels.h"
#include "SDL2/SDL_stdinc.h"
#include "window.hpp"
#include "shapes.hpp"
#include <iostream>
#include "SDL2/SDL_timer.h"

SDL_Color color_select(const char* arg);
void arg_manager(int argc, char* argv[], std::string& file, SDL_Color& color, int& width, int& height);

int main(int argc, char* argv[])
{
	bool running = true;

	Uint64 start;
	Uint64 end;
	float elapsedMS;
	SDL_Color color;
	std::string file = "mesh-files/";
	int width;
	int height;
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;

	arg_manager(argc,argv,file,color,width,height);

	// std::cout << file << std::endl;
	// printf("%d, %d, %d, %d\n",color.r,color.g,color.b,color.a);

	Window window(600,600);

	Shape3D obj(300,300,0,width,height,window.get_renderer(), file.c_str());
	Shape3D xyz(100,500,0,20,20,window.get_renderer(), "mesh-files/xyz.obj");

	
	while(running)
	{
		start = SDL_GetPerformanceCounter();

		xyz.set_color({WHITE});
		xyz.rotate(x,y,z);
		xyz.draw();
	
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
void arg_manager(int argc, char* argv[], std::string& file, SDL_Color& color, int& width, int& height)
{

	if(argc < 5)
	{
		std::cout << "Input requires object file color width and height" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	file += argv[1];
	color = color_select(argv[2]);
	width = atoi(argv[3]);
	height = atoi(argv[4]);

	if(width == 0)
	{
		std::cout << "width not set" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	if(height == 0)
	{
		std::cout << "height not set" << std::endl;
		std::exit(EXIT_FAILURE);
	}

}