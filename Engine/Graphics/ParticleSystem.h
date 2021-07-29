#pragma once
#include "Math\Vector2.h"
#include "Math\Color.h"
#include "Base/System.h"
#include <vector>

namespace ds
{
	struct Particle
	{
		Vector2 position;
		Vector2 prevPosition;
		Vector2 velocity;
		Color color;
		float lifetime;
		float angle;
		bool isActive{ false };

		static bool isNotActive(Particle particle) { return !particle.isActive; }
	};

	class ParticleSystem : public GraphicsSystem
	{
	public:
		void Startup() override;
		void Shutdown() override;

		void Update(float dt) override;
		void Draw(Core::Graphics& graphics) override;

		void Create(const Vector2& position, size_t count, float lifetime, const Color& color, float speed);
		void Create(const Vector2& position, size_t count, float lifetime, const std::vector<ds::Color>& colors, float speed);
		void Create(const Vector2& position, size_t count, float lifetime, const std::vector<ds::Color>& colors, float speed, float angle, float angleRange);

	public:
		std::vector<Particle> particles;
	};
}