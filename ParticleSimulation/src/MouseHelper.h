#pragma once

#ifndef MOUSEHELPER_H_INCLUDED
#define MOUSEHELPER_H_INCLUDED

struct Point
{
	Point(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	float x;
	float y;
};

class MouseHelper
{
public:
	static Point GetCursorPos();
};

#endif // MOUSEHELPER_H_INCLUDED
