#ifndef MYVECTOR2
#define MYVECTOR2

#include <iostream>
#include <SFML/Graphics.hpp>


class MyVector2
{
public:
	double x;
	double y;


	MyVector2();
	~MyVector2();

	void normalise();

};



#endif 