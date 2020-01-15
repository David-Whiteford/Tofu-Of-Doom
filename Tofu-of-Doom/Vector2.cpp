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

double MyVector2::length() const
{
	//math to determine the lenght of the vector
	const double answer = std::sqrt(x * x + y * y);
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

void MyVector2::normalise()
{
	double vecLength = length();

	if (vecLength != 0.0)
	{
		
		x = x / vecLength;
		y = y / vecLength;
		
	}
}

MyVector2 MyVector2::projection(const MyVector2 t_other) const
{
	return MyVector2();
}

MyVector2 MyVector2::rejection(const MyVector2 t_other) const
{
	return MyVector2();
}
