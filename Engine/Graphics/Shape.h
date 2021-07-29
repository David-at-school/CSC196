#pragma once
#include "Math/Vector2.h"
#include "Math/Color.h"
#include <Math/Transform.h>
#include "Framework/ResourceSystem.h"
#include <vector>
#include <string>

namespace ds
{
	class Shape : public Resource
	{
	public:
		Shape() {}
		Shape( const std::vector<Vector2>& points, const Color& color) : points{ points }, color{ color } 
		{
			ComputeRadius();
		}

		void Draw(Core::Graphics& graphics, const Vector2& position, float angle, float scale = 1);
		void Draw(Core::Graphics& graphics, const Transform& transform);

		bool Load(const std::string& filename);

	private:
		void ComputeRadius();
		void ComputeDimensions();

	public:

		std::vector<Vector2> points;
		Color color;
		float radius = 0;

		float leftBound = 0;
		float rightBound = 0;
		float upperBound = 0;
		float lowerBound = 0;
	};
}