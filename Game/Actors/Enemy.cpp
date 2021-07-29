#include "Enemy.h"
#include "Projectile.h"
#include "Player.h"
#include "Engine.h"

void Enemy::Update(float dt)
{
	if (scene->GetActor<Player>())
	{
		ds::Vector2 direction = scene->GetActor<Player>()->transform.position - transform.position;
		ds::Vector2 forward = ds::Vector2::Rotate(ds::Vector2::right, transform.rotation);

		float turnAngle = ds::Vector2::SignedAngle(forward, direction.Normalized());
		transform.rotation = transform.rotation + turnAngle * (3 *dt);

		float angle = ds::Vector2::Angle(direction.Normalized(), forward);

		fireTimer -= dt;
		if (fireTimer <= 0 && angle <= ds::QuarterPi / 4	)
		{
			fireTimer = 2.0f;

			std::vector<ds::Vector2> points = { {-5, -5}, {5, -5}, {0, 5}, {-5, -5} };
			std::shared_ptr<ds::Shape> shape = std::make_shared<ds::Shape>(points, ds::Color{ 0,0,1 });

			ds::Transform t = transform;
			t.scale = 0.5f;

			std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(t, shape, 200.0f);
			projectile->lifetime = 1;
			projectile->type = "projectile";
			projectile->tag = "Enemy";
			scene->AddActor(std::move(projectile));

			scene->engine->Get<ds::AudioSystem>()->PlayAudio("enemyFire");
		}
	}

	transform.position += ds::Vector2::Rotate(ds::Vector2::right, transform.rotation) * speed * dt;
	transform.position.x = ds::Wrap(transform.position.x, 0.0f, 1000.0f);
	transform.position.y = ds::Wrap(transform.position.y, 0.0f, 800.0f);

	Actor::Update(dt);
}

void Enemy::OnCollision(Actor* actor)
{
	if (dynamic_cast<Projectile*>(actor) && actor->tag == "Player")
	{
		destroy = true;
		actor->destroy = true;

		std::vector<ds::Color> colors = { ds::Color::white, ds::Color::red, ds::Color::orange };
		scene->engine->Get<ds::ParticleSystem>()->Create(transform.position, 100, 2, colors, 25);
		scene->engine->Get<ds::AudioSystem>()->PlayAudio("explosion");

		ds::Event event;
		event.name = "AddPoints";
		event.data = 300;
		scene->engine->Get<ds::EventSystem>()->Notify(event);
	}
	if (dynamic_cast<Player*>(actor))
	{
		destroy = true;

		std::vector<ds::Color> colors = { ds::Color::white, ds::Color::red, ds::Color::orange };
		scene->engine->Get<ds::ParticleSystem>()->Create(transform.position, 100, 2, colors, 25);
		scene->engine->Get<ds::AudioSystem>()->PlayAudio("explosion");

		ds::Event event;
		event.name = "AddPoints";
		event.data = 300;
		scene->engine->Get<ds::EventSystem>()->Notify(event);
	}
}
