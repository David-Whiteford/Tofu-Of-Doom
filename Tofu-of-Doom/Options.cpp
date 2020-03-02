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

void Options::update(sf::Time t_deltaTime, ISoundEngine* bgSoundEngine)
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

	//function call for navigating mennus
	if (m_optionsPos < 2)
	{
		navMenu(t_deltaTime, bgSoundEngine);
	}
	else
	{
		navInnerMenu();
		if (m_controller.yButton() == true)
		{
			m_optionsPos = 0;
			m_outlineRect.setPosition(sf::Vector2f(100.0f, 100.0f));
		}
	}
	checkPosition();
	checkButtonPosition();
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
	if (m_controller.backButton() == true || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		m_game.resetScreenTrans();
		m_game.m_drawState = m_game.DrawState::MAIN;

	}
	//when at pos 2
	//check if A is pressed
	if ((m_controller.aButton() == true || sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) && m_pressed == false)
	{
		//play sound effect and set to true
		m_pressed = true;

		if (m_optionsPos == 0)
		{
			m_outlineRect.setPosition(m_button[2].getPosition());
			m_optionsPos = 2;
			navInnerMenu();
		}
		else if (m_optionsPos == 2)
		{
			changeMusicState(bgSoundEngine);
		}
		else if (m_optionsPos == 3)
		{
			changeMusicState(bgSoundEngine);
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
	t_window.draw(m_bg);
	for (int i = 0; i < 4; i++)
	{

		t_window.draw(m_button[i]);
		
	}
	//draw messages
	t_window.draw(m_musicMessage);
	t_window.draw(m_volumnMessage);

	//draw volumn bar inner and outer, draw select sound square

	t_window.draw(m_volumnBarIn);
	t_window.draw(m_volumnBarOuter);

	//run through and draw radio box
	for (int i = 0; i < 2; i++)
	{
		t_window.draw(m_radioBox[i]);
	}
	t_window.draw(m_musicmsgOff);
	t_window.draw(m_musicmsgOn);
	t_window.draw(m_pressBackMessage);
	
	t_window.display();
}
void Options::checkButtonPosition()
{

	if (m_optionsPos == 0)
	{
		m_musicMessage.setColor(sf::Color(sf::Color::Yellow));
		m_musicmsgOn.setColor(sf::Color(sf::Color::White));
		m_volumnMessage.setColor(sf::Color(sf::Color::White));
		m_musicmsgOff.setColor(sf::Color(sf::Color::White));
	}
	if (m_optionsPos == 1)
	{
		m_musicMessage.setColor(sf::Color(sf::Color::White));
		m_musicmsgOn.setColor(sf::Color(sf::Color::White));
		m_volumnMessage.setColor(sf::Color(sf::Color::Yellow));
		m_musicmsgOff.setColor(sf::Color(sf::Color::White));
	}

	if (m_optionsPos == 2)
	{
		m_musicmsgOff.setColor(sf::Color(sf::Color::Yellow));
		m_volumnMessage.setColor(sf::Color(sf::Color::White));
		m_musicMessage.setColor(sf::Color(sf::Color::White));
		m_musicmsgOn.setColor(sf::Color(sf::Color::White));
	}
	if (m_optionsPos == 3)
	{


		m_musicmsgOn.setColor(sf::Color(sf::Color::Yellow));
		m_musicmsgOff.setColor(sf::Color(sf::Color::White));
		m_volumnMessage.setColor(sf::Color(sf::Color::White));
		m_musicMessage.setColor(sf::Color(sf::Color::White));
	}


}

void Options::setUpContent()
{
	if (!m_bgTexture.loadFromFile("images/bloodySplash.jpg"))
	{
		std::cout << "Cant load image " << std::endl;
	}
	m_bg.setTexture(m_bgTexture);
	m_bg.setPosition(0.0f, 0.0f);
	
	for (int i = 0; i < 2; i++)
	{
		//set their size pos and the color
		m_radioBox[i].setSize(sf::Vector2f(50, 50));
		//set the x pos to 600 and add next pos to y at 100
		m_radioBox[i].setPosition(800.0f, 110.0f + nextPos);
		m_radioBox[i].setFillColor(sf::Color::Red);
		m_radioBox[i].setOutlineThickness(2);
		m_radioBox[i].setOutlineColor(sf::Color::White);
		//add 50 to set the next one 50 down from the last
		nextPos += 70;
	}
	m_radioBox[1].setFillColor(sf::Color::Green);
	m_musicmsgOff.setPosition(m_radioBox[0].getPosition().x - 50, m_radioBox[0].getPosition().y + nextPos / 2);
	m_musicmsgOff.setFont(m_font);
	m_musicmsgOff.setFillColor(sf::Color::White);
	m_musicmsgOff.setString(OFF_MSG);
	m_musicmsgOff.setCharacterSize(40);

	m_musicmsgOn.setPosition(m_radioBox[1].getPosition().x - 50, m_radioBox[1].getPosition().y + nextPos);
	m_musicmsgOn.setFont(m_font);
	m_musicmsgOn.setFillColor(sf::Color::White);
	m_musicmsgOn.setString(OFF_MSG);
	m_musicmsgOn.setCharacterSize(40);

	if (!m_buttonTexture.loadFromFile("images/bloodybutton.png"))
	{
		std::cout << "Cant load bloody button image " << std::endl;
	}
	for (int i = 0; i < 4; i++)
	{
		m_button[i].setTexture(m_buttonTexture);
		m_button[i].setPosition(100, 100 + m_offsetX);
		m_button[i].setScale(1.1, 1.5);
		m_offsetX += 150;

	}
	sf::Vector2f offset = sf::Vector2f(0, 100);
	m_button[2].setPosition(600, 0 + offset.y);
	m_button[3].setPosition(600, 78 + offset.y);

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

	setUpText();
	m_pressBackMessage.setFont(m_font);
	m_pressBackMessage.setPosition(600.0f, 500.0f);
	m_pressBackMessage.setString("Press BACK to return to menu");
	m_pressBackMessage.setCharacterSize(55);

}
void Options::navMenu(sf::Time t_deltaTime, ISoundEngine* bgSoundEngine)
{

	//downwards on the d pad
	if (m_controller.downButton() == true && m_moved == false && m_optionsPos != 1)
	{
		//set moved to true 
		m_moved = true;
		m_optionsPos++;
	}
	//up on the d pad
	if (m_controller.upButton() == true && m_moved == false && m_optionsPos != 0)
	{
		//set moved to true 
		m_moved = true;
		m_optionsPos--;
	}

	//if at position 1
	if (m_optionsPos == 1)
	{
		//call adjust vol
		changeMusicVol(bgSoundEngine);
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

void Options::checkPosition()
{
	//check the position of the outline rect and set its position variable dependong on the position
	if (m_optionsPos == 0)
	{
		m_outlineRect.setPosition(100.0f, 100.0f);
	}
	else if(m_optionsPos == 1)
	{
		m_outlineRect.setPosition(100.0f, 250.0f);
	}
	else if (m_optionsPos == 2)
	{
		m_outlineRect.setPosition(600.0f, 100.0f);
	}
	else if (m_optionsPos == 3)
	{
		m_outlineRect.setPosition(600.0f, 170.0f);
	}

}


void Options::flashText()
{



}
void Options::navInnerMenu()
{

	//downwards on the d pad
	if (m_controller.downButton() == true && m_moved == false)
	{
		//set moved to true 
		m_moved = true;
		if (m_optionsPos != 3)
		{
			m_optionsPos++;
		}
	}
	//up on the d pad
	if (m_controller.upButton() == true && m_moved == false)
	{
		//set moved to true 
		m_moved = true;
		if (m_optionsPos != 2)
		{
			m_optionsPos--;
		}
	}
}
void Options::setUpText()
{
	sf::Vector2f offset(sf::Vector2f(50.0f, 20.0f));
	//set the font , position and the string , character size of the texts used
	m_musicMessage.setFont(m_font);
	m_musicMessage.setPosition(m_button[0].getPosition().x + offset.x, m_button[0].getPosition().y + offset.y);
	m_musicMessage.setString(BACKGROUND_MESSAGE);
	m_musicMessage.setCharacterSize(40);


	offset = (sf::Vector2f(35.0f, 20.0f));
	m_volumnMessage.setFont(m_font);
	m_volumnMessage.setPosition(m_button[1].getPosition().x + offset.x, m_button[1].getPosition().y + offset.y);
	m_volumnMessage.setString(VOL_MESSAGE);
	m_volumnMessage.setCharacterSize(40);

	//offset = (sf::Vector2f(60.0f, 20.0f));
	//m_exitText.setFont(m_font);
	//m_exitText.setPosition(m_button[2].getPosition().x + offset.x, m_button[2].getPosition().y + offset.y);
	//m_exitText.setString("EXIT");
	//m_exitText.setCharacterSize(40);
	offset = (sf::Vector2f(55.0f, 15.0f));
	m_musicmsgOff.setFont(m_font);
	m_musicmsgOff.setPosition(m_button[2].getPosition().x + offset.x, m_button[2].getPosition().y + offset.y);
	m_musicmsgOff.setString("Off");
	m_musicmsgOff.setCharacterSize(40);

	offset = (sf::Vector2f(55.0f, 15.0f));
	m_musicmsgOn.setFont(m_font);
	m_musicmsgOn.setPosition(m_button[3].getPosition().x + offset.x, m_button[3].getPosition().y + offset.y);
	m_musicmsgOn.setString("On");
	m_musicmsgOn.setCharacterSize(40);


}


void Options::changeMusicState(ISoundEngine* bgSoundEngine)
{
	if (m_optionsPos == 2)
	{
		//radio button for background music off
		m_radioBox[0].setFillColor(sf::Color::Green);
		m_radioBox[1].setFillColor(sf::Color::Red);
		m_backgrdMusic = false;
		bgSoundEngine->setAllSoundsPaused(true);
	}
	else if (m_optionsPos == 3)
	{
		//The radio button for on
		m_radioBox[0].setFillColor(sf::Color::Red);
		m_radioBox[1].setFillColor(sf::Color::Green);
		bgSoundEngine->setAllSoundsPaused(false);

	}

}

void Options::changeMusicVol(ISoundEngine* bgSoundEngine)
{
	if (m_controller.leftButton() && m_moved == false)
	{
		//if the outer vol bar and the 
		if (m_volumnBarOuter.getPosition().x + m_volumnBarOuter.getSize().x >=
			m_volumnBarIn.getPosition().x + 10)
		{
			m_volumnBarOuter.setSize(sf::Vector2f(m_volumnBarOuter.getSize().x - 10, 50));
			bgSoundEngine->setSoundVolume(bgSoundEngine->getSoundVolume() - 0.05);
		}

	}
	if (m_controller.rightButton() && m_moved == false)
	{
		if (m_volumnBarOuter.getPosition().x + m_volumnBarOuter.getSize().x <=
			m_volumnBarIn.getPosition().x + m_volumnBarIn.getSize().x - 10)
		{
			m_volumnBarOuter.setSize(sf::Vector2f(m_volumnBarOuter.getSize().x + 10, 50));
			bgSoundEngine->setSoundVolume(bgSoundEngine->getSoundVolume() + 0.05);
		}
	}

}

bool Options::getBackgroundMusic()
{
	return m_backgrdMusic;
}
