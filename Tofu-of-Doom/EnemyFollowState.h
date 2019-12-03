#ifndef FOLLOW_ENEMY_STATE_H
#define FOLLOW_ENEMY_STATE_H

#include "EnemyState.h"

class EnemyFollowState : public EnemyState
{
public:
	//virtual EnemyState* handleInputs(Events& inputs);
	virtual void update();
	virtual void enter();
	virtual void exit();
};


#endif

