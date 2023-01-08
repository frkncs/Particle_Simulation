#pragma once

#ifndef PARTICLE_H_INCLUDED
#define PARTICLE_H_INCLUDED

#include "Vector2.h"

struct Particle
{
public:
	Vector2 position;

private:
	double _speed;
	float _direction;

public:
	Particle();
	void Update(int interval);
private:
	void Init();
};

#endif PARTICLE_H_INCLUDED
