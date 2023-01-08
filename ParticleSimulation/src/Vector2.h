#pragma once

#ifndef VECTOR2_H_INCLUDED
#define VECTOR2_H_INCLUDED

#include <cmath>

struct Vector2
{
	double x;
	double y;

	double Length() const;
	void Normalize();

	Vector2 operator+(const Vector2& other) const;
	Vector2& operator+=(const Vector2& other);
	Vector2 operator-(const Vector2& other) const;
	Vector2& operator-=(const Vector2& other);
};

#endif // VECTOR2_H_INCLUDED
