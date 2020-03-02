#include "MainMenu.h"

MainMenu::MainMenu(Game& t_game, sf::Font t_font) :
	m_game{ t_game },
	m_font{ t_font }

{

	//function to set up content
	setUpContent();

}

MainMenu::~MainMenu()
{
}

void MainMenu::update(sf::Time t_deltaTime, bool t_soundFX)
{

	std::cout << "start" << m_startUp << std::endl;
	//when start up is true then screen tran is on 
	if (m_startUp == true)
	{
		screenTransitionOn(t_deltaTime);

	}
	//when continue is true then screen tran is off 
	//if (m_continue == true)
	//{
	//	screenTransitionOff(t_deltaTime);
	//}

	//moved the outline for the menu down to bottom
	if ((m_controller.downButton() == true || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && m_moved == false)
	{
		//sets moved option to true
		m_moved = true;
		//if lees than 620 then move to the down by 200
		if (m_spaceOutline < 620)
		{
			m_spaceOutline += 200;
			//set sound fx to true and play
			if (t_soundFX == true)
			{
				//m_moveOptionSound.play();
			}
		}
		//set pos of outline rect
		m_outlineRect.setPosition(50, m_spaceOutline);

	}
	//moves hovering option left
	if ((m_controller.upButton() == true || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && m_moved == false)
	{
		//sets moved option to true
		m_moved = true;
		//if greater than 20 then move to the up by 200
		if (m_spaceOutline > 20)
		{
			m_spaceOutline -= 200;
			//set sound fx to true and play
			if (t_soundFX == true)
			{
				//m_moveOptionSound.play();
			}
		}
		//set pos of outline rect
		m_outlineRect.setPosition(50, m_spaceOutline);
	}
	checkPosition();
	changeGameState(t_soundFX);
	//adds delay in between switching options
	if (timer >= sf::seconds(0.0) && timer <= sf::seconds(0.5f))
	{
		//increment timer
		timer += t_deltaTime;
	}
	else
	{
		//set move to true and reset timer to 0
		m_moved = false;
		timer = sf::seconds(0.0);
	}
}
/// <summary>
/// render to t_window
/// </summary>
/// <param name="t_window"></param>
void MainMenu::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_bg);
	//loop through buttons and render
	for (int i = 0; i < 3; i++)
	{
		t_window.draw(m_button[i]);
	}
	// draw all text 
	t_window.draw(m_playText);
	t_window.draw(m_optionsText);
	t_window.draw(m_exitText);
	t_window.draw(m_titleMessage);
	t_window.draw(m_titlemessageSecond);

	t_window.display();
}

void MainMenu::setUpContent()
{


	//sets up the message for the first title message
	m_titleMessage.setFont(m_font);
	m_titleMessage.setPosition(800.0f, 100.0f);
	m_titleMessage.setString(FIRST_TITLE_MESSAGE);
	m_titleMessage.setCharacterSize(85);
	m_titleMessage.setColor(sf::Color::Black);
	//sets up the message for the second title message
	m_titlemessageSecond.setFont(m_font);
	m_titlemessageSecond.setPosition(820.0f, 180.0f);
	m_titlemessageSecond.setString(SECOND_TITLE_MESSAGE);
	m_titlemessageSecond.setCharacterSize(85);
	m_titlemessageSecond.setColor(sf::Color::Black);
	//load all textures
	if (!m_bgTexture.loadFromFile("images/bloodySplash.jpg"))
	{
		std::cout << "Cant load image " << std::endl;
	}
	if (!m_buttonTexture.loadFromFile("images/bloodybutton.png"))
	{
		std::cout << "Cant load bloody button image " << std::endl;
	}
	for (int i = 0; i < 3; i++)
	{
		m_button[i].setTexture(m_buttonTexture);
		m_button[i].setPosition(50, 20 + space);
		m_button[i].setScale(1.1, 1.5);
		space += 200;
	}

	//set the size , position and colour of the outline rect
	m_outlineRect.setSize(sf::Vector2f(165, 70));
	m_outlineRect.setPosition(50, 20);

	m_bg.setTexture(m_bgTexture);
	m_bg.setPosition(0.0f, 0.0f);
	m_bg.setColor(sf::Color(255, 255, 255, 0));
	setUpText();
}

void MainMenu::screenTransitionOff(sf::Time t_deltaTime)
{
	if (transitionTimerOff >= sf::seconds(0.0) && transitionTimerOff <= sf::seconds(4.0f))
	{
		//increment timer
		transitionTimerOff += t_deltaTime;
		std::cout << "TIMER: " << transitionTimerOff.asSeconds() << std::endl;
		//fase the background
		m_bg.setColor(sf::Color(255, 255, 255, m_bg.getColor().a - 1));
		for (int i = 0; i < 4; i++)
		{
			m_button[i].setColor(sf::Color(255, 255, 255, m_bg.getColor().a - 1));
		}
		m_playText.setColor(sf::Color(255, 255, 255, m_bg.getColor().a - 1));
		m_optionsText.setColor(sf::Color(255, 255, 255, m_bg.getColor().a - 1));
		m_exitText.setColor(sf::Color(255, 255, 255, m_bg.getColor().a - 1));

	}
	else if (transitionTimerOff >= sf::seconds(3.9f))
	{

		m_transitionToScreen = true;

	}
}

void MainMenu::checkPosition()
{
	if (m_startUp == false)
	{
		if (m_outlineRect.getPosition().y == 20)
		{
			m_selectPos = 0;
			m_playText.setColor(sf::Color(sf::Color::Yellow));
			m_optionsText.setColor(sf::Color(sf::Color::White));
			m_exitText.setColor(sf::Color(sf::Color::White));
		}
		if (m_outlineRect.getPosition().y == 220)
		{
			m_selectPos = 1;
			m_optionsText.setColor(sf::Color(sf::Color::Yellow));
			m_playText.setColor(sf::Color(sf::Color::White));
			m_exitText.setColor(sf::Color(sf::Color::White));
		}
		if (m_outlineRect.getPosition().y == 420)
		{
			m_selectPos = 2;
			m_exitText.setColor(sf::Color(sf::Color::Yellow));
			m_playText.setColor(sf::Color(sf::Color::White));
			m_optionsText.setColor(sf::Color(sf::Color::White));
		}

	}
}

void MainMenu::changeGameState(bool t_soundFX)
{
	if (m_controller.aButton() || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		//set continue to true
		m_continue = true;
		//check the position of the outline rectangle

			//depending on the position of the outline rect set the gamemode
		if (m_selectPos == 0)
		{
			m_game.m_drawState = m_game.DrawState::GAME;

		}
		if (m_selectPos == 1)
		{
			m_game.m_drawState = m_game.DrawState::OPTIONS;
		}
		if (m_selectPos == 2)
		{
			m_game.m_drawState = m_game.DrawState::EXIT;
		}


	}
}

void MainMenu::setUpText()
{

	sf::Vector2f offset(sf::Vector2f(50.0f, 20.0f));
	//set the font , position and the string , character size of the texts used
	m_playText.setFont(m_font);
	m_playText.setPosition(m_button[0].getPosition().x + offset.x, m_button[0].getPosition().y + offset.y);
	m_playText.setString("Play");
	m_playText.setCharacterSize(40);
	offset = (sf::Vector2f(35.0f, 20.0f));
	m_optionsText.setFont(m_font);
	m_optionsText.setPosition(m_button[1].getPosition().x + offset.x, m_button[1].getPosition().y + offset.y);
	m_optionsText.setString("Options");
	m_optionsText.setCharacterSize(40);
	offset = (sf::Vector2f(60.0f, 20.0f));
	m_exitText.setFont(m_font);
	m_exitText.setPosition(m_button[2].getPosition().x + offset.x, m_button[2].getPosition().y + offset.y);
	m_exitText.setString("EXIT");
	m_exitText.setCharacterSize(40);



}

void MainMenu::setStartUP(bool startup)
{
	m_startUp = startup;
	m_transitionToScreen = false;
	m_continue = false;
}

void MainMenu::screenTransitionOn(sf::Time t_deltaTime)
{
	if (transitionTimer >= sf::seconds(0.0) && transitionTimer <= sf::seconds(4.0f))
	{
		//increment timer
		transitionTimer += t_deltaTime;
		std::cout << "TIMER: " << transitionTimer.asSeconds() << std::endl;
		//fase in the background image and the text and buttons
		m_bg.setColor(sf::Color(255, 255, 255, m_bg.getColor().a + 1));
		for (int i = 0; i < 4; i++)
		{
			m_button[i].setColor(sf::Color(255, 255, 255, m_bg.getColor().a + 1));
		}
		m_playText.setColor(sf::Color(255, 255, 255, m_bg.getColor().a + 1));
		m_optionsText.setColor(sf::Color(255, 255, 255, m_bg.getColor().a + 1));
		m_exitText.setColor(sf::Color(255, 255, 255, m_bg.getColor().a + 1));

	}
	else
	{
		m_startUp = false;

	}

}