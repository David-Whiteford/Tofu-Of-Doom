#include "Options.h"

Options::Options(Game & t_game, sf::Font t_font) :
	m_game{ t_game },
	m_font{ t_font }
{
	//set up content function
	setUpContent();
}

Options::~Options()
{
}

void Options::update(sf::Time t_deltaTime , sf::Music &t_bgMusic)
{
	//timer is not 900 so increment
	if (m_timer != 900)
	{
		m_timer++;
	}
	else
	{
		//if its 900 then set to 0
		m_timer = 0;
	}
	//check the position of the outline rect and set its position variable dependong on the position
	if (outlineRect.getPosition().y == 100.0f && outlineRect.getPosition().x == 100.0f)
	{
		//set to 0
		m_optionsPos = 0;
	}

	if (outlineRect.getPosition().y == 300.0f&& outlineRect.getPosition().x == 100.0f)
	{
		//set to 1
		m_optionsPos = 1;
	}
	if (outlineRect.getPosition().y == 500.0f&& outlineRect.getPosition().x == 100.0f)
	{
		//set to 2
		m_optionsPos = 2;
	}
	//function call for navigating mennu and flashing text
	navMenu(t_deltaTime, t_bgMusic);
	flashText();
	//timer less than 0.5 then increment 
	if (m_optionsTimer >= sf::seconds(0.0f) && m_optionsTimer <= sf::seconds(0.5f))
	{
		m_optionsTimer += t_deltaTime;
	}
	//set to 0.0 again and set mved to false and pressed to false
	else
	{
		m_moved = false;
		m_pressed = false;
		m_optionsTimer = sf::seconds(0.0f);
	}

	//back button is pressed to go back to main menu
	if (sf::Joystick::isButtonPressed(0, 6) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		m_game.m_currentGameState = GameState::Main;
	}
	//when at pos 2
	if (m_optionsPos == 2)
	{
		//check if A is pressed
		if ((sf::Joystick::isButtonPressed(0, 0) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) && m_pressed == false)
		{
			//play sound effect and set to true
			m_pressed = true;
			if (m_soundFX == true)
			{
				m_soundFX = false;
			}
			else if(m_soundFX == false)
			{
				m_soundFX = true;
			}
		}
	}
	//move into level select options
	if (m_optionsPos == 0)
	{
		//the button A is presses
		if ((sf::Joystick::isButtonPressed(0, 0) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) && m_pressed == false)
		{
			//levelselect is set to true
			m_levelSelect = true;
			//soud effect is  true
			if (m_soundFX == true)
			{
				//move sound will play
				m_moveOptionSound.play();
			}
		}
	}

	if (m_levelSelect == true)
	{
		if (m_optionsPos == 0)
		{
			m_optionsPos = 3;
			outlineRect.setPosition(400.0f, 100);
			outlineRect.setSize(sf::Vector2f(150, 40));
		}
		//back
		if ((sf::Joystick::isButtonPressed(0, 1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) && m_pressed == false)
		{
			//soud effect is  true
			if (m_soundFX == true)
			{
				//move sound will play
				m_moveOptionSound.play();
			}
			//level select is set to false,the position variable is set to 0
			m_levelSelect = false;
			m_optionsPos = 0;
			//the position of the outline rect and its size is set
			outlineRect.setPosition(100.0f, 100);
			outlineRect.setSize(sf::Vector2f(200, 70));
		}
		//downwards on the d pad
		if (sf::Joystick::getAxisPosition(0, sf::Joystick::PovY) < -50 && m_moved == false)
		{
			//soud effect is  true
			if (m_soundFX == true)
			{
				//move sound will play
				m_moveOptionSound.play();
			}
			//move is set to true
			m_moved = true;
			//if the outline rect is at 400 150
			if (outlineRect.getPosition() == sf::Vector2f(400, 150))
			{
				//set its position to 400 200 and set optionns pos variable to 5
				outlineRect.setPosition(sf::Vector2f(400, 200));
				m_optionsPos = 5;
			}
			//if the outline rect is at 400 100
			if (outlineRect.getPosition() == sf::Vector2f(400, 100))
			{
				//set its position to 400 150 and set optionns pos variable to 4
				outlineRect.setPosition(sf::Vector2f(400, 150));
				m_optionsPos = 4;
			}
		}
		//up on the d pad
		if (sf::Joystick::getAxisPosition(0, sf::Joystick::PovY) > 50 && m_moved == false)
		{
			//soud effect is  true
			if (m_soundFX == true)
			{
				//play move option
				m_moveOptionSound.play();
			}
			m_moved = true;
			//if the outline rect is at 400 150
			if (outlineRect.getPosition() == sf::Vector2f(400, 150))
			{
				//set its position to 400 100 and set options pos variable to 3
				outlineRect.setPosition(sf::Vector2f(400, 100));
				m_optionsPos = 3;
			}
			//if the outline rect is at 400 200
			if ((outlineRect.getPosition() == sf::Vector2f(400, 200)))
			{
				//set its position to 400 150 and set optionns pos variable to 4
				outlineRect.setPosition(sf::Vector2f(400, 150));
				m_optionsPos = 4;
			}
		}
		//if the A button is pressed 
		if ((sf::Joystick::isButtonPressed(0, 0) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) && m_pressed == false)
		{
			//if sound effect is true
			if (m_soundFX == true)
			{
				//play move option
				m_moveOptionSound.play();
			}
			changeLevelSelect();
		}
	}

}
/// <summary>
/// render to t_window
/// </summary>
/// <param name="t_window"></param>
void Options::render(sf::RenderWindow & t_window)
{

	t_window.clear(sf::Color::Black);
	t_window.draw(outlineRect);
	//draw messages
	t_window.draw(m_musicMessage);
	t_window.draw(m_volumnMessage);
	t_window.draw(m_levelMessage);
	//draw volumn bar inner and outer, draw select sound square
	t_window.draw(m_selectSoundSquare);
	t_window.draw(m_volumnBarIn);
	t_window.draw(m_volumnBarOuter);
	//draw levels text
	t_window.draw(m_level1Text);
	t_window.draw(m_level2Text);
	t_window.draw(m_level3Text);
	//run through and draw radio box
	for (int i = 0; i < 3; i++)
	{
		t_window.draw(m_radioBox[i]);
	}
	
	t_window.display();
}

void Options::setUpContent()
{

	//the set up sets the position , size , font of text ,color and string of the text
	//level setup
	m_levelMessage.setFont(m_font);
	m_levelMessage.setFillColor(sf::Color::Yellow);
	m_levelMessage.setString(LEVEL_MESSAGE);
	m_levelMessage.setCharacterSize(40);
	m_levelMessage.setPosition(100.0f, 100.0f);

	//volumn of music setup 
	m_volumnMessage.setPosition(100.0f, 300.0f);
	m_volumnMessage.setFont(m_font);
	m_volumnMessage.setFillColor(sf::Color::Yellow);
	m_volumnMessage.setString(VOL_MESSAGE);
	m_volumnMessage.setCharacterSize(40);

	//music on / off set up 
	m_musicMessage.setPosition(100.0f, 500.0f);
	m_musicMessage.setFont(m_font);
	m_musicMessage.setFillColor(sf::Color::Yellow);
	m_musicMessage.setString(BACKGROUND_MESSAGE);
	m_musicMessage.setCharacterSize(40);
	//levels text to set the 
	m_level1Text.setPosition(400.0f, 100.0f);
	m_level1Text.setFont(m_font);
	m_level1Text.setFillColor(sf::Color::Green);
	m_level1Text.setString("-Level 1 | 4x4");
	m_level1Text.setCharacterSize(30);

	m_level2Text.setPosition(400.0f, 150.0f);
	m_level2Text.setFont(m_font);
	m_level2Text.setFillColor(sf::Color::Red);
	m_level2Text.setString("-Level 2 | 5x5");
	m_level2Text.setCharacterSize(30);

	m_level3Text.setPosition(400.0f, 200.0f);
	m_level3Text.setFont(m_font);
	m_level3Text.setFillColor(sf::Color::Red);
	m_level3Text.setString("-Level 3 | 6x6");
	m_level3Text.setCharacterSize(30);
	//loop through all 3 radio boxes
	for (int i = 0; i < 3; i++)
	{
		//set their size pos and the color
		m_radioBox[i].setSize(sf::Vector2f(20, 20));
		//set the x pos to 600 and add next pos to y at 100
		m_radioBox[i].setPosition(600.0f, 110.0f + nextPos);
		m_radioBox[i].setFillColor(sf::Color::Red);
		//add 50 to set the next one 50 down from the last
		nextPos += 50;
	}
	//set up all rectangles
	m_radioBox[0].setFillColor(sf::Color::Green);
	outlineRect.setSize(sf::Vector2f(200.0f, 70.0f));
	outlineRect.setPosition(100.0f, 100.0f);
	outlineRect.setFillColor(sf::Color::Yellow);
	//both volumn bars are set to the same size but one is a different color from the other 
	m_volumnBarIn.setSize(sf::Vector2f(200.0f, 50.0f));
	m_volumnBarIn.setPosition(100.0f, 350.0f);
	m_volumnBarIn.setFillColor(sf::Color::Red);
	m_volumnBarOuter.setSize(sf::Vector2f(200.0f, 50.0f));
	m_volumnBarOuter.setPosition(100.0f, 350.0f);
	m_volumnBarOuter.setFillColor(sf::Color::Green);
	//sound select rects size ,position and the color
	m_selectSoundSquare.setSize(sf::Vector2f(40.0f, 40.0f));
	m_selectSoundSquare.setPosition(230.0f, 510.0f);
	m_selectSoundSquare.setFillColor(sf::Color::Green);
	//loads the sound for the move options
	if (!m_buffoptionMove.loadFromFile("ASSETS\\AUDIO\\moveSelectSound.wav"))
	{
		std::cout << "Error, cannot load audio" << std::endl;
	}
	//sets the buffer and the volumn
	m_moveOptionSound.setBuffer(m_buffoptionMove);
	m_moveOptionSound.setVolume(50);
}
void Options::navMenu(sf::Time t_deltaTime, sf::Music &t_bgMusic)
{
	// if the level select is not true)
	if(m_levelSelect != true)
	{
		//downwards on the d pad
		if (sf::Joystick::getAxisPosition(0, sf::Joystick::PovY) < -50 && m_moved == false)
		{ 
			//set moved to true 
			m_moved = true;
			//if the outline rect is less than 500
			if (m_spaceOutline < 500.0f)
			{   // add on 200
				m_spaceOutline += 200.0f;
				//play ove sound
				if (m_soundFX == true)
				{
					m_moveOptionSound.play();
				}
			}
			//set the position od the outline rect
			outlineRect.setPosition(100.0f, m_spaceOutline);
		}
		//up on the d pad
		if (sf::Joystick::getAxisPosition(0, sf::Joystick::PovY) > 50 && m_moved == false)
		{
			//set moved to true 
			m_moved = true; 
			//if the outline rect is greater than 100
			if (m_spaceOutline > 100.0f)
			{
				//subtract 200
				m_spaceOutline -= 200.0f;
				//play the move sound 
				if (m_soundFX == true)
				{
					m_moveOptionSound.play();
				}
			}
			//set the position of the outline rect

			outlineRect.setPosition(100, m_spaceOutline);
		}
	}


	
}


void Options::flashText()
{
	    //if the outline rect is at the pos below
		if (outlineRect.getPosition().x == 100.0f && outlineRect.getPosition().y == 100.0f)
		{
			//level message color is black
			m_levelMessage.setFillColor(sf::Color::Black);
		}
		else
		{
			//level message color is yellow
			m_levelMessage.setFillColor(sf::Color::Yellow);
		}
		//if the outline rect is at the pos below
		if (outlineRect.getPosition().x == 100.0f && outlineRect.getPosition().y == 300.0f)
		{
			//volumne message color is black
			m_volumnMessage.setFillColor(sf::Color::Black);
		}
		else
		{
			//volumne message color is yellow
			m_volumnMessage.setFillColor(sf::Color::Yellow);
		}
		//if the outline rect is at the pos below
		if (outlineRect.getPosition().x == 100.0f && outlineRect.getPosition().y == 500.0f)
		{
			//music message color is black
			m_musicMessage.setFillColor(sf::Color::Black);
		}
		else
		{
			//music message color is yellow
			m_musicMessage.setFillColor(sf::Color::Yellow);
		}
		// if the soundeffect is off then set the colour of the sound fx square to red
		if (m_soundFX == false)
		{
			m_selectSoundSquare.setFillColor(sf::Color::Red);
		}
		// if the soundeffect is on then set the colour of the sound fx square to green
		else if(m_soundFX == true)
		{
			m_selectSoundSquare.setFillColor(sf::Color::Green);
		}
}
void Options::adjustVolumn(sf::Music &t_backgroundMusic)
{
	
	if (sf::Joystick::getAxisPosition(0, sf::Joystick::PovX) > 50 && m_moved == false)
	{
		if (m_volumnBarOuter.getPosition().x + m_volumnBarOuter.getSize().x <= 290)
		{
			//changes the size of the outer red bar
			m_volumnBarOuter.setSize(sf::Vector2f(m_volumnBarOuter.getSize().x + 10, 50));
			t_backgroundMusic.setVolume(t_backgroundMusic.getVolume() + 10);
		}
	}
	//left for the Dpad
	if (sf::Joystick::getAxisPosition(0, sf::Joystick::PovX) < -50 && m_moved == false)
	{
		if (m_volumnBarOuter.getPosition().x + m_volumnBarOuter.getSize().x >= 110)
		{
			//changes the size of the outer red bar
			m_volumnBarOuter.setSize(sf::Vector2f(m_volumnBarOuter.getSize().x - 10, 50));
			t_backgroundMusic.setVolume(t_backgroundMusic.getVolume() - 10);
		}
	}
	
}

void Options::changeLevelSelect()
{
	if (m_optionsPos == 3)
	{
		m_level1Text.setFillColor(sf::Color::Green);
		m_level2Text.setFillColor(sf::Color::Red);
		m_level3Text.setFillColor(sf::Color::Red);
		//set the colour depending on which one 
		//is active in this case the one at index 0 is active 
		//so 0 is green and rest are red
		m_radioBox[0].setFillColor(sf::Color::Green);
		m_radioBox[1].setFillColor(sf::Color::Red);
		m_radioBox[2].setFillColor(sf::Color::Red);
	}
	else if (m_optionsPos == 4)
	{
		m_level1Text.setFillColor(sf::Color::Red);
		m_level2Text.setFillColor(sf::Color::Green);
		m_level3Text.setFillColor(sf::Color::Red);
		//set the colour depending on which one 
		//is active in this case the one at index 1 is active 
		//so 1 is green and rest are red
		m_radioBox[1].setFillColor(sf::Color::Green);
		m_radioBox[0].setFillColor(sf::Color::Red);
		m_radioBox[2].setFillColor(sf::Color::Red);
	}
	else if (m_optionsPos == 5)
	{
		m_level1Text.setFillColor(sf::Color::Red);
		m_level2Text.setFillColor(sf::Color::Red);
		m_level3Text.setFillColor(sf::Color::Green);
		//set the colour depending on which one 
		//is active in this case the one at index 2 is active 
		//so 2 is green and rest are red
		m_radioBox[2].setFillColor(sf::Color::Green);
		m_radioBox[0].setFillColor(sf::Color::Red);
		m_radioBox[1].setFillColor(sf::Color::Red);
	}
}
