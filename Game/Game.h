#pragma once
#include "Engine.h"

class Game
{
public:
	enum class eState
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		GameOver
	};

public:
	void Initialize();
	void Shutdown();

	void Update(float dt);
	void Draw(Core::Graphics& graphics);

private:
	void UpdateTitle(float dt);
	void UpdateStartLevel(float dt);
	void OnAddPoints(const ds::Event& event);
	void OnPlayerDead(const ds::Event& event);

public:
	std::unique_ptr<ds::Engine> engine;
	std::unique_ptr<ds::Scene> scene;

private:
	eState state = eState::Title;
	float stateTimer = 0.0f;
	unsigned int enemyCount = 10;

	void (Game::* stateFunction)(float) = nullptr;

	size_t score = 0;
	size_t lives = 0;
};