#include "window.hpp"
#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_error.h"
#include "SDL2/SDL_keycode.h"

Window::Window(int _width, int _height)
: renderer(std::make_shared<SDL_Renderer*>())
, width(_width)
, height(_height)
{
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL init failure " << SDL_GetError() << std::endl;
		std::exit(EXIT_FAILURE);
	}
	window = SDL_CreateWindow("SDL-3D", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, width, height, 0);
	if(!window)
	{
		std::cout << "window is null " << SDL_GetError() << std::endl;
		std::exit(EXIT_FAILURE);
	}
	renderer = std::make_shared<SDL_Renderer*>(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));
	if(!renderer.get())
	{
		std::cout << "renderer is null " << SDL_GetError() << std::endl;
		std::exit(EXIT_FAILURE);
	}
}

Window::~Window()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Window::poll_events(bool& running, float& x, float& y, float& z)
{
	SDL_Event event;
	while(SDL_PollEvent(&event) > 0)
	{
		switch(event.type)
		{
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.scancode)
				{

					case SDL_SCANCODE_LEFT:	 y = -0.05;	break; // left
					case SDL_SCANCODE_RIGHT: y = 0.05;	break; // right
					case SDL_SCANCODE_UP:	 x = 0.05;	break; // up
					case SDL_SCANCODE_DOWN:	 x = -0.05;	break; // down
					case SDL_SCANCODE_A:	 z = -0.05;	break; //a
					case SDL_SCANCODE_D:	 z = 0.05;	break; //d

					default: break;
				}
				// key_code(event.key);
				break;
			case SDL_KEYUP:
				switch(event.key.keysym.scancode)
				{
					case SDL_SCANCODE_LEFT:
					case SDL_SCANCODE_RIGHT:	y = 0; break;
					case SDL_SCANCODE_UP:
					case SDL_SCANCODE_DOWN:		x = 0; break;
					case SDL_SCANCODE_A:
					case SDL_SCANCODE_D:		z = 0; break;

					default: break;
				}
				break;
		}
	}
}
void Window::update()
{
	SDL_SetRenderDrawColor(*renderer, 0, 0, 0, 0);
	SDL_RenderPresent(*renderer);
	SDL_RenderClear(*renderer);
}
std::shared_ptr<SDL_Renderer*> Window::get_renderer()
{
	return renderer;
}
void Window::key_code(SDL_KeyboardEvent& key)
{
	/* scan code */
	printf( "Scancode: 0x%02X ", key.keysym.scancode);
	/* Print the name of the key */
	printf( ", Name: %s\n", SDL_GetKeyName( key.keysym.sym ));
}
