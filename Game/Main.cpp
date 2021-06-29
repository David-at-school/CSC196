#include "Helper.h"
#include "Dynamic.h"
#include <iostream>

int main()
{
	std::cout << ds::sqr(5) << std::endl;

	ds::point p1(10, 10);
	ds::point p2(10, 10);
	ds::point p3 = p1 + p2;
	std::cout << p3.x << " " << p3.y << std::endl;

	system("pause");
}
