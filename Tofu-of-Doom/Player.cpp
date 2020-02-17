#include "Player.h"

/// <summary>
/// Constructor for the Player class
/// </summary>
Player::Player()
{
	m_playerCircle.setRadius(25.0f);
	m_playerCircle.setFillColor(sf::Color::Blue);
	m_playerCircle.setOrigin(sf::Vector2f(25.0f, 25.0f));
}

/// <summary>
/// Destructor for the Player class
/// </summary>
Player::~Player()
{
	// Much like my sad life, this is empty....
}

/// <summary>
/// Get the player's position
/// </summary>
sf::Vector2f Player::getPosition()
{
	return m_position;
}

/// <summary>
/// Set player position (sf::Vector2f)
/// </summary>
void Player::setPosition(sf::Vector2f t_position)
{
	m_position = t_position;
}

/// <summary>
/// Set player position (float x and y)
/// </summary>
void Player::setPosition(float t_x, float t_y)
{
	m_position = sf::Vector2f(t_x, t_y);
}

/// <summary>
/// Get the player's current health
/// </summary>
int Player::getHealth()
{
	return m_health;
}

/// <summary>
/// Set the player's current health to an exact amount
/// </summary>
void Player::setHealth(int t_healthAmount)
{
	m_health = t_healthAmount;
}

/// <summary>
/// Increase the player's health by a specified amount
/// </summary>
void Player::increaseHealth(int t_healthAmount)
{
	m_health += t_healthAmount;

	if (m_health > 100)
	{
		m_health = 100;
	}
}

/// <summary>
/// Decrease the player's health by a specified amount
/// </summary>
void Player::decreaseHealth(int t_healthAmount)
{
	m_health -= t_healthAmount;

	if (m_health < 0)
	{
		m_health = 0;

		/////////////////////
		// PLAYER IS DEAD! //
		//    GAME OVER    //
		/////////////////////

		// Do the game over thing here
	}
}

void Player::init()
{
	m_health = 100;	
	currentHandGunBullets = 27;
	currentHandgunCLip = 9;
	currentShotGunShells = 10;
	currentShotGunClip = 5;
	currentMachineGunRounds = 100;
	currentMachineGunClip = 30;


}

/// <summary>
/// Get the player sprite
/// </summary>
sf::CircleShape Player::getSprite()
{
	return m_playerCircle;
}

/// <summary>
/// Get the player sprite
/// </summary>
void Player::update()
{
	m_playerCircle.setPosition(m_position);
}


