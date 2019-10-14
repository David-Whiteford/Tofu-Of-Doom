#include "Game.h"

static double const MS_PER_UPDATE = 10.0;
Game::Game()
	: m_window(sf::VideoMode(ScreenSize::s_width, ScreenSize::s_height, 32), "Tofu of Doom", sf::Style::Default)
	, m_enemy()
	, m_enemyFollower()
	, m_player()
{
	m_enemy.setUpContent();
	m_enemyFollower.setUpContent();
	m_player.setUpContent();


	m_testRect.setFillColor(sf::Color::Red);
	m_testRect.setSize(sf::Vector2f(100, 50));
	m_testRect.setOutlineColor(sf::Color::Red);
	m_testRect.setOutlineThickness(5);
	m_testRect.setPosition(10, 20);

}

void Game::run()
{
	sf::Clock clock;
	sf::Int32 lag = 0;

	while (m_window.isOpen())
	{
		sf::Time dt = clock.restart();

		lag += dt.asMilliseconds();

		processEvents();

		while (lag > MS_PER_UPDATE)
		{
			update(MS_PER_UPDATE);
			lag -= MS_PER_UPDATE;
		}
		update(MS_PER_UPDATE);
		render();
	}
}

////////////////////////////////////////////////////////////
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		processGameEvents(event);

	}
}
void Game::update(double dt)
{
	
	m_playerRect = m_player.getPlayer();
	m_enemy.update();
	m_enemyFollower.update(m_playerRect);
	m_player.update();
	
}
void Game::processGameEvents(sf::Event& event)
{
	if (sf::Event::KeyPressed == event.type)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Escape:
			m_window.close();
			break;
		default:
			break;
		}
	}
}


void Game::render()
{
	m_window.clear(sf::Color(255, 255, 255, 0));

	m_window.draw(m_testRect);
	m_enemy.render(m_window);
	m_enemyFollower.render(m_window);
	m_player.render(m_window);

	m_window.display();
}

void Game::collisions()
{
	if (m_player.getPlayer().getGlobalBounds().intersects(m_enemy.getFollower().getGlobalBounds()))
	{
		m_player.applyDamage();
	}
}

