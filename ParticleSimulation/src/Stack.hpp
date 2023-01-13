#pragma once

#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "Particle.hpp"

class Stack
{
public:
	const static int ParticleCount = 2500;

private:
	Particle* _particles;
	int _lastTime;

public:
	Stack();
	~Stack();

	const Particle* const GetParticles()
	{
		return _particles;
	}

	void Update(int elapsedTime);
};

#endif // STACK_H_INCLUDED
