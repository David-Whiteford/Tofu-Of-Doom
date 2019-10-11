#pragma once
#include <cmath>


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

		Position position;

		Transform();
		~Transform();
		

	};

	