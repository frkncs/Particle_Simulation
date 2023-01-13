#include "Stack.hpp"
#include "Particle.hpp"

Stack::Stack() : _lastTime(0)
{
	_particles = new Particle[ParticleCount];
}

void Stack::Update(int elapsedTime)
{
	int interval = elapsedTime - _lastTime;

	for (int i = 0; i < Stack::ParticleCount; i++)
	{
		_particles[i].Update(interval);
	}

	_lastTime = elapsedTime;
}

Stack::~Stack()
{
	delete[] _particles;
}