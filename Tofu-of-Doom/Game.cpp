#include "Game.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

/// <summary>
/// Constructor for the Game class
/// </summary>
Game::Game(sf::ContextSettings t_settings)
	:
	m_window{ sf::VideoMode{ 1920, 1080, 32 }, "Tofu of Doom", sf::Style::Default, t_settings }
	, m_enemy()
	, m_enemyFollower()
	, m_player()
{
	//2D stuff
	m_enemy.setUpContent();
	m_enemyFollower.setUpContent();
	m_player.setUpContent();


	m_testRect.setFillColor(sf::Color::Red);
	m_testRect.setSize(sf::Vector2f(100, 50));
	m_testRect.setOutlineColor(sf::Color::Red);
	m_testRect.setOutlineThickness(5);
	m_testRect.setPosition(10, 20);

	initialise();
}

/// <summary>
/// Destructor for the Game class
/// </summary>
Game::~Game()
{

}

/// <summary>
/// Run
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);

	while (m_window.isOpen() && !m_exitGame)
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();

		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
			render();
		}
	}
}

void Game::initialise()
{

	engine = createIrrKlangDevice();

	shotgun = engine->play2D("gun.mp3", false , true);
	/*pistol = engine->play2D("gun.mp3", false, true);
	machinegun = engine->play2D("gun.mp3", false, true);*/

	//name of file , position in 3D space , play loop , start paused , track
	background = engine->play2D("Zombie_Horde.mp3" , true);
	int gunNum = 1;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (gunNum == 1)
		{
			// left mouse button is pressed
			// play some sound stream, looped
			engine->play2D("shotgun.mp3", false);
		}
		//if (gunNum == 2)
		//{
		//	// left mouse button is pressed
		//	// play some sound stream, looped
		//	engine->play2D("Minigun.mp3", false);
		//}
		//if (gunNum == 3)
		//{
		//	// left mouse button is pressed
		//	// play some sound stream, looped
		//	engine->play2D("9mm.mp3", false);
		//}
	}


	/*if (music)
		music->setMinDistance(5.0f);*/




	for (int i = 0; i < ROOM_NUMBERS; i++)
	{
		anotherRoom[i].initialise(); 
		anotherRoom[i].transform.position.x += (i * 10);
		anotherRoom[i].setPosition();
		
	}



	//ISound* zombieEnemies;
	//vec3df positionEnemies;
	

	//for (int i = 0; i < 11; i++)
	//{
	//	j += 10;
	//	positionEnemies[i](anotherRoom[j].transform.position.x, anotherRoom[j].transform.position.y, 
	//		anotherRoom[j].transform.position.z);

	//	zombieEnemies[i] = engine->play3D("Mindless Zombie Awakening.mp3", positionEnemies[i], true, true, true);
	//	
	//	if (zombie[i])
	//	{
	//		zombie[i]->setMinDistance(30.0f); // a loud sound
	//		zombie[i]->setIsPaused(false); // unpause the sound
	//	}

	//}
	vec3df position(anotherRoom[5].transform.position.x, anotherRoom[5].transform.position.y, 
		anotherRoom[5].transform.position.z);
	zombie = engine->play3D("Mindless Zombie Awakening.mp3", position, true, true, true);


	if (zombie)
	{
		zombie->setMinDistance(30.0f); // a loud sound
		zombie->setIsPaused(false); // unpause the sound
	}
	// Load texture
	filename = "cottage-texture.png";
	stbi_set_flip_vertically_on_load(false);
	texture_data = stbi_load(filename.c_str(), &width, &height, &comp_count, 3);

	glGenTextures(1, &Texture);
	glBindTexture(GL_TEXTURE_2D, Texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);



	for (int i = 0; i < ROOM_NUMBERS; i++)
	{
		/*if (distance(cameraPos, anotherRoom[i].position) < 50)
		{*/

		glGenBuffers(1, &vertexbuffer[i]);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[i]);
		glBufferData(GL_ARRAY_BUFFER, anotherRoom[i].getVertices().size() * sizeof(glm::vec3), &anotherRoom[i].getVertices()[0], GL_STATIC_DRAW);


	}

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, anotherRoom[0].getUvs().size() * sizeof(glm::vec2), &anotherRoom[0].getUvs()[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, anotherRoom[0].getNormals().size() * sizeof(glm::vec3), &anotherRoom[0].getNormals()[0], GL_STATIC_DRAW);



	/*bool res = m_modelLoader.loadOBJ("cottage.obj", vertices, uvs, normals);*/
	int v = 0;
	
	/*for (int i = 0; i < vertices.size(); i++)
	{
		vertices[i].x += 90;
		std::cout << std::to_string(vertices[i].x) << std::endl;

	}*/
	//std::cout << "There are " << std::to_string(v) << std::endl;
	GLuint m_error = glewInit(); // Initialise GLEW

	// Load vertex and fragment shader files into shader objects
	m_genericShader = new tk::Shader("Standard.vert", "Standard.frag");

	GLint isCompiled = 0;
	GLint isLinked = 0;
	
	// Projection matrix 
	projection = glm::perspective(45.0f, 4.0f / 3.0f, 1.0f, 500.0f);

	// Model matrix
	model = glm::mat4(glm::translate(glm::mat4(1), glm::vec3(10.0f, 0.0f, 0.0f)));

	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Get a handle for our "MVP" uniform
	// Only during the initialisation
	MatrixID = glGetUniformLocation(m_genericShader->m_programID, "MVP");
	ViewMatrixID = glGetUniformLocation(m_genericShader->m_programID, "V");
	ModelMatrixID = glGetUniformLocation(m_genericShader->m_programID, "M");

	// Get a handle for our "myTextureSampler" uniform
	TextureID = glGetUniformLocation(m_genericShader->m_programID, "myTextureSampler");

	LightID = glGetUniformLocation(m_genericShader->m_programID, "LightPosition_worldspace");
}

/// <summary>
/// Process events
/// </summary>
void Game::processEvents()
{
	sf::Event event;

	while (m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			m_window.close();
		}

		if (sf::Event::KeyPressed == event.type)
		{
			if (sf::Keyboard::Escape == event.key.code)
			{
				m_exitGame = true;
			}
		}
	}
}

/// <summary>
/// Update
/// </summary>
void Game::update(sf::Time t_deltaTime)
{

	//sf::Time dt = sf::seconds(1.f / 60.f);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		m_timerStart = true;
		// left mouse button is pressed
		// play some sound stream, looped
		shotgun->setIsPaused(false);
	}
	//shotgun->setIsPaused(true);
	
	
	
	//2D stuff
	m_playerRect = m_player.getPlayer();
	m_enemy.update();
	m_enemyFollower.update(m_playerRect);
	m_player.update();
	bool move = false;

	// Update game controls
	camera.input(t_deltaTime);

	// Update model view projection
	mvp = projection * camera.getView() * model;

	
	irrklang::vec3df position(camera.transform.position.x, camera.transform.position.y, camera.transform.position.z);        // position of the listener
	irrklang::vec3df lookDirection(10, 0, 10); // the direction the listener looks into
	irrklang::vec3df velPerSecond(0, 0, 0);    // only relevant for doppler effects
	irrklang::vec3df upVector(0, 1, 0);        // where 'up' is in your 3D scene

	engine->setListenerPosition(position, lookDirection, velPerSecond, upVector);
	/// <summary>
	/// This moves objects
	/// </summary>
	/// <param name="t_deltaTime"></param>
	for (int i = 0; i < ROOM_NUMBERS; i++)
	{
		// Do soemthing like this if we have many enemies on screen to boost performance
		if (Transform::distance(anotherRoom[i].transform.position, camera.transform.position) < 50)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
			{
				// play some sound stream, looped
				std::cout << "Y" << std::endl;
				anotherRoom[i].transform.position.z += 1;
				anotherRoom[i].setPosition();
				move = true;
				timer = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
			{
				std::cout << "U" << std::endl;
				anotherRoom[i].transform.position.y += 1;
				anotherRoom[i].setPosition();
				move = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
			{
				std::cout << "I" << std::endl;
				anotherRoom[i].transform.position.x += 1;
				anotherRoom[i].setPosition();
				move = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				std::cout << "P" << std::endl;
				anotherRoom[i].transform.position.x -= 1;
				anotherRoom[i].setPosition();
				move = true;
			}

			if (move)
			{
				// update bind buffer
				glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[i]);
				glBufferData(GL_ARRAY_BUFFER, anotherRoom[i].getVertices().size() * sizeof(glm::vec3), &anotherRoom[i].getVertices()[0], GL_STATIC_DRAW);
			}
		}
		
		// end of moving objects in 3D space
	}

	// Send our transformation to the currently bound shader, in the "MVP" uniform
	// This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &camera.getView()[0][0]);

	glm::vec3 lightPos = glm::vec3(0, 3, 0);
	camera.transform.position.x = camera.getEye().x;
	camera.transform.position.y = camera.getEye().y;
	camera.transform.position.z = camera.getEye().z;

	// glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z); // Static light position
	glUniform3f(LightID, camera.getEye().x, camera.getEye().y, camera.getEye().z);
}

/// <summary>
/// Render
/// </summary>
void Game::render()
{
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_window.clear();




	DrawRooms();


	
	m_window.display();
	// Check for OpenGL error code
	error = glGetError();

	if (error != GL_NO_ERROR)
	{
		DEBUG_MSG(error);
	}
}





void Game::DrawRooms()
{
	//// This is where any SFML related stuff can be drawn
	//m_window.pushGLStates();

	///////////////////////////////////////
	//// SFML draw stuff can go in here! //
	
		//2D stuff
	//m_window.draw(m_testRect);
	//m_enemy.render(m_window);
	//m_enemyFollower.render(m_window);
	//m_player.render(m_window);

	///////////////////////////////////////

	//m_window.popGLStates(); // End of SFML stuff


	for (int i = 0; i < ROOM_NUMBERS; i++)
	{
		if (Transform::distance(anotherRoom[i].transform.position, camera.transform.position) < 50)
		{

			// Use our shader
			glUseProgram(m_genericShader->m_programID);

			// Bind our texture in Texture Unit 0
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, Texture);

			// Set our "myTextureSampler" sampler to use Texture Unit 0
			glUniform1i(TextureID, 0);

			// Vertices buffer
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[i]);
			glVertexAttribPointer(
				0,                  // attribute
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				0,                  // stride
				(void*)(0)       // array buffer offset
			);

			// UV buffer
			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
			glVertexAttribPointer(
				1,								  // attribute
				2,                                // size
				GL_FLOAT,                         // type
				GL_FALSE,                         // normalized?
				0,                                // stride
				(void*)(0)                       // array buffer offset
			);

			// Normals buffer
			glEnableVertexAttribArray(2);
			glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
			glVertexAttribPointer(
				2,                                // attribute
				3,                                // size
				GL_FLOAT,                         // type
				GL_FALSE,                         // normalized?
				0,                                // stride
				(void*)(0)                          // array buffer offset
			);


			glDrawArrays(GL_TRIANGLES, 0, anotherRoom[i].getVertices().size() * sizeof(glm::vec3));

			// Draw

			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);
		} // end distance check
	}
}


