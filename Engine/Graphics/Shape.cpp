#include "Shape.h"
#include <fstream>

void ds::Shape::Draw(Core::Graphics& graphics, const Vector2& position, float angle, float scale)
{
	graphics.SetColor(color);
	for (size_t i = 0; i < points.size() - 1; i++)
	{
		ds::Vector2 p1 = position + (Vector2::Rotate(points[i], angle) * scale);// +Vector2{ rand() % 10 - 5, rand() % 10 - 5 };
		ds::Vector2 p2 = position + (Vector2::Rotate(points[i + 1], angle) * scale);// +Vector2{ rand() % 10 - 5, rand() % 10 - 5 };
		graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}

void ds::Shape::Draw(Core::Graphics& graphics, const Transform& transform)
{
	graphics.SetColor(color);
	for (size_t i = 0; i < points.size() - 1; i++)
	{
		ds::Vector2 p1 = transform.matrix * points[i];// +Vector2{ rand() % 10 - 5, rand() % 10 - 5 };
		ds::Vector2 p2 = transform.matrix * points[i + 1];// +Vector2{ rand() % 10 - 5, rand() % 10 - 5 };
		
		graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}

bool ds::Shape::Load(const std::string& filename)
{
	bool success = false;

	std::ifstream stream(filename);
	if (stream.is_open())
	{
 		success = true;

		stream >> color;

		std::string line;
		std::getline(stream, line);
		size_t size = std::stoi(line);

		for (size_t i = 0; i < size; i++)
		{
			ds::Vector2 point;
			stream >> point;

			points.push_back(point);
		}

		ComputeRadius();
		ComputeDimensions();
	}

	return success;
}

void ds::Shape::ComputeRadius()
{
	for (auto& point : points)
	{
		radius = std::max(radius, point.Length());
	}
}

void ds::Shape::ComputeDimensions()
{
	for (auto& point : points)
	{
		leftBound = std::min(leftBound, point.x);
		rightBound = std::max(rightBound, point.x);
		upperBound = std::min(upperBound, point.y);
		lowerBound = std::max(lowerBound, point.y);
	}
}
