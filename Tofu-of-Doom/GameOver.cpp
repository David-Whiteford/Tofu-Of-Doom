#include "GameOver.h"

GameOver::GameOver(Game& t_game, sf::Font t_font) :
	m_game{ t_game },
	m_font{ t_font }

{
	//function call to set up content
	setUpContent();
}

GameOver::~GameOver()
{
}

void GameOver::update(sf::Time t_deltaTime)
{

	if (screenTimer >= sf::seconds(0.0) && screenTimer <= sf::seconds(3.0f))
	{
		//increment timer
		screenTimer += t_deltaTime;
		
	}
	else if (screenTimer >= sf::seconds(2.9f))
	{
		screenTransitionOn(t_deltaTime);
	}
	
}
/// <summary>
/// render to t_window
/// </summary>
/// <param name="t_window"></param>
void GameOver::render(sf::RenderWindow& t_window)
{

	t_window.clear(sf::Color::Black);
	//draw background sprite and all messages 
	t_window.draw(m_backgroundSprite);
	t_window.draw(m_titleMessage);
	t_window.draw(m_titlemessageSecond);
	t_window.display();
}

void GameOver::setUpContent()
{
	//sets up the message for the first title message
	m_titleMessage.setFont(m_font);
	m_titleMessage.setPosition(150.0f, 450.0f);
	m_titleMessage.setString(FIRST_TITLE_MESSAGE);
	m_titleMessage.setCharacterSize(85);

	//sets up the message for the second title message
	m_titlemessageSecond.setFont(m_font);
	m_titlemessageSecond.setPosition(170.0f, 530.0f);
	m_titlemessageSecond.setString(SECOND_TITLE_MESSAGE);
	m_titlemessageSecond.setCharacterSize(85);

	m_titlemessageSecond.setColor(sf::Color::Red);
	m_titleMessage.setColor(sf::Color::Red);
	if (!m_backgroundTexture.loadFromFile("images/YouDied.jpg"))
	{
		std::cout << "Can't load image!" << std::endl;
	}
	m_backgroundSprite.setTexture(m_backgroundTexture);
	m_backgroundSprite.setPosition(0.0f, 0.0f);


}

void GameOver::screenTransitionOn(sf::Time t_deltaTime)
{

	if (transitionTimer >= sf::seconds(0.0) && transitionTimer <= sf::seconds(4.0f))
	{
		//increment timer
		transitionTimer += t_deltaTime;
		m_backgroundSprite.setColor(sf::Color(255, 255, 255, m_backgroundSprite.getColor().a - 1));

		m_titlemessageSecond.setColor(sf::Color(m_titlemessageSecond.getColor().r
			, m_titlemessageSecond.getColor().g, m_titlemessageSecond.getColor().b
			, m_titlemessageSecond.getColor().a - 1));

		m_titleMessage.setColor(sf::Color(m_titleMessage.getColor().r
			, m_titleMessage.getColor().g, m_titleMessage.getColor().b
			, m_titleMessage.getColor().a - 1));

	}
	else if (transitionTimer >= sf::seconds(4.0f))
	{
		m_game.resetScreenTrans();
		m_game.m_drawState = m_game.DrawState::MAIN;
	}
}

void GameOver::resetTime()
{
	screenTimer = sf::seconds(0.0);
	transitionTimer = sf::seconds(0.0);
}

void GameOver::setFontText(sf::Font t_font, std::string FIRST_TITLE_MESSAGE, sf::Sprite t_backgroundSprite)
{
	m_font = t_font;
	m_titleMessage.setString(FIRST_TITLE_MESSAGE);
	m_titlemessageSecond.setString(SECOND_TITLE_MESSAGE);
	m_backgroundSprite = t_backgroundSprite;

}
