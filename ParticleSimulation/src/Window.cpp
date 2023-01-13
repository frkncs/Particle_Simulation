#include <iostream>
#include <Windows.h>
#include <SDL.h>
#include "Window.hpp"
#include "MouseHelper.hpp"
#include "Stack.hpp"

using namespace std;

namespace ParticleSimulationEngine
{
	void Window::Run()
	{
		Init("Particle Simulation");

		Loop();
	}

	void Window::SetPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue)
	{
		if (x <= 0 || y <= 0 || x >= Window::ScreenWidth || y >= Window::ScreenHeight)
		{
			// Out of the screen
			return;
		}

		_buffer[(y * ScreenWidth) + x] = static_cast<Uint32>(red << 24 | green << 16 | blue << 8 | 0xff);
	}

	void Window::Init(const char* windowName)
	{
		window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
								   ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);

		glContext = SDL_GL_CreateContext(window);

		_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
		_texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, ScreenWidth, ScreenHeight);

		_buffer = new Uint32[ScreenWidth * ScreenHeight];
		_newBuffer = new Uint32[ScreenWidth * ScreenHeight];

		ClearBuffers();
	}

	void Window::Loop()
	{
		Stack stack;

		while (_windowState != WindowStates::Exit)
		{
			if ((GetKeyState(VK_LBUTTON) & 0x80) != 0)
			{
				cout << "Left Mouse Button Pressing!" << endl;
			}

			int elapsedTime = SDL_GetTicks();

			srand(time(0));

			Point cursorPos = MouseHelper::GetCursorPos();

			const Particle* const particles = stack.GetParticles();
			
			unsigned char red = static_cast<unsigned char>((1 + cos(elapsedTime * 0.0005)) * 128);
			unsigned char green = static_cast<unsigned char>((1 + cos(elapsedTime * 0.0003)) * 128);
			unsigned char blue = static_cast<unsigned char>((1 + cos(elapsedTime * 0.0007)) * 128);

			for (int i = 0; i <= Stack::ParticleCount; i++)
			{
				Particle particleToMove = particles[i];

				int x = (particleToMove.position.x + 8 / (8 * Window::ParticleRingScale)) * (ScreenWidth / (2 / Window::ParticleRingScale));
				int y = (particleToMove.position.y * (ScreenWidth / (2 / Window::ParticleRingScale))) + ScreenHeight / 2;

				SetPixel(x, y, red, green, blue);
			}

			//BoxBlur();
			stack.Update(elapsedTime);
			Update();

			HandleEvents();
		}
	}

	void Window::Update()
	{
		SDL_UpdateTexture(_texture, NULL, _buffer,ScreenWidth * sizeof(Uint32));
		SDL_RenderClear(_renderer);
		SDL_RenderCopy(_renderer, _texture, NULL, NULL);
		SDL_RenderPresent(_renderer);
	}

	void Window::HandleEvents()
	{
		SDL_Event _event;
		SDL_PollEvent(&_event);

		switch (_event.type)
		{
			case SDL_QUIT:
				_windowState = WindowStates::Exit;

				delete[] _buffer;
				delete[] _newBuffer;

				DestroyTexture();

				break;
		}
	}

	void Window::BoxBlur()
	{
		// Swap buffers
		Uint32* temBuf = _buffer;
		_buffer = _newBuffer;
		_newBuffer = temBuf;

		for (int y = 0; y < ScreenHeight; y++)
		{
			for (int x = 0; x < ScreenWidth; x++)
			{
				int totalRed = 0;
				int totalGreen = 0;
				int totalBlue = 0;

				for (int row = -1; row <= 1; row++)
				{
					for (int col = -1; col <= 1; col++)
					{
						int current_x = x + col;
						int current_y = y + row;

						if (current_x >= 0 && current_x < ScreenWidth &&
							current_y >= 0 && current_y < ScreenHeight)
						{
							auto color = _newBuffer[current_y * ScreenWidth + current_x];

							Uint8 red = color >> 24;
							Uint8 green = color >> 16;
							Uint8 blue = color >> 8;

							totalRed += red;
							totalGreen += green;
							totalBlue += blue;
						}
					}
				}

				Uint8 red = totalRed / 9;
				Uint8 green = totalGreen / 9;
				Uint8 blue = totalBlue / 9;

				SetPixel(x, y, red, green, blue);
			}
		}
	}

	void Window::ClearBuffers()
	{
		memset(_buffer, 0, ScreenWidth * ScreenHeight * sizeof(Uint32));
		memset(_newBuffer, 0, ScreenWidth * ScreenHeight * sizeof(Uint32));
	}

	void Window::DestroyRenderer()
	{
		SDL_DestroyRenderer(_renderer);
		SDL_DestroyWindow(window);
	}

	void Window::DestroyTexture()
	{
		SDL_DestroyTexture(_texture);
		DestroyRenderer();
	}
}