#include "Vector2.h"

MyVector2::MyVector2()
{
}

MyVector2::~MyVector2()
{
}

MyVector2::MyVector2(double x, double y)
{
}

bool MyVector2::operator==(const MyVector2 t_right) const
{
	return false;
}

bool MyVector2::operator!=(const MyVector2 t_right) const
{
	return false;
}

MyVector2 MyVector2::operator+=(const MyVector2 t_right)
{
	return MyVector2();
}

MyVector2 MyVector2::operator-=(const MyVector2 t_right)
{
	return MyVector2();
}

MyVector2 MyVector2::operator-()
{
	return MyVector2();
}

double MyVector2::length(sf::Vector2f t_pos) const
{
	//math to determine the lenght of the vector
	const double answer = std::sqrt(t_pos.x * t_pos.x + t_pos.y * t_pos.y);
	return answer;
}

double MyVector2::lengthSquared() const
{
	return 0.0;
}

double MyVector2::dot(const MyVector2 t_other) const
{
	return 0.0;
}

double MyVector2::angleBetween(const MyVector2 t_other) const
{
	return 0.0;
}

MyVector2 MyVector2::unit() const
{
	return MyVector2();
}

sf::Vector2f MyVector2::normalise(sf::Vector2f t_pos)
{
	double vecLength = length(t_pos);

	if (vecLength != 0.0)
	{
		
		t_pos.x = t_pos.x / vecLength;
		t_pos.y = t_pos.y / vecLength;
		
	}
	return t_pos;
}

MyVector2 MyVector2::projection(const MyVector2 t_other) const
{
	return MyVector2();
}

MyVector2 MyVector2::rejection(const MyVector2 t_other) const
{
	return MyVector2();
}
