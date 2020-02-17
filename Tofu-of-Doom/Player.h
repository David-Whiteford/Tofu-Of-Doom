#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>
class Player
{
public:
	Player();
	~Player();
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f t_position);
	void setPosition(float t_x, float t_y);
	int getHealth();
	void setHealth(int t_healthAmount);
	void increaseHealth(int t_healthAmount);
	void decreaseHealth(int t_healthAmount);
	sf::CircleShape getSprite();
	void update();

	// Handgun
	int getCurrentHandGunClip() { return currentHandgunCLip; }
	int getCurrentHandGunBullets() { return currentHandGunBullets; }
	
	void reduceCurrentGunClip(int _gunType) 
	{ 
		if (_gunType == 1)
		{
			currentHandgunCLip--;
		}
		else if (_gunType == 2)
		{
			currentShotGunClip--;
		}
		else
		{
			currentMachineGunClip--;
		}
	}

	// Shot Gun
	int getCurrentShotGunClip() { return currentShotGunClip; }
	int getCurrentShotGunBullets() { return currentShotGunShells; }

	// Machine Gun
	int getCurrentMachineGunClip() { return currentMachineGunClip; }
	int getCurrentMachineGunBullets() { return currentMachineGunRounds; }


private:
	sf::CircleShape m_playerCircle;
	int m_health{ 100 };
	sf::Vector2f m_position;

	int currentHandGunBullets = 40, currentHandgunCLip = 7, currentShotGunShells = 12, currentShotGunClip = 3, currentMachineGunRounds= 320, currentMachineGunClip = 30;
};

#endif // !PLAYER_H
