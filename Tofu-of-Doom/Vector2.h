#ifndef MYVECTOR3 
#define MYVECTOR3


/// 
/// David Whiteford
/// 

#include <iostream>
#include <SFML/Graphics.hpp>


class MyVector2
{
public:
	double x;
	double y;


	MyVector2();
	~MyVector2();

	MyVector2(double x, double y);
	bool operator == (const MyVector2 t_right) const;
	bool operator != (const MyVector2 t_right) const;

	MyVector2 operator +=(const MyVector2 t_right);
	MyVector2 operator -=(const MyVector2 t_right);


	// negative of a vector 
	MyVector2 operator -();
	double length()const;
	double lengthSquared()const;
	double dot(const MyVector2 t_other) const;
	//MyVector3 crossProduct(const MyVector3 t_other)const;
	double angleBetween(const MyVector2 t_other)const;
	MyVector2 unit() const;
	void normalise(); 
	MyVector2 projection(const MyVector2 t_other)const;
	// projection of other onto the current vector so answer will parralell to current vector.
	MyVector2 rejection(const MyVector2 t_other)const;

};



#endif // !MYVECTOR3
