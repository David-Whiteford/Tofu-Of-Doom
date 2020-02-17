#include "EnemyBullet.h"

void EnemyBullet::init(sf::Vector2f pos, sf::Vector2f dir)
{
	bullet.setPosition(pos);
	direction = dir;
	active = true;
	life = 0;
}

void EnemyBullet::update()
{
	bullet.setPosition(bullet.getPosition() + ((direction) * speed));
	life++;
	if (life > 600)
	{
		life = 0;
		active = false;
	}
}

EnemyBullet::EnemyBullet()
{
	bullet.setRadius(14);
}

EnemyBullet::~EnemyBullet()
{
}
