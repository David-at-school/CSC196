#pragma once
#include "Base/Actor.h"

class Player : public ds::Actor
{
public:
	Player(const ds::Transform& transform, std::shared_ptr<ds::Shape> shape, float speed);

	void Initialize() override;

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

private:
	float fireTimer{0};
	float secondaryTimer{ 0 };
	//float tertiaryTimer{ 0 };
	float fireRate{ 0.2f };
	float secondaryRate{ 1.0f };
	//float tertiaryRate{ 2.0f };

	float speed{ 300 };
	ds::Vector2 velocity;

	int lives = 3;
};