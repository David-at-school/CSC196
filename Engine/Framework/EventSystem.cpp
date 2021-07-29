#include "EventSystem.h"

namespace ds
{
	void EventSystem::Startup()
	{

	}

	void EventSystem::Shutdown()
	{

	}

	void EventSystem::Update(float dt)
	{

	}

	void EventSystem::Subscribe(const std::string& name, function_t function)
	{
		Observer observer;
		observer.function = function;
		observers[name].push_back(observer);
	}

	void EventSystem::Notify(const Event& e)
	{
		auto& eventObservers = observers[e.name];
		for (auto& observer : eventObservers)
		{
			observer.function(e);
		}
	}
}