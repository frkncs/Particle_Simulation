#include "MouseHelper.h"
#include <SDL.h>

Point MouseHelper::GetCursorPos()
{
	int curX, curY;
	SDL_GetMouseState(&curX, &curY);

	return Point(curX, curY);
}