#include "Projectile.h"
#include "Engine.h"

void Projectile::Update(float dt)
{
	lifetime -= dt;
	destroy = (lifetime <= 0);

	transform.position += ds::Vector2::Rotate(ds::Vector2::right, transform.rotation) * speed * dt;
	transform.position.x = ds::Wrap(transform.position.x, 0.0f, 1000.0f);
	transform.position.y = ds::Wrap(transform.position.y, 0.0f, 800.0f);

	std::vector<ds::Color> colors = { ds::Color::white, ds::Color::red, ds::Color::blue, ds::Color::green, ds::Color::purple, ds::Color::cyan, ds::Color::orange };
	scene->engine->Get<ds::ParticleSystem>()->Create(transform.position, 1, 1, colors, 1);

	Actor::Update(dt);
}

void Projectile::OnCollision(Actor* actor)
{
	
}
