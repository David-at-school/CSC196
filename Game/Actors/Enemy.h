#pragma once
#include "Base/Actor.h"

class Enemy : public ds::Actor
{
public:
	Enemy() {}
	Enemy(const ds::Transform& transform, std::shared_ptr<ds::Shape> shape, float speed) : ds::Actor{ transform, shape }, speed{ speed } {}

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

private:
	float fireTimer{ 0 };
	float fireRate{ 0.2f };
	float speed{ 3000 };
};