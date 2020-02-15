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
	//when start up is true then screen tran is on 
	if (m_startUp == true)
	{
		screenTransitionOn(t_deltaTime);
	}
	//when continue is true then screen tran is off 
	if (m_continue == true)
	{
		screenTransitionOff(t_deltaTime);
	}

	//moved the outline for the menu down to bottom
	if ((sf::Joystick::getAxisPosition(0, sf::Joystick::PovY) > 50 || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && m_moved == false)
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
	if ((sf::Joystick::getAxisPosition(0, sf::Joystick::PovY) < -50 ||sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && m_moved == false)
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
	//if A is pressed

	//std::cout << "The selectPosiotion " << m_selectPos << std::endl;
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
	t_window.draw(m_outlineRect);
	//loop through buttons and render
	for (int i = 0; i < 5; i++)
	{
		t_window.draw(m_button[i]);
	}
	// draw all text 
	t_window.draw(m_playText);
	t_window.draw(m_highScoreText);
	t_window.draw(m_optionsText);
	t_window.draw(m_exitText);
	t_window.draw(m_creditsText);
	t_window.display();
}

void MainMenu::setUpContent()
{
	//load all textures
	if (!m_bgTexture.loadFromFile("models/monster.jpg"))
	{
		std::cout << "Cant load image " << std::endl;
	}
	if (!m_buttonTexture.loadFromFile("models/bloodybutton.png"))
	{
		std::cout << "Cant load bloody button image " << std::endl;
	}
	// load and set the sounds of the move and set volumn
	//if (!buff.loadFromFile("ASSETS\\AUDIO\\moveSelectSound.wav"))
	//{
	//	std::cout << "Error, cannot load audio" << std::endl;
	//}
	//m_moveOptionSound.setBuffer(buff);
	//m_moveOptionSound.setVolume(50);
	//// load and set the sounds of the thunder and set volumn
	//if (!buff3.loadFromFile("ASSETS\\AUDIO\\thunder.ogg"))
	//{
	//	std::cout << "Error, cannot load audio" << std::endl;
	//}
	////m_thunder.setBuffer(buff3);
	//m_thunder.setVolume(60);
	//m_thunder.setPlayingOffset(sf::seconds(1.5));
	//// load and set the sounds of the select and set volumn
	//if (!buff2.loadFromFile("ASSETS\\AUDIO\\select.wav"))
	//{
	//	std::cout << "Error, cannot load audio" << std::endl;
	//}
	//m_selectSound.setBuffer(buff2);
	//m_selectSound.setVolume(50);
	//loop through the buttons and set texture, position , scale and increment space by 200
	for (int i = 0; i < 4; i++)
	{
		m_button[i].setTexture(m_buttonTexture);
		m_button[i].setPosition(50, 20 +space);
		m_button[i].setScale(1.1, 1.5);
		space += 200;

	}
	
	//set the size , position and colour of the outline rect
	m_outlineRect.setSize(sf::Vector2f(165, 70));
	m_outlineRect.setPosition(50, 20);
	m_outlineRect.setFillColor(sf::Color::Yellow);

	m_bg.setTexture(m_bgTexture);
	m_bg.setPosition(400.0f, -50.0f);
	m_bg.setColor(sf::Color(255, 255, 255, 0));
	setUpText();
}

void MainMenu::screenTransitionOff(sf::Time t_deltaTime)
{
	// the timer is less than 255 then increment and set color
	if (transition_timer >= sf::seconds(0.0) && transition_timer <= sf::seconds(255.0f))
	{
		transition_timer += t_deltaTime;
		m_bg.setColor(sf::Color(255, 255, 255, m_bg.getColor().a - 1));
	}
}

void MainMenu::checkPosition()
{
	if (m_outlineRect.getPosition().y == 20)
	{
		m_selectPos = 0;
	}
	if (m_outlineRect.getPosition().y == 220)
	{
		m_selectPos = 1;
	}
	if (m_outlineRect.getPosition().y == 420)
	{
		m_selectPos = 2;
	}
	if (m_outlineRect.getPosition().y == 620)
	{
		m_selectPos = 3;
	}
}

void MainMenu::changeGameState(bool t_soundFX)
{
	if (sf::Joystick::isButtonPressed(0, 0) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		//play move sound move if true
		if (t_soundFX == true)
		{
			//m_selectSound.play();
		}
		//set continue to true
		m_continue = true;
		//check the position of the outline rectangle
		//depending on the position of the outline rect set the gamemode
		if (m_selectPos == 0)
		{
			m_game.m_drawState = m_game.DrawState::GAME;
			m_game.initialise();
		}
		if (m_selectPos == 1)
		{
		
		}
		if (m_selectPos == 2)
		{
		
		}

	}
}

void MainMenu::setUpText()
{
	//set the font , position and the string , character size of the texts used
	m_playText.setFont(m_font);
	m_playText.setPosition(64.0f, 518.0f);
	m_playText.setString("Play");
	m_playText.setCharacterSize(55);

	m_highScoreText.setFont(m_font);
	m_highScoreText.setPosition(238.0f, 530.0f);
	m_highScoreText.setString("HighScores");
	m_highScoreText.setCharacterSize(33);

	m_optionsText.setFont(m_font);
	m_optionsText.setPosition(438.0f, 530.0f);
	m_optionsText.setString("Options");
	m_optionsText.setCharacterSize(40);

	m_exitText.setFont(m_font);
	m_exitText.setPosition(660.0f, 518.0f);
	m_exitText.setString("EXIT");
	m_exitText.setCharacterSize(55);

	m_creditsText.setFont(m_font);
	m_creditsText.setPosition(25.0f, 98.0f);
	m_creditsText.setString("CREDITS");
	m_creditsText.setCharacterSize(55);

}

void MainMenu::screenTransitionOn(sf::Time t_deltaTime)
{
	// if the timer is less than 255
	if (transition_timer >= sf::seconds(0.0) && transition_timer <= sf::seconds(255.0f))
	{
		//increment transition timer
		transition_timer += t_deltaTime;
		m_bg.setColor(sf::Color(255, 255, 255, m_bg.getColor().a + 1));
		if (transition_timer >= sf::seconds(255.0f))
		{
			m_startUp = false;
		}
	}

}