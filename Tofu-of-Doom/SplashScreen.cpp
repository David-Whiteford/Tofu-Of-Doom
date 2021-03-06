#include "SplashScreen.h"

SplashScreen::SplashScreen(Game& t_game, sf::Font t_font) :
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
			m_pressstartMessage.setColor(sf::Color::Black);
		}
		//if the timer is between the numbers below then its yellow
		else
		{
			m_pressstartMessage.setFillColor(sf::Color::Red);
		}
	}
	// if the start is preed then continue set transition to false
	if (m_controller.startButton() == true)
	{
		m_continue = true;

	}
	if (m_continue == true)
	{
		screenTransitionOn(t_deltaTime);
	}


	if (m_transition == true)
	{
		m_game.resetScreenTrans();
		m_game.m_drawState = m_game.DrawState::MAIN;
	}

}
/// <summary>
/// render to t_window
/// </summary>
/// <param name="t_window"></param>
void SplashScreen::render(sf::RenderWindow& t_window)
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
	m_pressstartMessage.setPosition(800.0f, 500.0f);
	m_pressstartMessage.setString("Press START to continue");
	m_pressstartMessage.setCharacterSize(55);

	//sets up the message for the first title message
	m_titleMessage.setFont(m_font);
	m_titleMessage.setPosition(800.0f, 100.0f);
	m_titleMessage.setString(FIRST_TITLE_MESSAGE);
	m_titleMessage.setCharacterSize(85);

	//sets up the message for the second title message
	m_titlemessageSecond.setFont(m_font);
	m_titlemessageSecond.setPosition(820.0f, 180.0f);
	m_titlemessageSecond.setString(SECOND_TITLE_MESSAGE);
	m_titlemessageSecond.setCharacterSize(85);

	m_titlemessageSecond.setColor(sf::Color::Black);
	m_titleMessage.setColor(sf::Color::Black);
	

	if (!m_backgroundTexture.loadFromFile("images/bloodySplash.jpg"))
	{
		std::cout << "Can't load image!" << std::endl;
	}
	m_backgroundSprite.setTexture(m_backgroundTexture);
	m_backgroundSprite.setPosition(0.0f, 0.0f);


}

void SplashScreen::screenTransitionOn(sf::Time t_deltaTime)
{

	if (transitionTimer >= sf::seconds(0.0) && transitionTimer <= sf::seconds(4.0f))
	{
		//increment timer
		transitionTimer += t_deltaTime;
		
		m_backgroundSprite.setColor(sf::Color(255, 255, 255, m_backgroundSprite.getColor().a - 1));
		m_titlemessageSecond.setColor(sf::Color(m_titlemessageSecond.getColor().r
			,m_titlemessageSecond.getColor().g, m_titlemessageSecond.getColor().b
			, m_titlemessageSecond.getColor().a - 1));

		m_titleMessage.setColor(sf::Color(m_titleMessage.getColor().r
			, m_titleMessage.getColor().g, m_titleMessage.getColor().b
			, m_titleMessage.getColor().a - 1));

		m_pressstartMessage.setColor(sf::Color(m_pressstartMessage.getColor().r
			, m_pressstartMessage.getColor().g, m_pressstartMessage.getColor().b
			, m_pressstartMessage .getColor().a - 1));

		

	}
	else if (transitionTimer >= sf::seconds(4.0f))
	{
		m_continue = false;
		m_transition = true;
	}



}