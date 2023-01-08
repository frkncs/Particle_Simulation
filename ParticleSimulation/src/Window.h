#pragma once

#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include <SDL.h>

namespace ParticleSimulationEngine
{
	enum WindowStates
	{
		Play,
		Exit
	};

	class Window
	{
	public:
		static const int ScreenWidth = 1024;
		static const int ScreenHeight = 800;
	private:
		SDL_Window* _window;
		SDL_Renderer* _renderer;
		SDL_Texture* _texture;

		Uint32* _buffer;
		Uint32* _newBuffer;
		WindowStates _windowState;

	public:
		Window() :_window(NULL), _renderer(NULL), _texture(NULL), _windowState(WindowStates::Play),
			_buffer(NULL), _newBuffer(NULL)
		{
		};

		void Run();
	private:
		void Init(const char* windowName);
		void Loop();
		void Update();
		void SetPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
		void HandleEvents();
		void ClearBuffers();
		void BoxBlur();

		void DestroyRenderer();
		void DestroyTexture();
	};
}

#endif // WINDOW_H_INCLUDED
