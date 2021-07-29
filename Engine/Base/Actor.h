#pragma once
#include "Object.h"
#include "Math/Transform.h"
#include "core.h"
#include <memory>
#include <vector>

namespace ds
{
	class Shape;
	class Scene;

	class Actor : public  Object
	{
	public:
		Actor() {}
		Actor(const Transform& transform, std::shared_ptr<Shape> shape = {}) : transform{ transform }, shape{ shape } {}

		virtual void Initialize() {};

		virtual void Update(float dt);
		virtual void Draw(Core::Graphics& graphics);

		virtual void OnCollision(Actor* actor);
		void AddChild(std::unique_ptr<Actor> actor);

		float GetRadius();

	public:
		bool destroy{false};
		std::string tag;

		Transform transform;
		std::shared_ptr<Shape> shape;
		Scene* scene{ nullptr};

		Actor* parent{ nullptr };
		std::vector<std::unique_ptr<Actor>> children;

		float localLeftBound = 0;
		float localRightBound = 0;
		float localUpperBound = 0;
		float localLowerBound = 0;
	};
}