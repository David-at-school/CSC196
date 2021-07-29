#include "ParticleSystem.h"
#include "Math\Random.h"
#include "Math/MathUtils.h"

namespace ds
{
	void ParticleSystem::Startup()
	{
		particles.resize(1000000);
	}

	void ParticleSystem::Shutdown()
	{
		particles.clear();
	}

	void ParticleSystem::Update(float dt)
	{
		for (Particle& particle : particles)
		{
			if (particle.isActive)
			{
				particle.lifetime -= dt;
				particle.isActive = particle.lifetime > 0;
				particle.prevPosition = particle.position;
				particle.position += particle.velocity * dt;
				//particle.velocity.x *= (1 - dt / 4);
				//particle.velocity.y += (50 * dt);
				particle.angle = std::atan2(particle.velocity.x, particle.velocity.y);
			}
		}
	}

	void ParticleSystem::Draw(Core::Graphics& graphics)
	{
		for (const Particle& particle : particles)
		{
			if (particle.isActive) {
				graphics.SetColor(particle.color);
				graphics.DrawLine(particle.position.x, particle.position.y, particle.position.x + (particle.velocity.x / 2), particle.position.y + (particle.velocity.y / 2));
			}
		}
	}

	void ParticleSystem::Create(const Vector2& position, size_t count, float lifetime, const Color& color, float speed)
	{
		for (size_t i = 0; i < count; i++)
		{
			auto particle = std::find_if(particles.begin(), particles.end(), Particle::isNotActive);
			if (particle != particles.end())
			{
				particle->isActive = true;
				particle->lifetime = lifetime;
				particle->position = position;
				particle->prevPosition = position;
				particle->color = color;
				float randX = RandomRange(-1, 1);
				float randY = RandomRange(-1, 1);
				particle->angle = std::atan2(randX, randY);
				particle->velocity = Vector2{ randX, randY } *(speed * Random());
			}
		}
	}

	void ParticleSystem::Create(const Vector2& position, size_t count, float lifetime, const std::vector<ds::Color>& colors, float speed)
	{
		for (size_t i = 0; i < count; i++)
		{
			auto particle = std::find_if(particles.begin(), particles.end(), Particle::isNotActive);
			if (particle != particles.end())
			{
				particle->isActive = true;
				particle->lifetime = lifetime;
				particle->position = position;
				particle->prevPosition = position;
				particle->color = colors[ds::RandomRangeInt(0, colors.size())];
				float randX = RandomRange(-1, 1);
				float randY = RandomRange(-1, 1);
				particle->angle = std::atan2(randX, randY);
				particle->velocity = Vector2{ randX, randY } * (speed * Random());
			}
		}
	}
	void ParticleSystem::Create(const Vector2& position, size_t count, float lifetime, const std::vector<ds::Color>& colors, float speed, float angle, float angleRange)
	{
		for (size_t i = 0; i < count; i++)
		{
			auto particle = std::find_if(particles.begin(), particles.end(), Particle::isNotActive);
			if (particle != particles.end())
			{
				particle->isActive = true;
				particle->lifetime = lifetime;
				particle->position = position;
				particle->prevPosition = position;
				particle->color = colors[ds::RandomRangeInt(0, colors.size())];
				float randX = RandomRange(-1, 1);
				float randY = RandomRange(-1, 1);
				particle->angle = std::atan2(randX, randY);
				particle->velocity = (ds::Vector2::Rotate(ds::Vector2::right, angle + ds::RandomRange(-angleRange, angleRange))) * (speed * Random());
			}
		}
	}
}