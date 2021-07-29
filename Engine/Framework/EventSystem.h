#pragma once
#include "Base/System.h"
#include <string>
#include <functional>
#include <map>
#include <list>
#include <variant>

namespace ds
{
	struct Event
	{
		std::string name;
		std::variant<int, bool, float, std::string> data;
	};

	class EventSystem : public System
	{
	public:
		using function_t = std::function<void(const Event&)>;

		virtual void Startup() override;
		virtual void Shutdown() override;
		virtual void Update(float dt) override;

		void Subscribe(const std::string& name, function_t function);
		void Notify(const Event& e);

	private:
		struct Observer
		{
			function_t function;
		};

	private:
		std::map<std::string, std::list<Observer>> observers;
	};
}