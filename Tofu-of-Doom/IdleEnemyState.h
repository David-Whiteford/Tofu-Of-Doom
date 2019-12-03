#ifndef IDLE_ENEMY_STATE_H
#define IDLE_ENEMY_STATE_H

#include "EnemyState.h"

class EnemyIdleState : public EnemyState
{
public:
	//virtual EnemyState* handleInputs(Events& inputs);
	virtual void update();
	virtual void enter();
	virtual void exit();
};


#endif

