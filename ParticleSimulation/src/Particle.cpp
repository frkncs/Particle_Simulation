#include "Particle.hpp"

#define M_PI 3.1415

Particle::Particle() : position(Vector2{0,0})
{
	Init();
}

void Particle::Init()
{
	position.x = 0;
	position.y = 0;

	_direction = (M_PI * 2 * rand()) / RAND_MAX;
	
	//_speed = 0.04 * rand() / RAND_MAX;
	_speed = 0.002 * (rand() % 10);
	
	_speed *= _speed;
}

void Particle::Update(int interval)
{
	_direction += interval * 0.001;

	Vector2 speedVector
	{
		_speed * cos(_direction) * interval,
		_speed * sin(_direction) * interval
	};

	position += speedVector;

	if (position.x <= -1 || position.x >= 1 || position.y <= -1 || position.y >= 1)
	{
		Init();
	}

	if (rand() < RAND_MAX / 100)
	{
		Init();
	}
}