#ifndef PATROL_ENEMY_STATE_H
#define PATROL_ENEMY_STATE_H

#include "EnemyState.h"

class EnemyPatrolState : public EnemyState
{
public:
	//virtual EnemyState* handleInputs(Events& inputs);
	virtual void update();
	virtual void enter();
	virtual void exit();
};


#endif


