#pragma once
#include "Base/Actor.h"
#include <string>

class Projectile : public ds::Actor
{
public:
	Projectile(const ds::Transform& transform, std::shared_ptr<ds::Shape> shape, float speed) : ds::Actor{ transform, shape }, speed{ speed } {}

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

	float lifetime{ 2 };
	std::string type;
private:
	float speed{ 3000 };
};