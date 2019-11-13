#include "Game.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

/// <summary>
/// Constructor for the Game class
/// </summary>
Game::Game(sf::ContextSettings t_settings)
	:
	m_window{ sf::VideoMode{ 1280, 720, 32 }, "Tofu of Doom", sf::Style::Default, t_settings }
{
	// Initialise GLEW
	GLuint m_error = glewInit();

	// Initialise everything else
	initialise();
}

/// <summary>
/// Destructor for the Game class
/// </summary>
Game::~Game()
{
	delete m_genericShader;
}

/// <summary>
/// Run
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Clock gunClock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);

	m_deltaTime = timePerFrame;

	while (m_window.isOpen() && !m_exitGame)
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();

		while (timeSinceLastUpdate > timePerFrame)
		{
			m_time += gunClock.restart();
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
			render();
		}
	}
}

/// <summary>
/// Initialise OpenGL and load models and textures
/// </summary>
void Game::initialise()
{
	m_ShotDelay = sf::seconds(.7f); // .7f is the length for the reload sound to finish
	m_vibrateLength = sf::seconds(.1f); // .7f is the length for the reload sound to finish
	soundEngine = createIrrKlangDevice();

	//name of file , position in 3D space , play loop , start paused , track
	background = soundEngine->play2D("horror.mp3" , true);
	glm::vec3 soundPos(25, 0, 25);
	vec3df position(25, 0, 25);
	positions.push_back(position);


	//for (int i = 0; i < 11; i++)
	//{
	//	
	///*	positionEnemies[i].X = anotherRoom[j].transform.position.x;
	//	positionEnemies[i].Y = anotherRoom[j].transform.position.y;
	//	positionEnemies[i].Z = anotherRoom[j].transform.position.z;*/
	//	
	//	zombieEnemies[i] = soundEngine->play3D("Mindless Zombie Awakening.mp3", position, true, true, true);

	//	//if (zombieEnemies[i])
	//	//{
	//	//	zombieEnemies[i]->setMinDistance(5.0f); // a loud sound
	//	//	zombieEnemies[i]->setIsPaused(false); // unpause the sound
	//	//}

	//}
	//
	//zombie = soundEngine->play3D("Mindless Zombie Awakening.mp3", position, true, true, true);
	//if (zombie)
	//{
	//	zombie->setMinDistance(30.0f); // a loud sound
	//	zombie->setIsPaused(false); // unpause the sound
	//}
	


	// Load shader
	m_genericShader = new tk::Shader("Standard.vert", "Standard.frag");

	GLint isCompiled = 0;
	GLint isLinked = 0;

	// Load models and textures and bind to VAOs
	loadVAO("models/wallType1/wallType1.png", "models/wallType1/wallType1.obj", wallType1_VAO_ID, wallType1_VBO_ID,
		wallType1_normalBufferID, wallType1_textureID, wallType1_texture, wallType1_uvBufferID, wallType1_vertices, wallType1_uvs, wallType1_normals);

	loadVAO("models/wallType2/wallType2.png", "models/wallType2/wallType2.obj", wallType2_VAO_ID, wallType2_VBO_ID,
		wallType2_normalBufferID, wallType2_textureID, wallType2_texture, wallType2_uvBufferID, wallType2_vertices, wallType2_uvs, wallType2_normals);

	loadVAO("models/machineGun/machineGun.png", "models/machineGun/machineGun.obj", machineGun_VAO_ID, machineGun_VBO_ID,
		machineGun_normalBufferID, machineGun_textureID, machineGun_texture, machineGun_uvBufferID, machineGun_vertices, machineGun_uvs, machineGun_normals);
	   
	loadVAO("models/oilDrum/oilDrum.jpg", "models/oilDrum/oilDrum.obj", oilDrum_VAO_ID, oilDrum_VBO_ID,
		oilDrum_normalBufferID, oilDrum_textureID, oilDrum_texture, oilDrum_uvBufferID, oilDrum_vertices, oilDrum_uvs, oilDrum_normals);
	
	loadVAO("models/fireExtinguisher/fireExtinguisher.png", "models/fireExtinguisher/fireExtinguisher.obj", fireExtinguisher_VAO_ID, fireExtinguisher_VBO_ID,
		fireExtinguisher_normalBufferID, fireExtinguisher_textureID, fireExtinguisher_texture, fireExtinguisher_uvBufferID, fireExtinguisher_vertices, fireExtinguisher_uvs, fireExtinguisher_normals);
	
	// Projection matrix 
	projection = glm::perspective(45.0f, 4.0f / 3.0f, 1.0f, 1000.0f); // Enable depth test

	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Uniforms for model, view and projection matrices
	m_modelMatrixID = glGetUniformLocation(m_genericShader->m_programID, "M");
	m_viewMatrixID = glGetUniformLocation(m_genericShader->m_programID, "V");
	m_projectionMatrixID = glGetUniformLocation(m_genericShader->m_programID, "P");	

	// Other uniforms
	m_currentTextureID = glGetUniformLocation(m_genericShader->m_programID, "currentTexture");
	m_lightID = glGetUniformLocation(m_genericShader->m_programID, "LightPosition_worldspace");
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
	m_gameWorld->updateWorld();

	// Update game controls
	camera.input(t_deltaTime);


	camera.transform.position.x = camera.getEye().x;
	camera.transform.position.y = camera.getEye().y;
	camera.transform.position.z = camera.getEye().z;


	// Update model view projection
	// mvp = projection * camera.getView() * model_1;

	if (camera.controller.aButtonDown())
	{

		if (gunNum == 1 && m_time > m_ShotDelay)
		{
			// left mouse button is pressed
			// play some sound stream, looped

			soundEngine->play2D("shotgun.mp3", false);
			m_time = sf::Time::Zero;
			m_time = m_time.Zero;

			vibrate = true;
			camera.controller.Vibrate(65535, 65535);


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

	if (m_vibrateLength < m_time)
	{
		vibrate = false;
		camera.controller.Vibrate(0, 0);
	}

	// std::cout << m_time.asSeconds() << std::endl;



	// This is currently only used to display the mini-map
	gameControls(t_deltaTime);

	// Update view (camera)
	camera.getView() = camera.camera(m_gameWorld->getCameraPosition(), m_gameWorld->getPitch(), m_gameWorld->getYaw());


	irrklang::vec3df position(m_gameWorld->getCameraPosition().x , m_gameWorld->getCameraPosition().y, m_gameWorld->getCameraPosition().z);        // position of the listener
	irrklang::vec3df lookDirection(10, 0, 10); // the direction the listener looks into
	irrklang::vec3df velPerSecond(0, 0, 0);    // only relevant for doppler effects
	irrklang::vec3df upVector(0, 1, 0);        // where 'up' is in your 3D scene

	soundEngine->setListenerPosition(position, lookDirection, velPerSecond, upVector);

	// Test cube
	model_2 = glm::translate(glm::mat4(1.0f), glm::vec3(15.0f, 0.0f, 15.0f));
	
	// Gun height is fixed at a Y value of 1.5 OpenGL units
	// Gun will always face in the same direction as the camera / player
	glm::vec3 gunDirection(camera.getDirection().x, 1.5f, camera.getDirection().z);
	model_3 = glm::translate(glm::mat4(1.0f), camera.getEye() - (gunDirection * 2.0f));

	// Rotate machine gun with player (180 degrees to flip the gun so it faces in the correct direction + actual rotation)
	model_3 = glm::rotate(model_3, glm::radians(180.0f + camera.getYaw()), glm::vec3(0.0f, 1.0f, 0.0f));

	// Send our transformation to the currently bound shader, in the "MVP" uniform
	// This is done in the update loop since each model will have a different MVP matrix (At least for the M part)
	glUniformMatrix4fv(m_viewMatrixID, 1, GL_FALSE, &camera.getView()[0][0]);
	glUniformMatrix4fv(m_projectionMatrixID, 1, GL_FALSE, &projection[0][0]);

	glm::vec3 lightPos = glm::vec3(25, 8, 25);
	glUniform3f(m_lightID, lightPos.x, lightPos.y, lightPos.z);
}

/// <summary>
/// Render
/// </summary>
void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (m_drawState)
	{
	case DrawState::MAP:
		m_window.pushGLStates();
		m_gameWorld->drawWorld();
		m_window.popGLStates();

		break;

	case DrawState::GAME:
		// Use shader
		glUseProgram(m_genericShader->m_programID);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, wallType1_texture);

		// Set shader to use Texture Unit 0
		glUniform1i(m_currentTextureID, 0);

		glBindVertexArray(wallType1_VAO_ID);		

		for (int i = 0; i < m_gameWorld->getWallData()->size(); ++i)
		{
			model_1 = glm::translate(glm::mat4(1.0f), m_gameWorld->getWallData()->at(i).first / s_displayScale);
			glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &model_1[0][0]);
			glDrawArrays(GL_TRIANGLES, 0, wallType1_vertices.size());
		}	

		glBindVertexArray(0);

		// ---------------------------------------------------------------------------------------------------------------------

		// Bind our texture in Texture Unit 1
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, wallType2_texture);

		// Set shader to use Texture Unit 1
		glUniform1i(m_currentTextureID, 1);

		glBindVertexArray(wallType2_VAO_ID);
		glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &model_2[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, wallType2_vertices.size());
		glBindVertexArray(0);

		// ---------------------------------------------------------------------------------------------------------------------

		// Bind our texture in Texture Unit 2
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, machineGun_texture);

		// Set shader to use Texture Unit 2
		glUniform1i(m_currentTextureID, 2);

		glBindVertexArray(machineGun_VAO_ID);
		glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &model_3[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, machineGun_vertices.size());
		glBindVertexArray(0);

		// ---------------------------------------------------------------------------------------------------------------------

		// Bind our texture in Texture Unit 3
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, oilDrum_texture);

		// Set shader to use Texture Unit 3
		glUniform1i(m_currentTextureID, 3);

		glBindVertexArray(oilDrum_VAO_ID);

		for (int i = 0; i < 5; ++i)
		{
			model_4 = glm::translate(glm::mat4(1.0f), glm::vec3(20.0f + (i * 4.0f), -2.5f, 15.0f));
			model_4 = glm::scale(model_4, glm::vec3(i + 1, i + 1, i + 1));  // Add 1 because 0 can't be used to scale
			glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &model_4[0][0]);
			glDrawArrays(GL_TRIANGLES, 0, oilDrum_vertices.size());
		}

		glBindVertexArray(0);

		// ---------------------------------------------------------------------------------------------------------------------

		// Bind our texture in Texture Unit 4
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, fireExtinguisher_texture);

		// Set shader to use Texture Unit 4
		glUniform1i(m_currentTextureID, 4);

		glBindVertexArray(fireExtinguisher_VAO_ID);

		for (int i = 0; i < 5; ++i)
		{
			model_5 = glm::translate(glm::mat4(1.0f), glm::vec3(30.0f + (i * 0.8f), -2.5f, 20.0f));
			model_5 = glm::scale(model_5, glm::vec3(i + 1, i + 1, i + 1)); // Add 1 because 0 can't be used to scale
			glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &model_5[0][0]);
			glDrawArrays(GL_TRIANGLES, 0, fireExtinguisher_vertices.size());
		}

		glBindVertexArray(0);

		// ---------------------------------------------------------------------------------------------------------------------
		
		// Reset OpenGL
		glBindVertexArray(GL_NONE);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE0);

		// ---------------------------------------------------------------------------------------------------------------------
		
		break;
	}

	// Check for OpenGL error code
	error = glGetError();

	if (error != GL_NO_ERROR)
	{
		DEBUG_MSG(error);
	}

	m_window.display();
}



/// <summary>
/// Game controls
/// </summary>
void Game::gameControls(sf::Time t_deltaTime)
{
	m_eye = m_gameWorld->getCameraPosition();

	// Switch between game and map screen
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
	{
		if (m_drawState == DrawState::GAME)
		{
			m_drawState = DrawState::MAP;
		}
		else
		{
			m_drawState = DrawState::GAME;
		}
	}

	// Look up OR down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_pitch += 2.0 * static_cast<float>(t_deltaTime.asMilliseconds() * m_speed);

		if (m_pitch >= 85.0)
		{
			m_pitch = 85.0;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_pitch -= 2.0 * static_cast<float>(t_deltaTime.asMilliseconds() * m_speed);

		if (m_pitch <= -85.0)
		{
			m_pitch = -85.0;
		}
	}
}

/// <summary>
/// Load VAO
///  
/// This function loads a texture and model, and binds them to a given VAO
/// </summary>
void Game::loadVAO(std::string t_textureFilename, const char *t_modelFilename, GLuint &t_vaoID,
	GLuint &t_vboID, GLuint &t_normalBufferID, GLuint &t_textureID, GLuint &t_texture, GLuint &t_uvBufferID,
	std::vector<glm::vec3> &t_vertices, std::vector<glm::vec2> &t_UVs, std::vector<glm::vec3> &t_normals)
{
	// This is used to hold the texture data
	unsigned char *f_data;

	// Width, height, texture component and colour type (RGBA is the default value)
	int f_width;
	int f_height;
	int f_compCount;
	const int f_number = 4;

	// Load model texture
	stbi_set_flip_vertically_on_load(false);
	f_data = stbi_load(t_textureFilename.c_str(), &f_width, &f_height, &f_compCount, 4);

	glGenTextures(1, &t_texture);
	glBindTexture(GL_TEXTURE_2D, t_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, f_width, f_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, f_data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// Load .obj file
	if (!tk::ModelLoader::loadOBJ(t_modelFilename, t_vertices, t_UVs, t_normals))
	{
		std::cout << "Error loading model!" << std::endl;
	}

	// Initialise buffers for model
	glGenBuffers(1, &t_vboID);
	glBindBuffer(GL_ARRAY_BUFFER, t_vboID);
	glBufferData(GL_ARRAY_BUFFER, t_vertices.size() * sizeof(glm::vec3), &t_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &t_uvBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, t_uvBufferID);
	glBufferData(GL_ARRAY_BUFFER, t_UVs.size() * sizeof(glm::vec2), &t_UVs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &t_normalBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, t_normalBufferID);
	glBufferData(GL_ARRAY_BUFFER, t_normals.size() * sizeof(glm::vec3), &t_normals[0], GL_STATIC_DRAW);

	// This VAO stores all states for model
	glGenVertexArrays(1, &t_vaoID);
	glBindVertexArray(t_vaoID);

	// Vertex buffer	
	glBindBuffer(GL_ARRAY_BUFFER, t_vboID);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// UV buffer
	glBindBuffer(GL_ARRAY_BUFFER, t_uvBufferID);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Normal buffer
	glBindBuffer(GL_ARRAY_BUFFER, t_normalBufferID);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindVertexArray(0);
}


