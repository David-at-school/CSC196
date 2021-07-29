#pragma once
#include "Projectile.h"

class Bullet : public Projectile
{
public:
	Bullet(const ds::Transform& transform, std::shared_ptr<ds::Shape> shape, float speed) : Projectile{ transform, shape, speed } {}

	float lifetime{ 1 };
	std::string type;
private:
	float speed{ 500 };
};