#include "Credits.h"

Credits::Credits(Game & t_game, sf::Font t_font) :
	m_game{ t_game },
	m_font{ t_font }

{
	//function to set up content and the file output
	setUpContent();
	fileOutput();

}

Credits::~Credits()
{
}



void Credits::update(sf::Time t_deltaTime)
{
	//move the credits up the screen
	m_creditText.setPosition(m_creditText.getPosition() + sf::Vector2f{ 0 , -2 });
	//if the position of the start of the text is 1100 outside of screen
	if(m_creditText.getPosition().y <= -1100.0f)
	{
		//set the gamestate to main menu
		m_game.m_currentGameState = GameState::Main;

	}
	
	

}
/// <summary>
/// file output 
/// what will be output by the file when called
/// </summary>
void Credits::fileOutput()
{
	//sets file and opens it
	std::ifstream file;
	file.open("Credits.txt");
	//checks if the load failed and outputs messgae if so
	if (file.fail())
	{
		cout << "fail" << endl;
	}
	//checks if file is open
	else if (file.is_open())
	{
		
		//if its not the end of the file
		while (!file.eof())
		{
			//gets the line
			getline(file, line);
			//appends so as to get next
			output.append(line + "\n");

		}
	}
	//sets the text of the line
	m_creditText.setString(output);
}
/// render to t_window
/// </summary>
/// <param name="t_window"></param>
void Credits::render(sf::RenderWindow & t_window)
{

	t_window.clear(sf::Color::Black);
	//draw  , credits message and title
	t_window.draw(m_creditText);
	t_window.draw(m_titleText);
	t_window.display();
}

void Credits::setUpContent()
{
	//sets the text font,position ,size and color
	m_creditText.setFont(m_font);
	m_creditText.setPosition(300.0f, 550.0f);
	m_creditText.setCharacterSize(60);
	m_creditText.setFillColor(sf::Color::White);
	
	//sets the text font,position ,size and color
	m_titleText.setFont(m_font);
	m_titleText.setPosition(50.0f, 50.0f);
	m_titleText.setCharacterSize(60);
	m_titleText.setFillColor(sf::Color::Yellow);
	m_titleText.setString("CREDITS");
}


	

		
	
