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
	delete m_mainShader;
}

/// <summary>
/// Run
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Clock gunClock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds((1.f / 35.0f));

	m_deltaTime = timePerFrame;

	while (m_window.isOpen() && !m_exitGame)
	{
		timeSinceLastUpdate += clock.restart();

		if(timeSinceLastUpdate > timePerFrame)
		{
			m_time += gunClock.restart();
			processEvents();
			update(timePerFrame);
			render();
			timeSinceLastUpdate -= timePerFrame;
			processEvents();

		}

		
	}
}

/// <summary>
/// Initialise OpenGL and load models and textures
/// </summary>
void Game::initialise()
{
	// Set light positions (this will be put into a level loader probably)
	for (int i = 0; i < LIGHT_AMOUNT; ++i)
	{
		glm::vec3 f_temp = glm::vec3(m_gameWorld->getLightPositions()->at(i).x / s_displayScale, m_gameWorld->getLightPositions()->at(i).y / s_displayScale, m_gameWorld->getLightPositions()->at(i).z / s_displayScale);
		m_lightPositions.push_back(f_temp);
	}

	graph = new Graph<NodeData, int>(25);
	m_ShotDelay = sf::seconds(.7f); // .7f is the length for the reload sound to finish
	m_vibrateLength = sf::seconds(.1f); // .7f is the length for the reload sound to finish
	soundEngine = createIrrKlangDevice();
	gunSoundEngine = createIrrKlangDevice();
	//name of file , position in 3D space , play loop , start paused , track
	background = soundEngine->play2D("horror.mp3" , true);
	glm::vec3 soundPos(25, 0, 25);
	vec3df position(25, 0, 25);
	positions.push_back(position);

	shotgunSound = soundEngine->addSoundSourceFromFile("shotgun.mp3");
	machinegunSound = soundEngine->addSoundSourceFromFile("cg1.wav");
	pistolSound = soundEngine->addSoundSourceFromFile("9mm.mp3");
	zombie = soundEngine->addSoundSourceFromFile("Monster.mp3");
	shotgunQueue.push(shotgunSound); // 4
	shotgunQueue.push(machinegunSound); // 3
	shotgunQueue.push(pistolSound); // 2
	shotgunQueue.push(shotgunSound); // 1

	
	zombiePosition = vec3df(m_gameWorld->getEnemyPosition().x, 0 , m_gameWorld->getEnemyPosition().y);

	soundEngine->play3D(zombie, zombiePosition, true, false, false, false);

	

	//Astar stuff
	// List all neighbors:
	for (int direction = 0; direction < 9; direction++)
	{
		if (direction == 4) continue; // Skip 4, this is ourself.

		int n_row = row + ((direction % 3) - 1); // Neighbor row
		int n_col = col + ((direction / 3) - 1); // Neighbor column

		// Check the bounds:
		if (n_row >= 0 && n_row < ROWS && n_col >= 0 && n_col < COLS) 
		{
			//graph->addArc(1, 2, 10);
			// Add an arc from cell id 24 to cell id arr[n_row][n_col] 
			// A valid neighbor:
			//std::cout << "Neighbor: " << n_row << "," << n_col << ": " << arr[n_row][n_col] << std::endl;
		}
	}


	//zombie = soundEngine->play3D("Monster.mp3", zombiePosition, true, true, true);
	//
	//if (zombie)
	//{
	//	zombie->setMinDistance(15.0f); // a loud sound
	//	zombie->setIsPaused(false); // unpause the sound
	//}
	

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
	m_mainShader = new tk::Shader("shaders/mainShader.vert", "shaders/mainShaderMultipleLights.frag");

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
	
	loadVAO("models/rifle/rifle.png", "models/rifle/rifle.obj", rifle_VAO_ID, rifle_VBO_ID,
		rifle_normalBufferID, rifle_textureID, rifle_texture, rifle_uvBufferID, rifle_vertices, rifle_uvs, rifle_normals);

	loadVAO("models/pistol/pistol.jpg", "models/pistol/pistol.obj", pistol_VAO_ID, pistol_VBO_ID,
		pistol_normalBufferID, pistol_textureID, pistol_texture, pistol_uvBufferID, pistol_vertices, pistol_uvs, pistol_normals);

	loadVAO("models/enemyTest/enemyTest.png", "models/enemyTest/enemyTest.obj", enemyTest_VAO_ID, enemyTest_VBO_ID,
		enemyTest_normalBufferID, enemyTest_textureID, enemyTest_texture, enemyTest_uvBufferID, enemyTest_vertices, enemyTest_uvs, enemyTest_normals);
	
	// Projection matrix 
	projection = glm::perspective(45.0f, 4.0f / 3.0f, 1.0f, 1000.0f); // Enable depth test

	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Uniforms for model, view and projection matrices
	m_modelMatrixID = glGetUniformLocation(m_mainShader->m_programID, "M");
	m_viewMatrixID = glGetUniformLocation(m_mainShader->m_programID, "V");
	m_projectionMatrixID = glGetUniformLocation(m_mainShader->m_programID, "P");	

	// Other uniforms
	m_currentTextureID = glGetUniformLocation(m_mainShader->m_programID, "currentTexture");
	m_lightID = glGetUniformLocation(m_mainShader->m_programID, "LightPosition_worldspace");
	m_lightPositionsID = glGetUniformLocation(m_mainShader->m_programID, "lightPositionsWorldspace");
	m_muzzleFlashIntensityID = glGetUniformLocation(m_mainShader->m_programID, "muzzleFlashIntensity");
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

	//======DEBUG COLLISION ====//
	// system("cls");
	/*std::cout << "Player: " << "x: " << camera.collider.bounds.x1 <<
		"y: " << camera.collider.bounds.y1 << " x2: " << camera.collider.bounds.x2 << " y2: " << camera.collider.bounds.y2 << std::endl;
	std::cout << "cube: " << "x: " << cubeCollider.bounds.x1 <<
		"y: " << cubeCollider.bounds.y1 << " x2: " << cubeCollider.bounds.x2 << " y2: " << cubeCollider.bounds.y2 << std::endl;*/
	if (Collider2D::isColliding(camera.collider.bounds, cubeCollider.bounds))
	{
	//	std::cout << "Working" << std::endl;
	}

	//update the zombie sound position to follow test zombie
	zombiePosition = vec3df(m_gameWorld->getEnemyPosition().x, 3.5f, m_gameWorld->getEnemyPosition().y); 
	

	// Update game controls
	camera.input(t_deltaTime);
	camera.transform.position.x = camera.getEye().x;
	camera.transform.position.y = camera.getEye().y;
	camera.transform.position.z = camera.getEye().z;


	fireGun();

	// std::cout << m_time.asSeconds() << std::endl;

	// This is currently only used to display the mini-map
	gameControls(t_deltaTime);


	m_gameWorld->updateWorld();

	// Update view (camera)
	camera.getView() = camera.camera(m_gameWorld->getCameraPosition(), m_gameWorld->getPitch(), m_gameWorld->getYaw());

	// Sound stuff
	irrklang::vec3df position(m_gameWorld->getCameraPosition().x , m_gameWorld->getCameraPosition().y, m_gameWorld->getCameraPosition().z);        // position of the listener
	irrklang::vec3df lookDirection(10, 0, 10); // the direction the listener looks into
	irrklang::vec3df velPerSecond(0, 0, 0);    // only relevant for doppler effects
	irrklang::vec3df upVector(0, 1, 0);        // where 'up' is in your 3D scene

	soundEngine->setListenerPosition(position, lookDirection, velPerSecond, upVector);

	// Test cube
	model_2 = glm::translate(glm::mat4(1.0f), glm::vec3(15.0f, 0.0f, 15.0f));
	cubeCollider.bounds.x1 = 10;
	cubeCollider.bounds.x2 = 20;
	cubeCollider.bounds.y1 = 10;
	cubeCollider.bounds.y2 = 20;
	//============================================================================== DEBUG ONLY 


	// Send our transformation to the currently bound shader, in the "MVP" uniform
	// This is done in the update loop since each model will have a different MVP matrix (At least for the M part)
	glUniformMatrix4fv(m_viewMatrixID, 1, GL_FALSE, &camera.getView()[0][0]);
	glUniformMatrix4fv(m_projectionMatrixID, 1, GL_FALSE, &projection[0][0]);

	glm::vec3 lightPos = camera.getEye();
	glUniform3f(m_lightID, lightPos.x, lightPos.y, lightPos.z);

	// Send array of light positions to shader
	glUniform3fv(m_lightPositionsID, LIGHT_AMOUNT * sizeof(glm::vec3), &m_lightPositions[0][0]);

	// Update test enemy matrix
	model_8 = glm::translate(glm::mat4(1.0f), glm::vec3(m_gameWorld->getEnemyPosition().x, 3.5f, m_gameWorld->getEnemyPosition().y));
	model_8 = glm::scale(model_8, glm::vec3(0.5f, 0.5f, 0.5f));
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
		glUseProgram(m_mainShader->m_programID);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, wallType1_texture);

		// Set shader to use Texture Unit 0
		glUniform1i(m_currentTextureID, 0);

		glBindVertexArray(wallType1_VAO_ID);		

		glm::vec3 f_offset(0.0f, 50.0f, 0.0f);

		for (int i = 0; i < m_gameWorld->getWallData()->size(); ++i)
		{
			if (m_gameWorld->getWallData()->at(i).second == WallType::WALLTYPE_1)
			{
				model_1 = glm::translate(glm::mat4(1.0f), m_gameWorld->getWallData()->at(i).first / s_displayScale);
				glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &model_1[0][0]);
				glDrawArrays(GL_TRIANGLES, 0, wallType1_vertices.size());

				model_1 = glm::translate(glm::mat4(1.0f), (m_gameWorld->getWallData()->at(i).first + f_offset) / s_displayScale);
				glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &model_1[0][0]);
				glDrawArrays(GL_TRIANGLES, 0, wallType1_vertices.size());

				model_1 = glm::translate(glm::mat4(1.0f), (m_gameWorld->getWallData()->at(i).first + (f_offset * 2.0f)) / s_displayScale);
				glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &model_1[0][0]);
				glDrawArrays(GL_TRIANGLES, 0, wallType1_vertices.size());

			}
		}	

		// Draw floors and ceilings
		for (int i = 0; i < m_gameWorld->getWallData()->size(); ++i)
		{
			// Floor
			model_1 = glm::translate(glm::mat4(1.0f), (m_gameWorld->getWallData()->at(i).first - f_offset) / s_displayScale);
			glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &model_1[0][0]);
			glDrawArrays(GL_TRIANGLES, 0, wallType1_vertices.size());

			// Ceiling
			model_1 = glm::translate(glm::mat4(1.0f), (m_gameWorld->getWallData()->at(i).first + (f_offset * 3.0f)) / s_displayScale);
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
		
		// This section contains the machine gun draw data
		if (gunNum == 3)
		{
			// Bind our texture in Texture Unit 2
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, machineGun_texture);

			// Set shader to use Texture Unit 2
			glUniform1i(m_currentTextureID, 2);

			glBindVertexArray(machineGun_VAO_ID);

			gunAnimation(model_3); // Does nothing if recoil is false

			glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &model_3[0][0]);
			glDrawArrays(GL_TRIANGLES, 0, machineGun_vertices.size());
			glBindVertexArray(0);
		}

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

		// This section contains the rifle draw data
		if (gunNum == 2)
		{
			// Bind our texture in Texture Unit 5
			glActiveTexture(GL_TEXTURE5);
			glBindTexture(GL_TEXTURE_2D, rifle_texture);

			// Set shader to use Texture Unit 5
			glUniform1i(m_currentTextureID, 5);

			glBindVertexArray(rifle_VAO_ID);

			gunAnimation(model_6); // Does nothing if recoil is false

			glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &model_6[0][0]);
			glDrawArrays(GL_TRIANGLES, 0, rifle_vertices.size());
			glBindVertexArray(0);
		}

		// ---------------------------------------------------------------------------------------------------------------------

		// This section contains the pistol draw data
		if (gunNum == 1)
		{
			// Bind our texture in Texture Unit 6
			glActiveTexture(GL_TEXTURE6);
			glBindTexture(GL_TEXTURE_2D, pistol_texture);

			// Set shader to use Texture Unit 6
			glUniform1i(m_currentTextureID, 6);

			glBindVertexArray(pistol_VAO_ID);

			gunAnimation(model_7); // Does nothing if recoil is false

			glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &model_7[0][0]);
			glDrawArrays(GL_TRIANGLES, 0, pistol_vertices.size());
			glBindVertexArray(0);
		}

		// ---------------------------------------------------------------------------------------------------------------------
		// Bind our texture in Texture Unit7
		glActiveTexture(GL_TEXTURE7);
		glBindTexture(GL_TEXTURE_2D, enemyTest_texture);

		// Set shader to use Texture Unit 7
		glUniform1i(m_currentTextureID, 7);
		glBindVertexArray(enemyTest_VAO_ID);		

		glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &model_8[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, enemyTest_vertices.size());
		glBindVertexArray(0);

		// ---------------------------------------------------------------------------------------------------------------------
		
		// Reset OpenGL
		glBindVertexArray(GL_NONE);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE0);

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
	if (camera.controller.backButtonDown() && !backButtonPressed)
	{
		backButtonPressed = true;
	}
	else if (!camera.controller.backButtonDown() && backButtonPressed)
	{
		if (m_drawState == DrawState::GAME)
		{
			m_drawState = DrawState::MAP;
		}
		else
		{
			m_drawState = DrawState::GAME;
		}

		backButtonPressed = false;
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

	stbi_image_free(f_data); // Unload data from CPU as it's on the GPU now

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

/// <summary>
/// This functions handles gun recoil
/// </summary>
void Game::gunAnimation(glm::mat4 &t_gunMatrix)
{
	glm::vec3 gunDirection(camera.getDirection().x, 1.5f, camera.getDirection().z);

	if (!gunRecoil)
	{
		t_gunMatrix = glm::translate(glm::mat4(1.0f), camera.getEye());
	}
	else
	{
		t_gunMatrix = glm::translate(glm::mat4(1.0f), camera.getEye() + camera.getDirection());
	}

	t_gunMatrix = glm::rotate(t_gunMatrix, glm::radians(camera.getYaw()), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Game::fireGun()
{

	if (gunNum == 1)
	{
		if (camera.controller.rightTriggerDown())
		{
			m_gameWorld->fireBullet(gunNum);

			gunSoundEngine->play2D(pistolSound);
			/*if (gunSoundEngine->isCurrentlyPlaying(shotgunSound) == false)
			{

				shotgunQueue.pop();
			}*/

			m_time = sf::Time::Zero;
			m_time = m_time.Zero;

			if (camera.isCameraShaking() == false)
			{
				camera.setCameraShake(true);
			}

			vibrate = true;
			camera.controller.Vibrate(65535, 65535);

			m_muzzleFlashIntensity = 300.0f;
			gunRecoil = true; // If the gun is being shot, create some recoil
		}
		else
		{
			m_muzzleFlashIntensity = 0.0f;
		}
	}
	else if (gunNum == 2 && m_time > m_ShotDelay) // Rifle
	{
		if (camera.controller.rightTriggerDown())
		{

			m_gameWorld->fireBullet(gunNum);

			gunSoundEngine->play2D(shotgunQueue.front());
			m_time = sf::Time::Zero;
			m_time = m_time.Zero;

			if (camera.isCameraShaking() == false)
			{
				camera.setCameraShake(true);
			}

			vibrate = true;
			camera.controller.Vibrate(65535, 65535);

			m_muzzleFlashIntensity = 300.0f;
			gunRecoil = true; // If the gun is being shot, create some recoil
		}
		else
		{
			m_muzzleFlashIntensity = 0.0f;
		}
	}
	else if (gunNum == 3 && m_time > m_ShotDelay / (float)6) // Machine gun
	{
		// Fire a shot with chosen gun
		if (camera.controller.rightTrigger())
		{

			m_gameWorld->fireBullet(gunNum);

			gunSoundEngine->play2D(machinegunSound);
			m_time = sf::Time::Zero;
			m_time = m_time.Zero;

			if (camera.isCameraShaking() == false)
			{
				camera.setCameraShake(true);
			}
			vibrate = true;
			camera.controller.Vibrate(65535, 65535);

			m_muzzleFlashIntensity = 300.0f;
			gunRecoil = true; // If the gun is being shot, create some recoil
		}
		else
		{
			m_muzzleFlashIntensity = 0.0f;
		}
	}

	// Recoil 
	if (m_vibrateLength < m_time)
	{
		vibrate = false;
		camera.controller.Vibrate(0, 0);

		gunRecoil = false; // Gun is not being fired, disable recoil

		// Switch between guns, but only when a shot being fired is finished, and only when the Y button is released
		if (camera.controller.yButtonDown() && !yButtonPressed)
		{
			yButtonPressed = true;
		}
		else if (!camera.controller.yButtonDown() && yButtonPressed)
		{
			gunNum++;

			if (gunNum == 4)
			{
				gunNum = 1;
			}

			if (gunNum % 2 == 0)
			{
				camera.setCameraShakeMax(8);
				camera.setCameraShakeSpeed(2);
			}
			else
			{
				camera.setCameraShakeMax(4);
				camera.setCameraShakeSpeed(2);
			}

			yButtonPressed = false;
		}
	}

	glUniform1f(m_muzzleFlashIntensityID, m_muzzleFlashIntensity);
	camera.cameraShake();
}

void Game::moveEnemy(glm::mat4& t_gunMatrix)
{
}


