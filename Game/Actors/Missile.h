#pragma once
#include "Projectile.h"

class Missile : public Projectile
{
public:
	Missile(const ds::Transform& transform, std::shared_ptr<ds::Shape> shape, float speed) : Projectile{ transform, shape, speed } {}

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

	float lifetime{ 1 };
	std::string type;
private:
	float speed{ 500 };
};