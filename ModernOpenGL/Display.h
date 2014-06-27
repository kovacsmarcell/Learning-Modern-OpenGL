#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <string>

class Display
{
public:
	Display(int width, int height, const std::string& title);
	~Display();

	void Clear(float r, float g, float b, float a);
	void Update();

	bool IsClosed();
	
	int GetWidth()
	{
		int w = 0;

		SDL_GetWindowSize(m_window, &w, NULL);
		
		return w;
	}
	int GetHeight()
	{
		int h = 0;

		SDL_GetWindowSize(m_window, NULL, &h);

		return h;
	}

	void SetClosed(bool closed) { isClosed = closed; }

	SDL_Window* GetWindow() { return m_window; }

private:
	SDL_Window* m_window;
	SDL_GLContext m_glContext;

	bool isClosed;
};

#endif