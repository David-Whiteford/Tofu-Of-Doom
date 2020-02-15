#include "SplashScreen.h"

SplashScreen::SplashScreen(Game & t_game, sf::Font t_font) :
	m_game{ t_game },
	m_font{ t_font }
	
{
	//function call to set up content
	setUpContent();
}

SplashScreen::~SplashScreen()
{
}

void SplashScreen::update(sf::Time t_deltaTime)
{
	//timer count up
	if (m_timer != 900)
	{
		m_timer++;
	}
	else
	{
		//if its 900 then set to 0
		m_timer = 0;
	}
	if (m_continue == false)
	{
		//if the timer is between the numbers below then its white
		if (m_timer >= 0 && m_timer <= 100 || m_timer >= 200 && m_timer <= 300 || m_timer >= 400 && m_timer <= 500
			|| m_timer >= 600 && m_timer <= 700 || m_timer >= 800 && m_timer <= 900)
		{
			m_pressstartMessage.setFillColor(sf::Color::White);
		}
		//if the timer is between the numbers below then its yellow
		else if (m_timer >= 100 && m_timer <= 200 || m_timer >= 300 && m_timer <= 400 || m_timer >= 500 && m_timer <= 600
			|| m_timer >= 700 && m_timer <= 800)
		{
			m_pressstartMessage.setFillColor(sf::Color::Yellow);
		}
	}
	// if the start is preed then continue set transition to false
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_continue = true;
		
	}
	if (m_continue == true)
	{
		screenTransitionOff();
	}
}
/// <summary>
/// render to t_window
/// </summary>
/// <param name="t_window"></param>
void SplashScreen::render(sf::RenderWindow & t_window)
{

	t_window.clear(sf::Color::Black);
	//draw background sprite and all messages 
	t_window.draw(m_backgroundSprite);
	t_window.draw(m_pressstartMessage);
	t_window.draw(m_titleMessage);
	t_window.draw(m_titlemessageSecond);
	t_window.display();
}

void SplashScreen::setUpContent()
{

	//sets up the message for the press start message
	m_pressstartMessage.setFont(m_font);
	m_pressstartMessage.setPosition(165.0f, 500.0f);
	m_pressstartMessage.setString("Press Enter to continue");
	m_pressstartMessage.setCharacterSize(55);

	//sets up the message for the first title message
	m_titleMessage.setFont(m_font);
	m_titleMessage.setPosition(50.0f, 20.0f);
	m_titleMessage.setString(FIRST_TITLE_MESSAGE);
	m_titleMessage.setCharacterSize(85);

	//sets up the message for the second title message
	m_titlemessageSecond.setFont(m_font);
	m_titlemessageSecond.setPosition(80.0f, 100.0f);
	m_titlemessageSecond.setString(SECOND_TITLE_MESSAGE);
	m_titlemessageSecond.setCharacterSize(85);

	if (!m_backgroundTexture.loadFromFile("Splash.jpg"))
	{
		std::cout << "Cant load image " << std::endl;
	}
	m_backgroundSprite.setTexture(m_backgroundTexture);
	m_backgroundSprite.setPosition(0.0f, 0.0f);
	
	
}

void SplashScreen::screenTransitionOff()
{
	//if timer is less than 60 then increment
	if (transition_timer >= 0.0 && transition_timer <= 60.0f)
	{
		transition_timer++;
		//if timer is 5 then set the color of the sprite , and messages
		if (transition_timer == 5)
		{
			m_backgroundSprite.setColor(sf::Color(255, 255, 255, 255));
			m_titlemessageSecond.setFillColor(sf::Color(255, 255, 255, 255));
			m_titleMessage.setFillColor(sf::Color(255, 255, 255, 255));
			m_pressstartMessage.setFillColor(sf::Color(255, 255, 255, 255));
		}
		//if timer is 10 then set the color of the sprite , and messages
		else if (transition_timer == 10)
		{
			m_backgroundSprite.setColor(sf::Color(255, 255, 255, 200));
			m_titlemessageSecond.setFillColor(sf::Color(255, 255, 255, 200));
			m_titleMessage.setFillColor(sf::Color(255, 255, 255, 200));
			m_pressstartMessage.setFillColor(sf::Color(255, 255, 255, 200));
		}
		//if timer is 15 then set the color of the sprite , and messages
		else if (transition_timer == 15)
		{
			m_backgroundSprite.setColor(sf::Color(255, 255, 255, 150));
			m_titlemessageSecond.setFillColor(sf::Color(255, 255, 255, 150));
			m_titleMessage.setFillColor(sf::Color(255, 255, 255, 150));
			m_pressstartMessage.setFillColor(sf::Color(255, 255, 255, 150));
		}
		//if timer is 20 then set the color of the sprite , and messages
		else if (transition_timer == 20)
		{
			m_backgroundSprite.setColor(sf::Color(255, 255, 255, 100));
			m_titlemessageSecond.setFillColor(sf::Color(255, 255, 255, 100));
			m_titleMessage.setFillColor(sf::Color(255, 255, 255, 100));
			m_pressstartMessage.setFillColor(sf::Color(255, 255, 255, 100));
		}
		//if timer is 25 then set the color of the sprite , and messages
		else if (transition_timer == 25)
		{
			m_backgroundSprite.setColor(sf::Color(255, 255, 255, 50));
			m_titlemessageSecond.setFillColor(sf::Color(255, 255, 255, 50));
			m_titleMessage.setFillColor(sf::Color(255, 255, 255, 50));
			m_pressstartMessage.setFillColor(sf::Color(255, 255, 255, 50));
		}
		//if timer is 30 then set the color of the sprite , and messages
		else if (transition_timer == 30)
		{
			m_backgroundSprite.setColor(sf::Color(255, 255, 255, 0));
			m_titlemessageSecond.setFillColor(sf::Color(255, 255, 255, 0));
			m_titleMessage.setFillColor(sf::Color(255, 255, 255, 0));
			m_pressstartMessage.setFillColor(sf::Color(255, 255, 255, 0));
	
		}
		//changing the color above will cause a fade to black effect
		//if timer is 60 then set gamestate to licence
		else if (transition_timer == 60)
		{
			//m_game.m_currentGameState = GameState::Licence;
		}
	}
	
	

}