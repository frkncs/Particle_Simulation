#include "Vector2.h"

double Vector2::Length() const
{
	return std::sqrt((x * x) + (y * y));
}

void Vector2::Normalize()
{
	const double l = Length();
	x /= l;
	y /= l;
}

Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2{ x + other.x, y + other.y };
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	x += other.x;
	y += other.y;

	return *this;
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2{ x - other.x, y - other.y };
}

Vector2& Vector2::operator-=(const Vector2& other)
{
	x -= other.x;
	y -= other.y;

	return *this;
}