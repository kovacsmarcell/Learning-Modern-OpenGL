#include <iostream>
#include <GL/glew.h>
#include "Display.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"

#include <map>

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char** argv)
{
	Display display(800, 600, "SDL2 & OpenGL 3.3");

	Vertex vertices[] = {
		Vertex(glm::vec3(-0.5, -0.5, 0.0), glm::vec2(0.0, 0.0)),
		Vertex(glm::vec3(0, 0.5, 0.0), glm::vec2(0.5, 1.0)),
		Vertex(glm::vec3(0.5, -0.5, 0.0), glm::vec2(1.0, 0.0))
	};

	unsigned int indices[] = {
		0, 1, 2
	};

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	Mesh mesh2("./res/monkey3.obj");
	Shader shader("./res/basicShader");
	Texture texture("./res/bricks.jpg");
	Camera camera(glm::vec3(0, 0, -4), 70.0f, (float)display.GetWidth() / (float)display.GetHeight(), 0.01f, 1000.0f);
	Transform transform;

	double angle = 0.0f;

	int centerX = 400;
	int centerY = 300;

	std::map<int, bool> key;
	std::map<int, bool> buttons;

	bool mouseLocked = false;

	while (!display.IsClosed())
	{
		SDL_Event e;

		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				display.SetClosed(true);
			if (e.type == SDL_KEYDOWN)
			{
				key[e.key.keysym.sym] = true;
			}
			if (e.type == SDL_KEYUP)
			{
				key[e.key.keysym.sym] = false;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
				buttons[e.button.button] = true;
			if (e.type == SDL_MOUSEBUTTONUP)
				buttons[e.button.button] = false;
		}

		transform.SetRot(glm::vec3(0, angle * 100, angle * 100));

		if (mouseLocked)
		{
			int mouseX;
			int mouseY;

			SDL_GetMouseState(&mouseX, &mouseY);

			SDL_WarpMouseInWindow(display.GetWindow(), 400, 300);

			int mouseDX = mouseX - centerX;
			int mouseDY = mouseY - centerY;

			std::cout << mouseDX << " , " << mouseDY << std::endl;

			camera.Pitch(mouseDY / 2);
			camera.RotateY(-mouseDX / 2);
		}

		if (key[SDLK_ESCAPE])
		{
			SDL_ShowCursor(true);
			mouseLocked = false;
		}
		if (buttons[SDL_BUTTON_LEFT])
		{
			SDL_ShowCursor(false);
			SDL_WarpMouseInWindow(display.GetWindow(), 400, 300);

			mouseLocked = true;
		}

		if (key[SDLK_w])
			camera.MoveForward(0.02);
		if (key[SDLK_s])
			camera.MoveForward(-0.02);
		if (key[SDLK_a])
			camera.MoveRight(0.02);
		if (key[SDLK_d])
			camera.MoveRight(-0.02);

		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
		
		shader.Bind();
		texture.Bind(0);
		shader.Update(transform, camera);

		angle += 0.0001;

		//mesh.Draw();
		mesh2.Draw();

		display.Update();
	}

	return 0;
}