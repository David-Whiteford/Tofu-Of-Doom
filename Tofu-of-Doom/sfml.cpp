#include "SFML.h"

SFML::SFML(Game& t_game, sf::Font t_font, sf::Sprite t_sfmlSprite) :
	//initialiser list with sprite game and font
	m_sfmlSprite(t_sfmlSprite),
	m_game{ t_game },
	m_font{ t_font },
	m_animationState{ AnimationState::Appear }
{
	//function call to set up content
	setUpContent();

}

SFML::~SFML()
{
}



void SFML::update(sf::Time t_deltaTime)
{
	//screen animation function call
	screenAnimation();
}
/// <summary>
/// render to t_window
/// </summary>
/// <param name="t_window"></param>
void SFML::render(sf::RenderWindow& t_window)
{
	//render sprite , message and display
	t_window.clear(sf::Color::Black);
	t_window.draw(m_sfmlSprite);
	t_window.draw(m_licenceMessage);
	t_window.display();
}



void SFML::setUpContent()
{

	//sets up the message , color ,position ,string ,character size for the licence
	m_licenceMessage.setFont(m_font);
	m_licenceMessage.setFillColor(sf::Color::Green);
	m_licenceMessage.setPosition(850.0f, 100.0f);
	m_licenceMessage.setString(First_MESSAGE);
	m_licenceMessage.setCharacterSize(55);
	//set position of the sfml sprite
	m_sfmlSprite.setPosition(800.0f, 320.0f);

}
void SFML::screenAnimation()
{
	if (m_animationState == AnimationState::Appear)
	{
		if (m_cumulativeTime.asMilliseconds() < m_keyFrameLevel)
		{
			//decrement timer if not 0
			if (m_timer != 0)
			{
				m_timer--;
			}
			//move message to the left when its not 280 on x 
			if (m_licenceMessage.getPosition().x != 280.0f)
			{
				m_licenceMessage.setPosition(m_licenceMessage.getPosition() + sf::Vector2f{ -5.0f,0.0f });

			}
			//move sfml sprite to the left when its not 300 on x 
			if (m_sfmlSprite.getPosition().x != 300.0f)
			{
				m_sfmlSprite.setPosition(m_sfmlSprite.getPosition() + sf::Vector2f{ -4.0f , 0.0f });
			}
			//if timer is 0 then move sprite and message off the screen
			if (m_timer == 0)
			{
				m_sfmlSprite.setPosition(m_sfmlSprite.getPosition() + sf::Vector2f{ -5.0f , 0.0f });
				m_licenceMessage.setPosition(m_licenceMessage.getPosition() + sf::Vector2f{ -5.0f,0.0f });

			}
		}
	}
	//set the gamestate if the message is off screen
	if (m_licenceMessage.getPosition().x + 680 <= 0)
	{
		m_game.m_currentGameState = GameState::Main;
	}
}