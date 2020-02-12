#include "MainMenu.h"

MainMenu::MainMenu(Game & t_game, sf::Font t_font) :
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
	//function call 
	lightningAnimation(t_deltaTime,t_soundFX);

	//moves hovering option right
	if ((sf::Joystick::getAxisPosition(0, sf::Joystick::PovX) > 50 || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && m_movedOption == false)
	{
		//sets moved option to true
		m_movedOption = true;
		//if lees than 620 then move to the right by 200
		if (m_spaceOutline < 620)
		{
			m_spaceOutline += 200;
			//set sound fx to true and play
			if (t_soundFX == true) 
			{
				m_moveOptionSound.play();
			}
		}
		//set pos of outline rect
		outline.setPosition(m_spaceOutline, 520);
		
	}
	//moves hovering option left
	if ((sf::Joystick::getAxisPosition(0, sf::Joystick::PovX) < -50 || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && m_movedOption == false)
	{
		//sets moved option to true
		m_movedOption = true;
		//if greater than 20 then move to the left by 200
		if (m_spaceOutline > 20)
		{
			m_spaceOutline -= 200;
			//set sound fx to true and play
			if (t_soundFX == true)
			{
				m_moveOptionSound.play();
			}
		}
		//set pos of outline rect
		outline.setPosition(m_spaceOutline, 520);
	}

	//up if in the player position
	if ((sf::Joystick::getAxisPosition(0, sf::Joystick::PovY) > 50 || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && m_movedOption == false)
	{  
		//set move to true
		m_movedOption = true;
		//if at position 520 or 20 
		if (outline.getPosition().y == 520.0f && outline.getPosition().x == 20.0f)
		{
			//set to position 20 , 100
			outline.setPosition(20.0f, 100.0f);
		}
		// sound is true
		if (t_soundFX == true)
		{
			//play move sound move 
			m_moveOptionSound.play();
		}
	}
	//down if in the credits button position
	if ((sf::Joystick::getAxisPosition(0, sf::Joystick::PovY) < -50 || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && m_movedOption == false)
	{
		//set move to true
		m_movedOption = true;
		//if at position 100 or 20 
		if (outline.getPosition().y == 100.0f && outline.getPosition().x == 20.0f)
		{
			//then set to pos 20 , 250
			outline.setPosition(20.0f, 520.0f);
		}
		// sound is true
		if (t_soundFX == true)
		{
			//play move sound move 
			m_moveOptionSound.play();
		}
	}

	//if A is pressed
	if (sf::Joystick::isButtonPressed(0, 0) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		//play move sound move if true
		if (t_soundFX == true)
		{
			m_selectSound.play();
		}
		//set continue to true
		m_continue = true;
		//check the position of the outline rectangle
		//depending on the position of the outline rect set the gamemode
		if (m_selectPos == 0)
		{
			m_game.m_currentGameState = GameState::Level1;
		}
		if (m_selectPos == 1)
		{
			m_game.m_currentGameState = GameState::HighScore;
		}
		if (m_selectPos == 2)
		{
			m_game.m_currentGameState = GameState::Options;
		}
		if (m_selectPos == 3)
		{
			m_game.m_currentGameState = GameState::Exit;
		}
		if (m_selectPos == 4)
		{
			m_game.m_currentGameState = GameState::Credits;
		}

	}
	// changes the position of select option eg outline rects position
	if(outline.getPosition().x == 20)
	{
		m_selectPos = 0;
	}
	if(outline.getPosition().x == 220)
	{
		m_selectPos = 1;
	}
	if(outline.getPosition().x == 420)
	{
		m_selectPos = 2;
	}
	if(outline.getPosition().x == 620)
	{
		m_selectPos = 3;
	}
	if (outline.getPosition().y == 100.0f && outline.getPosition().x == 20.0f)
	{
		m_selectPos = 4;
	}
	//adds delay in between switching options
	if (timer >= sf::seconds(0.0) && timer <= sf::seconds(0.5f))
	{
		//increment timer
		timer += t_deltaTime;
	}
	else
	{
		//set move to true and reset timer to 0
		m_movedOption = false;
		timer = sf::seconds(0.0);
	}
	
}
/// <summary>
/// render to t_window
/// </summary>
/// <param name="t_window"></param>
void MainMenu::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_bg);
	t_window.draw(outline);
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
	if (!m_bgTextureLightOn.loadFromFile("ASSETS\\IMAGES\\mainMenuLightOn.jpg"))
	{
		std::cout << "Cant load image " << std::endl;
	}
	if (!m_bgTextureLightOff.loadFromFile("ASSETS\\IMAGES\\mainMenuLightOff.jpg"))
	{
		std::cout << "Cant load image " << std::endl;
	}
	if (!m_buttonTexture.loadFromFile("ASSETS\\IMAGES\\bloodybutton.png"))
	{
		std::cout << "Cant load image " << std::endl;
	}
    // load and set the sounds of the move and set volumn
	if (!buff.loadFromFile("ASSETS\\AUDIO\\moveSelectSound.wav"))
	{
		std::cout << "Error, cannot load audio" << std::endl;
	}
	m_moveOptionSound.setBuffer(buff);
	m_moveOptionSound.setVolume(50);
	// load and set the sounds of the thunder and set volumn
	if (!buff3.loadFromFile("ASSETS\\AUDIO\\thunder.ogg"))
	{
		std::cout << "Error, cannot load audio" << std::endl;
	}
	m_thunder.setBuffer(buff3);
	m_thunder.setVolume(60);
	m_thunder.setPlayingOffset(sf::seconds(1.5));
	// load and set the sounds of the select and set volumn
	if (!buff2.loadFromFile("ASSETS\\AUDIO\\select.wav"))
	{
		std::cout << "Error, cannot load audio" << std::endl;
	}
	m_selectSound.setBuffer(buff2);
	m_selectSound.setVolume(50);
	//loop through the buttons and set texture, position , scale and increment space by 200
	for (int i = 0; i < 4; i++)
	{
		m_button[i].setTexture(m_buttonTexture);
		m_button[i].setPosition(20 + space, 520);
		m_button[i].setScale(1.1, 1.5);
		space += 200;
		
	}
	//set texture ,scale and position of button 
	m_button[4].setTexture(m_buttonTexture);
	m_button[4].setScale(1.1, 1.5);
	m_button[4].setPosition(20, 100);
	//set the size , position and colour of the outline rect
	outline.setSize(sf::Vector2f(165, 70));
	outline.setPosition(20, 520);
	outline.setFillColor(sf::Color::Yellow);
	m_bg.setTexture(m_bgTextureLightOff);
	m_bg.setPosition(0.0f, 0.0f);
	m_bg.setColor(sf::Color(255, 255, 255, 0));
	setUpText();
}

void MainMenu::screenTransitionOff(sf::Time t_deltaTime)
{
	// the timer is less than 255 then increment and set color
	if (transition_timer >= sf::seconds(0.0) && transition_timer <= sf::seconds(255.0f))
	{
		transition_timer += t_deltaTime;
		m_bg.setColor(sf::Color(255, 255, 255, m_bg.getColor().a -1));
	}
}
///lightning animatiton
void MainMenu::lightningAnimation(sf::Time t_deltaTime, bool t_soundFX)
{
	if (m_timerAnimation >= sf::seconds(0.0) && m_timerAnimation <= sf::seconds(10.0f))
	{
		m_timerAnimation += t_deltaTime;
		m_bg.setTexture(m_bgTextureLightOff);
	}
	else if (m_timerAnimation >= sf::seconds(10.0) && m_timerAnimation <= sf::seconds(10.8f))
	{
		m_timerAnimation += t_deltaTime;
		m_bg.setTexture(m_bgTextureLightOn);
		if (t_soundFX == true)
		{
			m_thunder.play();
		}
	}
	else
	{
		m_timerAnimation = sf::seconds(0.0);
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
