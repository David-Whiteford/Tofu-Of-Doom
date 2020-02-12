#include "GameOver.h"

GameOver::GameOver(Game & t_game, sf::Font t_font) :
	m_game{ t_game },
	m_font{ t_font }

{
	//function to set up content
	setUpContent();

}

GameOver::~GameOver()
{
}

int GameOver::update(int t_score, sf::Time dt ,sf::Event &event)
{
	timers(dt);
	nameInput(t_score);

	//if the button for back is pressed then set gamestate to high score
	if (sf::Joystick::isButtonPressed(0, 6))
	{

		m_game.m_currentGameState = GameState::Main;

	}

}


/// render to t_window
/// </summary>
/// <param name="t_window"></param>
void GameOver::render(sf::RenderWindow & t_window)
{

	t_window.clear(sf::Color::Black);
	//draw sprite
	t_window.draw(m_sprite);
	//draws all text messages
	t_window.draw(m_playerscoreText);
	t_window.draw(m_playernameText);
	t_window.draw(m_restartgameTxt);
	//draw arrow
	t_window.draw(m_arrowSprite);
	//draw player name text
	t_window.draw(m_playersname);
	//draw outline rect
	t_window.draw(m_outline);
	t_window.display();
}
void GameOver::setUpContent()
{
	//loads the texture
	if (!m_texture.loadFromFile("ASSETS\\IMAGES\\gameOver1.png"))
	{sf::Text m_scoreList;
		std::cout << "Cant load sfml image " << std::endl;
	}
	//sets the pos and texture 
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(50.0f, -50.0f);
	//loads the arrow texture 
	if (!m_arrowTexture.loadFromFile("ASSETS\\IMAGES\\arrow.jpg"))
	{
		sf::Text m_scoreList;
		std::cout << "Cant load sfml image " << std::endl;
	}

	//set the texture and position of the arrow and rotate it
	m_arrowSprite.setTexture(m_arrowTexture);
	m_arrowSprite.setPosition(655.0f, 400.0f);
	m_arrowSprite.rotate(180);
}


void GameOver::timers(sf::Time dt)
{
	//if the timer is greater or equal to 0 and less than 0.5
	if (m_timer >= sf::seconds(0.0f) && m_timer <= sf::seconds(0.5f))
	{
		//add deltatimer to timerr
		m_timer += dt;
	}
	else
	{
		//set moved to false and set timer to 0
		m_moved = false;
		m_timer = sf::seconds(0.0f);
	}
	//if the name timer is greater or equal to 0 and less than 0.5
	if (m_nameTimer >= sf::seconds(0.0f) && m_timer <= sf::seconds(0.5f))
	{
		//add deltatimer to name timerr
		m_nameTimer += dt;
	}
	else
	{	//set name moved to false and set name timer to 0
		m_nameMoved = false;
		m_nameTimer = sf::seconds(0.0f);
	}

}
void GameOver::nameInput(int t_score)
{
	//right movement of the dpad
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && m_moved == false)
	{
		//set i to 0 and moved to true
		i = 0;
		m_moved = true;
		//decrement if name index is less than or equal to 0
		if (m_charNameIndex <= 6)
		{
			m_charNameIndex++;
		}
		///if the position of the arrow is not 790 then sets its 
		/// position to its position plus 27
		/// do not change y pos
		/// </summary>
		if (m_arrowSprite.getPosition().x != 790.0f)
		{
			m_arrowSprite.setPosition(m_arrowSprite.getPosition().x + 27.0f, 400.0f);
		}

	}
	//left movement of the dpad
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && m_moved == false)
	{
		//set i to 0 and moved to true
		i = 0;
		m_moved = true;
		//decrement if name index is greater than or equakl to 0
		if (m_charNameIndex >= 0)
		{
			m_charNameIndex--;
		}
		///if the position of the arrow is not 655 then sets its 
		/// position to its position minus 27
		/// do not change y pos
		/// </summary>
		if (m_arrowSprite.getPosition().x != 655.0f)
		{
			m_arrowSprite.setPosition(m_arrowSprite.getPosition().x - 27.0f, 400.0f);
		}

	}

}
