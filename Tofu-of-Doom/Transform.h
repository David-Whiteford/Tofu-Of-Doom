#pragma once
#include <cmath>

#include "libs/glm/glm.hpp"
#include "libs/glm/gtc/matrix_transform.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

class Transform
{
	typedef struct Position
	{
		float x = 0;
		float y = 0;
		float z = 0;
	};


public:


	static float distance(Position& pos_1, Position& pos_2);
	//static float length(Position& pos);
	static float dotProduct(Position& pos_1, Position& pos_2);
	static float angleBetween(Position& pos_1, Position& pos_2);
	static float normalise(Position&);
	static Position moveTowards(Position t_position, Position t_targetPosition , float maxDistance);

	Position position;

	Transform();
	~Transform();

	void setPublicTransformToCentre(std::vector<glm::vec3> vertices);



private:
	Position realPosition;

};

