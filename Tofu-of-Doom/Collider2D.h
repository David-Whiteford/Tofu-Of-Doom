#pragma once


class Collider2D
{
public:
	typedef struct Bounds
	{
		float x1;
		float y1;
		float x2;
		float y2;
	};
	
	Collider2D();
	~Collider2D();
	// Compares if two bounds are overlapping
	static bool isColliding(Bounds bounds1, Bounds bounds2);

	void updateBounds(float xPos, float yPos);

	Bounds bounds;
};