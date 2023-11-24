#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <memory>
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_stdinc.h"

class Window
{
	private:
	std::shared_ptr<SDL_Renderer*> renderer;
	SDL_Window* window;
	int width, height;
	void key_code(SDL_KeyboardEvent& key);

	public:
	Window(int _width, int _height);
	~Window();
	void poll_events(bool& running, float& x, float& y, float& z);
	void update();
	std::shared_ptr<SDL_Renderer*> get_renderer();
};


#endif