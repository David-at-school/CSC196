#include "Game.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Actors/Projectile.h"

void Game::Initialize()
{
	engine = std::make_unique<ds::Engine>();
	engine->Startup();
	scene = std::make_unique<ds::Scene>();
	scene->engine = engine.get();

	engine->Get<ds::AudioSystem>()->AddAudio("explosion", "explosion.wav");
	engine->Get<ds::AudioSystem>()->AddAudio("enemyFire", "enemyFire.wav");
	engine->Get<ds::AudioSystem>()->AddAudio("playerFire", "playerFire.wav");

	engine->Get<ds::EventSystem>()->Subscribe("AddPoints", std::bind(&Game::OnAddPoints, this, std::placeholders::_1));
	engine->Get<ds::EventSystem>()->Subscribe("PlayerDead", std::bind(&Game::OnPlayerDead, this, std::placeholders::_1));
}

void Game::Shutdown()
{
	scene->RemoveAllActors();
	engine->Shutdown();
}

void Game::Update(float dt)
{
	stateTimer += dt;

	switch (state)
	{
	case Game::eState::Title:
		if (Core::Input::IsPressed(VK_SPACE))
		{
			state = eState::StartGame;
		}
		break;
	case Game::eState::StartGame:
		score = 0;
		lives = 3;
		state = eState::StartLevel;
		break;
	case Game::eState::StartLevel:
	{
		UpdateStartLevel(dt);
		state = eState::Game;
	}
		break;
	case Game::eState::Game:
		if (scene->GetActors<Enemy>().size() == 0)
		{
			enemyCount += 1;
			int countRemaining = enemyCount;
			for (size_t i = 0; i < ds::RandomRangeInt(0, enemyCount); i++)
			{
				countRemaining -= 1;
				scene->AddActor(std::make_unique<Enemy>(ds::Transform{ ds::Vector2{ds::RandomRange(0,1000), ds::RandomRange(0,800)}, ds::RandomRange(0, ds::TwoPi), 2 }, engine->Get<ds::ResourceSystem>()->Get<ds::Shape>("hunter.txt"), 150.0f));
			}
			if (countRemaining != 0)
			{
				for (size_t i = 0; i < countRemaining; i++)
				{
					scene->AddActor(std::make_unique<Enemy>(ds::Transform{ ds::Vector2{ds::RandomRange(0,1000), ds::RandomRange(0,800)}, ds::RandomRange(0, ds::TwoPi), 2 }, engine->Get<ds::ResourceSystem>()->Get<ds::Shape>("tracker.txt"), 100.0f));
				}
			}
		}
		break;
	case Game::eState::GameOver:
		break;
	default:
		break;
	}

	engine->Update(dt);
	scene->Update(dt);
}

void Game::Draw(Core::Graphics& graphics)
{
	switch (state)
	{
	case Game::eState::Title:
		lives = 3;
		score = 0;
		graphics.SetColor(ds::Color::blue);
		graphics.DrawString(400 + 400 * std::cos(stateTimer), 300 + 300 * std::sin(stateTimer), "Better Assassin's Creed");

		graphics.DrawString(410, 450, "Press Space to Start");
		break;
	case Game::eState::StartGame:
		break;
	case Game::eState::StartLevel:
		break;
	case Game::eState::Game:

		break;
	case Game::eState::GameOver:
		graphics.SetColor(ds::Color::red);
		graphics.DrawString(410, 450, "GAME OVER");
		scene->RemoveAllActors();
		state = eState::Title;
		break;
	default:
		break;
	}

	graphics.SetColor(ds::Color::white);
	graphics.DrawString(10, 10, std::to_string(score).c_str());
	graphics.DrawString(10, 20, std::to_string(lives).c_str());

	scene->Draw(graphics);
	engine->Get<ds::ParticleSystem>()->Draw(graphics);

}

void Game::UpdateTitle(float dt)
{
	if (Core::Input::IsPressed(VK_SPACE))
	{
		stateFunction = &Game::UpdateStartLevel;
		//state = eState::StartGame;
	}
}

void Game::UpdateStartLevel(float dt)
{
	scene->AddActor(std::make_unique<Player>(ds::Transform{ ds::Vector2{500, 750}, 0, 3 }, engine->Get<ds::ResourceSystem>()->Get<ds::Shape>("player.txt"), 500.0f));
	for (size_t i = 0; i < 10; i++)
	{
		scene->AddActor(std::make_unique<Enemy>(ds::Transform{ ds::Vector2{ds::RandomRange(0,1000), ds::RandomRange(0,800)}, ds::RandomRange(0, ds::TwoPi), 2 }, engine->Get<ds::ResourceSystem>()->Get<ds::Shape>("hunter.txt"), 100.0f));
	}
}

void Game::OnAddPoints(const ds::Event& event)
{
	score += std::get<int>(event.data);
}

void Game::OnPlayerDead(const ds::Event& event)
{
	lives -= 1;
	std::cout << std::get<std::string>(event.data) << std::endl;
	if (lives == 0)
	{ 
		state = eState::GameOver;
	}
}
