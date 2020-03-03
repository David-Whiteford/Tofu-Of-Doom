#include "Pause.h"

PauseScreen::PauseScreen(Game& t_game, sf::Font t_font):
	m_game{ t_game },
	m_font{ t_font }
{

	setUpContent();
}

PauseScreen::~PauseScreen()
{
}

void PauseScreen::update(sf::Time t_deltaTime)
{
	if (m_controller.startButton() == true)
	{
		m_game.m_drawState = m_game.DrawState::GAME;
	}
	else if (m_controller.backButton() == true)
	{
		m_game.resetScreenTrans();
		m_game.m_drawState = m_game.DrawState::MAIN;
	}
}

void PauseScreen::render(sf::RenderWindow& t_window)
{
	t_window.clear(sf::Color::Black);
	//draw background sprite and all messages 
	t_window.draw(m_backgroundSprite);
	t_window.draw(m_pressstartMessage);
	t_window.draw(m_pressBackMessage);
	
	t_window.display();

}

void PauseScreen::setUpContent()
{
	if (!m_backgroundTexture.loadFromFile("images/bloodySplash.jpg"))
	{
		std::cout << "Can't load image!" << std::endl;
	}
	m_backgroundSprite.setTexture(m_backgroundTexture);
	m_backgroundSprite.setPosition(0.0f, 0.0f);
	//sets up the message for the first title message
	m_pressstartMessage.setFont(m_font);
	m_pressstartMessage.setPosition(200.0f, 200.0f);
	m_pressstartMessage.setString(PAUS_MESSAGE);
	m_pressstartMessage.setCharacterSize(85);
	m_pressstartMessage.setColor(sf::Color::Black);

	//sets up the message for the second title message
	m_pressBackMessage.setFont(m_font);
	m_pressBackMessage.setPosition(200.0f, 400.0f);
	m_pressBackMessage.setString(BACK_MESSAGE);
	m_pressBackMessage.setCharacterSize(85);
	m_pressBackMessage.setColor(sf::Color::Black);
}
