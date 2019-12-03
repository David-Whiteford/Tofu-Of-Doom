#ifndef ENEMY_STATE_H
#define ENEMY_STATE_H

#include "Events.h"


class EnemyState
{
	public:
		virtual ~EnemyState()
		{};
		virtual EnemyState handleInputs(Events&);
		virtual void update();
		virtual void enter();
		virtual void exit();

};


#endif // !ENEMY_STATE_H

