#include "Actor.h"
#include "Graphics/Shape.h"

namespace ds
{
	void Actor::Update(float dt)
	{
		transform.Update();
		std::for_each(children.begin(), children.end(), [](auto& child) { child->transform.Update(child->parent->transform.matrix); });
	}

	void Actor::Draw(Core::Graphics& graphics)
	{
		if (shape)
		{
			localLeftBound = shape->leftBound * transform.scale.x + transform.position.x;
			localRightBound = shape->rightBound * transform.scale.x + transform.position.x;
			localUpperBound = shape->upperBound * transform.scale.y + transform.position.x;
			localLowerBound = shape->lowerBound * transform.scale.y + transform.position.y;
			shape->Draw(graphics, transform);
		}

		std::for_each(children.begin(), children.end(), [graphics](auto& child) mutable { if (child->shape) child->shape->Draw(graphics, child->transform); });
	}

	void Actor::OnCollision(Actor* actor)
	{

	}

	void Actor::AddChild(std::unique_ptr<Actor> actor)
	{
		actor->parent = this;

		children.push_back(std::move(actor));
	}

	float Actor::GetRadius()
	{
		return shape->radius * transform.scale.x;
	}
}