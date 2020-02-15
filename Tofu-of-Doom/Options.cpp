#include "Options.h"

Options::Options(Game& t_game, sf::Font t_font) :
	m_game{ t_game },
	m_font{ t_font }
{
	//set up content function
	setUpContent();
}

Options::~Options()
{
}

void Options::update(sf::Time t_deltaTime)
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
	if (m_outlineRect.getPosition().y == 100.0f && m_outlineRect.getPosition().x == 100.0f)
	{
		//set to 0
		m_optionsPos = 0;
	}

	if (m_outlineRect.getPosition().y == 300.0f && m_outlineRect.getPosition().x == 100.0f)
	{
		//go to the volumn
		m_optionsPos = 1;
	}
	if (m_outlineRect.getPosition().y == 500.0f && m_outlineRect.getPosition().x == 100.0f)
	{
		//set to 2
		m_optionsPos = 2;
	}
	//function call for navigating mennu and flashing text
	navMenu(t_deltaTime);
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
	//temporary
	//back button is pressed to go back to main menu
	if (sf::Joystick::isButtonPressed(0, 6) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		m_game.m_drawState = m_game.DrawState::MAIN;
	}
	//when at pos 2
	//check if A is pressed
	if ((sf::Joystick::isButtonPressed(0, 0) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) && m_pressed == false)
	{
		//play sound effect and set to true
		m_pressed = true;
		if (m_soundFX == true)
		{
			m_soundFX = false;
		}
		else if (m_soundFX == false)
		{
			m_soundFX = true;
		}
		if (m_optionsPos == 0)
		{
			m_game.m_drawState = m_game.DrawState::MAIN;
		}
		else if (m_optionsPos == 1)
		{

			m_optionsPos = 3;
			m_outlineRect.setPosition(m_musicmsgOff.getPosition());
			navInnerMenu();
		}

	}
}
/// <summary>
/// render to t_window
/// </summary>
/// <param name="t_window"></param>
void Options::render(sf::RenderWindow& t_window)
{

	t_window.clear(sf::Color::Black);
	t_window.draw(m_outlineRect);
	//draw messages
	t_window.draw(m_musicMessage);
	t_window.draw(m_volumnMessage);

	//draw volumn bar inner and outer, draw select sound square
	t_window.draw(m_selectSoundSquare);
	t_window.draw(m_volumnBarIn);
	t_window.draw(m_volumnBarOuter);

	//run through and draw radio box
	for (int i = 0; i < 2; i++)
	{
		t_window.draw(m_radioBox[i]);
	}

	t_window.display();
}

void Options::setUpContent()
{


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
	for (int i = 0; i < 2; i++)
	{
		//set their size pos and the color
		m_radioBox[i].setSize(sf::Vector2f(20, 20));
		//set the x pos to 600 and add next pos to y at 100
		m_radioBox[i].setPosition(600.0f, 110.0f + nextPos);

		m_radioBox[i].setFillColor(sf::Color::Red);
		//add 50 to set the next one 50 down from the last
		nextPos += 50;
	}

	m_musicmsgOff.setPosition(m_radioBox[0].getPosition().x - 50, m_radioBox[0].getPosition().y + nextPos / 2);
	m_musicmsgOff.setFont(m_font);
	m_musicmsgOff.setFillColor(sf::Color::Yellow);
	m_musicmsgOff.setString(OFF_MSG);
	m_musicmsgOff.setCharacterSize(40);

	m_musicmsgOn.setPosition(m_radioBox[1].getPosition().x - 50, m_radioBox[1].getPosition().y + nextPos);
	m_musicmsgOn.setFont(m_font);
	m_musicmsgOn.setFillColor(sf::Color::Yellow);
	m_musicmsgOn.setString(OFF_MSG);
	m_musicmsgOn.setCharacterSize(40);



	m_outlineRect.setSize(sf::Vector2f(200.0f, 70.0f));
	m_outlineRect.setPosition(100.0f, 100.0f);
	m_outlineRect.setFillColor(sf::Color::Yellow);
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

	////sets the buffer and the volumn
	//m_moveOptionSound.setBuffer(m_buffoptionMove);
	//m_moveOptionSound.setVolume(50);
}
void Options::navMenu(sf::Time t_deltaTime)
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
		m_outlineRect.setPosition(100.0f, m_spaceOutline);
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

		m_outlineRect.setPosition(100, m_spaceOutline);
	}

	//if at position 1
	if (m_optionsPos == 1)
	{
		//call adjust vol
		//adjustVolumn(t_bgMusic);
	}
	// if the sound effect is not true then set volumn to 0
	if (getSoundFX() != true)
	{
		//t_bgMusic.setVolume(0);
	}
	else
	{
		//else the volumn will play
		//t_bgMusic.setVolume(m_volumnBarOuter.getSize().x);
	}


}


void Options::flashText()
{



}
void Options::navInnerMenu()
{

	//downwards on the d pad
	if (sf::Joystick::getAxisPosition(0, sf::Joystick::PovY) < -50 && m_moved == false && m_optionsPos == 3)
	{
		//set moved to true 
		m_moved = true;
		//if the outline rect is less than 500
		if (m_spaceOutline < m_outlineRect.getPosition().y + 50.0f)
		{   // add on 200
			m_spaceOutline += 50.0f;
			//play ove sound
			if (m_soundFX == true)
			{
				m_moveOptionSound.play();
			}
			m_optionsPos = 4;
		}
		//set the position od the outline rect
		m_outlineRect.setPosition(m_outlineRect.getPosition().x, m_spaceOutline);
	}
	//up on the d pad
	if (sf::Joystick::getAxisPosition(0, sf::Joystick::PovY) > 50 && m_moved == false && m_optionsPos == 4)
	{
		//set moved to true 
		m_moved = true;
		//if the outline rect is greater than 100
		if (m_spaceOutline > m_outlineRect.getPosition().y - 50.0f)
		{
			//subtract 200
			m_spaceOutline -= 50.0f;
			//play the move sound 
			if (m_soundFX == true)
			{
				m_moveOptionSound.play();
			}
			m_optionsPos = 3;
		}
		//set the position of the outline rect

		m_outlineRect.setPosition(m_outlineRect.getPosition().x, m_spaceOutline);
	}
}
void Options::adjustVolumn(sf::Music& t_backgroundMusic)
{

	if (sf::Joystick::getAxisPosition(0, sf::Joystick::PovX) > 50 && m_moved == false)
	{
		if (m_volumnBarOuter.getPosition().x + m_volumnBarOuter.getSize().x <= 290)
		{
			//changes the size of the outer red bar
			m_volumnBarOuter.setSize(sf::Vector2f(m_volumnBarOuter.getSize().x + 10, 50));

		}
	}
	//left for the Dpad
	if (sf::Joystick::getAxisPosition(0, sf::Joystick::PovX) < -50 && m_moved == false)
	{
		if (m_volumnBarOuter.getPosition().x + m_volumnBarOuter.getSize().x >= 110)
		{
			//changes the size of the outer red bar
			m_volumnBarOuter.setSize(sf::Vector2f(m_volumnBarOuter.getSize().x - 10, 50));

		}
	}

}

void Options::changeLevelSelect()
{
	if (m_optionsPos == 3)
	{
		//radio button for background music on
		m_radioBox[0].setFillColor(sf::Color::Green);
		m_radioBox[1].setFillColor(sf::Color::Red);

		m_backgrdMusic = true;
	}
	else if (m_optionsPos == 4)
	{
		//The radio button for off
		m_radioBox[0].setFillColor(sf::Color::Red);
		m_radioBox[1].setFillColor(sf::Color::Green);

		m_backgrdMusic = false;
	}

}

bool Options::getBackgroundMusic()
{
	return m_backgrdMusic;
}
