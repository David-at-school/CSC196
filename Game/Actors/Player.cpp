#include "Player.h"
#include "Enemy.h"
#include "Math/MathUtils.h"
#include "Projectile.h"
#include "Missile.h"
#include "Bullet.h"
#include "Engine.h"
#include <memory>

Player::Player(const ds::Transform& transform, std::shared_ptr<ds::Shape> shape, float speed) : ds::Actor{ transform, shape }, speed{ speed } 
{
	
}

void Player::Initialize()
{
	std::unique_ptr locator = std::make_unique<Actor>();
	locator->transform.localPosition = ds::Vector2{ 8,0 };
	AddChild(std::move(locator));

	locator = std::make_unique<Actor>();
	locator->transform.localPosition = ds::Vector2{ 0,5 };
	AddChild(std::move(locator));

	locator = std::make_unique<Actor>();
	locator->transform.localPosition = ds::Vector2{ 0,-5 };
	AddChild(std::move(locator));
	
	locator = std::make_unique<Actor>();
	locator->transform.localPosition = ds::Vector2{ -8,0 };
	locator->transform.localRotation = ds::Pi;
	AddChild(std::move(locator));

	std::unique_ptr turret = std::make_unique<Actor>(ds::Transform{}, scene->engine->Get<ds::ResourceSystem>()->Get<ds::Shape>("turret.txt"));
	turret->transform.localPosition = ds::Vector2{ 8,0 };
	AddChild(std::move(turret));
}

void Player::Update(float dt)
{	
	//independant rotation
	children[4]->transform.localRotation += 5 * dt;

	//controls
	float thrust = 0;
	ds::Vector2 acceleration;

	if (Core::Input::IsPressed('W')) transform.position.y -= speed * dt;
	if (Core::Input::IsPressed('A')) transform.position.x -= speed * dt;
	if (Core::Input::IsPressed('S')) transform.position.y += speed * dt;
	if (Core::Input::IsPressed('D')) transform.position.x += speed * dt;

	if (Core::Input::IsPressed(VK_LSHIFT)) thrust *= 10;

	//rotation
	int x, y;
	Core::Input::GetMousePos(x, y);
	ds::Vector2 mouseLocation{ x, y };

	transform.rotation = std::atan2(mouseLocation.y - transform.position.y, mouseLocation.x - transform.position.x);

	//wrapping
	transform.position.x = ds::Wrap(transform.position.x, 0.0f, 1000.0f);
	transform.position.y = ds::Wrap(transform.position.y, 0.0f, 800.0f);

	// fire
	fireTimer -= dt;
	secondaryTimer -= dt;
	if (fireTimer <= 0 && Core::Input::IsPressed(VK_LBUTTON))
	{
		fireTimer = 0.25f;

		ds::Transform t = children[0]->transform;
		t.scale = 2.0f;

		std::unique_ptr<Bullet> projectile = std::make_unique<Bullet>(t, scene->engine->Get<ds::ResourceSystem>()->Get<ds::Shape>("bullet.txt"), 600.0f);
		projectile->tag = "Player";
		projectile->type = "bullet";
		scene->AddActor(std::move(projectile));

		scene->engine->Get<ds::AudioSystem>()->PlayAudio("playerFire");
	}

	if (secondaryTimer <= 0 && Core::Input::IsPressed(VK_RBUTTON))
	{
		secondaryTimer = 0.25f;

		ds::Transform t = children[0]->transform;
		t.scale = 5.0f;

		std::unique_ptr<Missile> projectile = std::make_unique<Missile>(t, scene->engine->Get<ds::ResourceSystem>()->Get<ds::Shape>("missile.txt"), 500.0f);
		projectile->lifetime = 1;
		projectile->type = "missile";
		projectile->tag = "Player";
		scene->AddActor(std::move(projectile));

		scene->engine->Get<ds::AudioSystem>()->PlayAudio("playerFire");
	}

	std::vector<ds::Color> colors = { ds::Color::white, ds::Color::red, ds::Color::blue, ds::Color::green, ds::Color::purple, ds::Color::cyan, ds::Color::orange };
	//scene->engine->Get<ds::ParticleSystem>()->Create(transform.position, 1, 5, colors, 25);
	scene->engine->Get<ds::ParticleSystem>()->Create(children[3]->transform.position, 1, 5, colors, 20, children[3]->transform.rotation, ds::DegToRad(15));

	Actor::Update(dt);
}

void Player::OnCollision(Actor* actor)
{
	if (dynamic_cast<Enemy*>(actor) || (dynamic_cast<Projectile*>(actor) && actor->tag == "Enemy"))
	{
		actor->destroy = true;
		ds::Event event;
		event.name = "PlayerDead";
		event.data = std::string("You... are... dead.");
		scene->engine->Get<ds::EventSystem>()->Notify(event);
		lives--;
		if (lives == 0)
		{
			destroy = true;

			std::vector<ds::Color> colors = { ds::Color::white, ds::Color::red, ds::Color::orange };
			scene->engine->Get<ds::ParticleSystem>()->Create(transform.position, 5000, 5, colors, 250);
			scene->engine->Get<ds::AudioSystem>()->PlayAudio("explosion");

		}
	}
}