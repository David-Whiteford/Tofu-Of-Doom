#include "Game.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <cstring>
#include <string>

/// <summary>
/// Constructor for the Game class
/// </summary>
Game::Game(sf::ContextSettings t_settings) : m_window{ sf::VideoMode(1280,720,32), "Tofu of Doom", sf::Style::Fullscreen, t_settings }
{
	// Initialise GLEW
	GLuint m_error = glewInit();
	m_window.setMouseCursorVisible(false);

	
	// Initialise everything else
	initialise();

	// Loads the SFML texture and the background music
	m_splashScreen = new SplashScreen{ *this , m_font };
	
	if (!m_sfmlTexture.loadFromFile("images/sfml.png"))
	{
		std::cout << "Can't load image! " << std::endl;
	}

	m_sfmlSprite.setTexture(m_sfmlTexture);
	m_sfmlScreen = new SFML{ *this , m_font, m_sfmlSprite };
	m_mainMenu = new MainMenu{ *this , m_font };
	m_optionsMenu = new Options{ *this,m_font };
	m_gameOver = new GameOver{ *this,m_bloodFont };
	m_window.setFramerateLimit(120);
}

/// <summary>
/// Destructor for the Game class
/// </summary>
Game::~Game()
{
	delete m_mainShader;
}

void Game::resetScreenTrans()
{
	m_mainMenu->setStartUP(true);
}

/// <summary>
/// Run
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Clock gunClock;
	sf::Time oldTime = sf::Time::Zero;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds((1.f / 60.0f));

	while (m_window.isOpen() && !m_exitGame)
	{
		m_deltaTime = clock.getElapsedTime() - oldTime;

		if (clock.getElapsedTime() > oldTime + timePerFrame)
		{
			m_time += gunClock.restart();
			processEvents();
			update(m_deltaTime);
			processEvents();
			oldTime = clock.getElapsedTime();
			render();
		}
	}
}

/// <summary>
/// Initialise OpenGL and load models and textures
/// </summary>
void Game::initialise()
{
	// Load fonr
	if (!m_font.loadFromFile("fonts/AmazDooMRight.ttf"))
	{
		std::cout << "Error loading font!" << std::endl;
	}
	if (!m_bloodFont.loadFromFile("fonts/plasdrip.ttf"))
	{
		std::cout << "Error loading font!" << std::endl;
	}

	if (!m_backgroundLooseTexture.loadFromFile("images/YouDied.jpg"))
	{
		std::cout << "Can't load image!" << std::endl;
	}
	m_backgroundLooseSprite.setTexture(m_backgroundLooseTexture);
	//Win texture for background
	if (!m_backgroundWinTexture.loadFromFile("images/YouWin.jpg"))
	{
		std::cout << "Can't load image!" << std::endl;
	}
	m_backgroundWinSprite.setTexture(m_backgroundWinTexture);
	
	// Set light positions
	for (int i = 0; i < LIGHT_AMOUNT; ++i)
	{
		glm::vec3 f_temp = glm::vec3(m_gameWorld->getLightPositions()->at(i).x / s_displayScale, m_gameWorld->getLightPositions()->at(i).y / s_displayScale, m_gameWorld->getLightPositions()->at(i).z / s_displayScale);
		m_lightPositions.push_back(f_temp);
	}

	m_ShotDelay = sf::seconds(.7f); // .7f is the length for the reload sound to finish
	m_vibrateLength = sf::seconds(.1f); // .7f is the length for the reload sound to finish
	soundEngine = createIrrKlangDevice();
	bgSoundEngine = createIrrKlangDevice();

	gunSoundEngine = createIrrKlangDevice();
	background = bgSoundEngine->play2D("audio/horror.mp3" , true);
	glm::vec3 soundPos(25, 0, 25);
	vec3df position(25, 0, 25);
	positions.push_back(position);

	shotgunSound = soundEngine->addSoundSourceFromFile("audio/shotgun.mp3");
	machinegunSound = soundEngine->addSoundSourceFromFile("audio/cg1.wav");
	pistolSound = soundEngine->addSoundSourceFromFile("audio/9mm.mp3");
	zombie = soundEngine->addSoundSourceFromFile("audio/Monster.mp3");
	outOfAmmo = soundEngine->addSoundSourceFromFile("audio/outofammo.wav");
	weaponLoad = soundEngine->addSoundSourceFromFile("audio/weapload.wav");


	ricochetOne = soundEngine->addSoundSourceFromFile("SoundEffects/Ricochet/ricochet1.wav");
	ricochet.push_back(ricochetOne);
	ricochetTwo = soundEngine->addSoundSourceFromFile("SoundEffects/Ricochet/ricochet2.wav");
	ricochet.push_back(ricochetTwo);
	ricochetThree = soundEngine->addSoundSourceFromFile("SoundEffects/Ricochet/ricochet3.wav");
	ricochet.push_back(ricochetThree);
	ricochetFour = soundEngine->addSoundSourceFromFile("SoundEffects/Ricochet/ricochet4.wav");
	ricochet.push_back(ricochetFour);
	ricochetFive = soundEngine->addSoundSourceFromFile("SoundEffects/Ricochet/ricochet5.wav");
	ricochet.push_back(ricochetFive);
	//ricochet = soundEngine->addSoundSourceFromFile("SoundEffects/Ricochet/ricochet1.wav");

	


	shotgunQueue.push(shotgunSound); // 4
	shotgunQueue.push(machinegunSound); // 3
	shotgunQueue.push(pistolSound); // 2
	shotgunQueue.push(shotgunSound); // 1	

	
	// Load shaders
	m_mainShader = new tk::Shader("shaders/mainShader.vert", "shaders/mainShader.frag");
	m_particleShader = new tk::Shader("shaders/particleShader.vert", "shaders/particleShader.frag");

	GLint isCompiled = 0;
	GLint isLinked = 0;

	// Load models and textures and bind to VAOs
	loadVAO("models/wallType1/wallType1.png", "models/wallType1/wallType1.obj", m_wallType1);
	loadVAO("models/wallType2/wallType2.png", "models/wallType2/wallType2.obj", m_wallType2);
	loadVAO("models/machineGun/machineGun.png", "models/machineGun/machineGun.obj", m_machineGun);	   
	loadVAO("models/oilDrum/oilDrum.jpg", "models/oilDrum/oilDrum.obj", m_oilDrum);	
	loadVAO("models/fireExtinguisher/fireExtinguisher.png", "models/fireExtinguisher/fireExtinguisher.obj", m_fireExt);	
	loadVAO("models/rifle/rifle.png", "models/rifle/rifle.obj", m_rifle);
	loadVAO("models/pistol/pistol.jpg", "models/pistol/pistol.obj", m_pistol);
	loadVAO("models/enemyTest/enemyTest.png", "models/enemyTest/enemyTest.obj", m_enemy);
	loadVAO("models/chair/chair.png", "models/chair/chair.obj", m_chair);
	loadVAO("models/table_1/table_1.png", "models/table_1/table_1.obj", m_table_1);
	loadVAO("models/table_2/table_2.png", "models/table_2/table_2.obj", m_table_2);
	loadVAO("models/spikeball/spikeball.png", "models/spikeball/spikeball.obj", m_enemyBall);
	loadVAO("models/skull/skull.jpg", "models/skull/skull.obj", m_enemySkull);
	loadVAO("models/eyeball/eyeball.png", "models/eyeball/eyeball.obj", m_enemyEyeball);
	
	// Projection matrix 
	projection = glm::perspective(45.0f, 4.0f / 3.0f, 1.0f, 1000.0f); // Enable depth test

	// Enable depth test and face culling
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Uniforms for model, view and projection matrices
	m_modelMatrixID = glGetUniformLocation(m_mainShader->m_programID, "M");
	m_viewMatrixID = glGetUniformLocation(m_mainShader->m_programID, "V");
	m_projectionMatrixID = glGetUniformLocation(m_mainShader->m_programID, "P");

	// This is an empty matrix for the enemy rotations
	originalEnemyRotationMatrix = glm::mat4(1.0f);

	// Other uniforms
	m_currentTextureID = glGetUniformLocation(m_mainShader->m_programID, "currentTexture");
	m_lightID = glGetUniformLocation(m_mainShader->m_programID, "LightPosition_worldspace");
	m_lightPositionsID = glGetUniformLocation(m_mainShader->m_programID, "lightPositionsWorldspace");
	m_muzzleFlashIntensityID = glGetUniformLocation(m_mainShader->m_programID, "muzzleFlashIntensity");

	// Test matrices
	m_enemySkull_modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(15.0f, 0.0f, 15.0f));
	m_enemyEyeball_modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(30.0f, 3.0f, 15.0f));
}

void Game::reload()
{
	if (camera.controller.aButtonDown())
	{
		m_gameWorld->reload(gunNum);
		gunSoundEngine->play2D(weaponLoad);
		
	}
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
	switch (m_drawState)
	{
	case DrawState::SPLASH:
		m_splashScreen->update(t_deltaTime);
		break;
	case DrawState::GAMEOVER:

		if (m_createdNewWorld == false)
		{
			camera.controller.Vibrate(0, 0);
			m_gameOver->resetTime();

			m_gameWorld = new GameWorld(m_window, m_deltaTime, &camera);
			m_createdNewWorld = true;
		}

		m_gameOver->update(t_deltaTime);
		break;
	case DrawState::MAP:
		updateWorld(t_deltaTime);
		break;

	case DrawState::MAIN:
		m_mainMenu->update(t_deltaTime, sound);
		break;

	case DrawState::OPTIONS:
		m_optionsMenu->update(t_deltaTime, bgSoundEngine);
		break;

	case DrawState::GAME:
		updateWorld(t_deltaTime);

		if (m_gameWorld->getActiveEnemyCount() == 0 ||
			m_gameWorld->getPlayerHealth() <= 0)
		{

			if (m_gameWorld->getActiveEnemyCount() == 0)
			{
				std::string TITLE_MESSAGE{ "YOU ARE THE WINNER" };
				m_gameOver->setFontText(m_font, TITLE_MESSAGE, m_backgroundWinSprite);
			}
			else if (m_gameWorld->getPlayerHealth() <= 0)
			{
				std::string TITLE_MESSAGE{ "YOU HAVE DIED" };
				m_gameOver->setFontText(m_bloodFont , TITLE_MESSAGE, m_backgroundLooseSprite);
			}
			m_drawState = DrawState::GAMEOVER;
			
			
			delete(m_gameWorld);
			m_createdNewWorld = false;
			
			/*camera.transform.position = { 400,0, 50 };*/


		}


		break;
	}
}

void Game::updateWorld(sf::Time t_deltaTime)
{
	// Check collisions
	m_gameWorld->checkPlayerRayCollsions(t_deltaTime);

	// Update game controls
	camera.input(t_deltaTime);
	camera.transform.position.x = camera.getEye().x;
	camera.transform.position.y = camera.getEye().y;
	camera.transform.position.z = camera.getEye().z;

	// Handle gun fire
	reload();
	fireGun();

	if (m_gameWorld->hitWall == true)
	{
		int randNumber = rand() % 5;

		gunSoundEngine->play2D(ricochet[randNumber]);
		m_gameWorld->hitWall = false;
		std::cout << "wall" << std::endl;
	}

	// This is currently only used to display the mini-map
	gameControls(t_deltaTime);

	// Update the gameworld
	m_gameWorld->updateWorld();

	// Update view (camera)
	camera.getView() = camera.camera(m_gameWorld->getCameraPosition(), m_gameWorld->getPitch(), m_gameWorld->getYaw());

	// Sound stuff
	irrklang::vec3df position(m_gameWorld->getCameraPosition().x, m_gameWorld->getCameraPosition().y, m_gameWorld->getCameraPosition().z);        // position of the listener
	irrklang::vec3df lookDirection(10, 0, 10); // The direction the listener looks into
	irrklang::vec3df velPerSecond(0, 0, 0); // Only relevant for doppler effects
	irrklang::vec3df upVector(0, 1, 0); // Where 'up' is in your 3D scene

	soundEngine->setListenerPosition(position, lookDirection, velPerSecond, upVector);

	// Send our transformation to the currently bound shader, in the "MVP" uniform
	// This is done in the update loop since each model will have a different MVP matrix (At least for the M part)
	glUniformMatrix4fv(m_viewMatrixID, 1, GL_FALSE, &camera.getView()[0][0]);
	glUniformMatrix4fv(m_projectionMatrixID, 1, GL_FALSE, &projection[0][0]);

	glm::vec3 lightPos = camera.getEye();
	glUniform3f(m_lightID, lightPos.x, lightPos.y, lightPos.z);

	// Send array of light positions to shader
	glUniform3fv(m_lightPositionsID, LIGHT_AMOUNT * sizeof(glm::vec3), &m_lightPositions[0][0]);
}

/// <summary>
/// Render
/// </summary>
void Game::render()
{
	m_window.clear();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (m_drawState)
	{
	case DrawState::SPLASH:
		m_window.pushGLStates();
		m_splashScreen->render(m_window);
		m_window.popGLStates();
		break;
	case DrawState::GAMEOVER:
		m_window.pushGLStates();
		m_gameOver->render(m_window);
		m_window.popGLStates();
		break;

	case DrawState::MAP:
		m_window.pushGLStates();
		m_gameWorld->drawWorld();
		m_window.popGLStates();
		break;

	case DrawState::MAIN:
		m_window.pushGLStates();
		m_mainMenu->render(m_window);
		m_window.popGLStates();
		break;

	case DrawState::OPTIONS:
		m_window.pushGLStates();
		m_optionsMenu->render(m_window);
		m_window.popGLStates();
		break;
	case DrawState::EXIT:
		m_window.close();
		break;

	case DrawState::GAME:
		drawGameScene();
		m_window.pushGLStates();

		m_gameWorld->drawUI();

		m_window.popGLStates();
		drawGameScene();
		break;
	}

	m_window.display();
}

/// <summary>
/// Draw the scene
/// </summary>
void Game::drawGameScene()
{
	// Use shader
	glUseProgram(m_mainShader->m_programID);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_wallType1.texture);

	// Set shader to use Texture Unit 0
	glUniform1i(m_currentTextureID, 0);

	glBindVertexArray(m_wallType1.VAO_ID);

	glm::vec3 f_offset(0.0f, 50.0f, 0.0f);

	for (int i = 0; i < m_gameWorld->getWallData()->size(); ++i)
	{
		if (m_gameWorld->getWallData()->at(i).second == WallType::WALLTYPE_1)
		{
			model_1 = glm::translate(glm::mat4(1.0f), m_gameWorld->getWallData()->at(i).first / s_displayScale);
			glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &model_1[0][0]);
			glDrawElements(GL_TRIANGLES, m_wallType1.indices.size(), GL_UNSIGNED_SHORT, (void*)0);

			model_1 = glm::translate(glm::mat4(1.0f), (m_gameWorld->getWallData()->at(i).first + f_offset) / s_displayScale);
			glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &model_1[0][0]);
			glDrawElements(GL_TRIANGLES, m_wallType1.indices.size(), GL_UNSIGNED_SHORT, (void*)0);

			model_1 = glm::translate(glm::mat4(1.0f), (m_gameWorld->getWallData()->at(i).first + (f_offset * 2.0f)) / s_displayScale);
			glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &model_1[0][0]);
			glDrawElements(GL_TRIANGLES, m_wallType1.indices.size(), GL_UNSIGNED_SHORT, (void*)0);
		}
	}

	// Draw floors and ceilings
	for (int i = 0; i < m_gameWorld->getWallData()->size(); ++i)
	{
		// Floor
		model_1 = glm::translate(glm::mat4(1.0f), (m_gameWorld->getWallData()->at(i).first - f_offset) / s_displayScale);
		glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &model_1[0][0]);
		glDrawElements(GL_TRIANGLES, m_wallType1.indices.size(), GL_UNSIGNED_SHORT, (void*)0);

		// Ceiling
		model_1 = glm::translate(glm::mat4(1.0f), (m_gameWorld->getWallData()->at(i).first + (f_offset * 3.0f)) / s_displayScale);
		glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &model_1[0][0]);
		glDrawElements(GL_TRIANGLES, m_wallType1.indices.size(), GL_UNSIGNED_SHORT, (void*)0);
	}

	glBindVertexArray(0);

	// This section contains the machine gun draw data
	if (gunNum == 3)
	{
		// Bind our texture in Texture Unit 2
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, m_machineGun.texture);

		// Set shader to use Texture Unit 2
		glUniform1i(m_currentTextureID, 2);

		glBindVertexArray(m_machineGun.VAO_ID);

		gunAnimation(m_machineGunModelMatrix); // Does nothing if recoil is false
		reloadAnimation(m_machineGunModelMatrix);

		glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &m_machineGunModelMatrix[0][0]);
		glDrawElements(GL_TRIANGLES, m_machineGun.indices.size(), GL_UNSIGNED_SHORT, (void*)0);
		glBindVertexArray(0);
	}

	// ---------------------------------------------------------------------------------------------------------------------

	// Bind our texture in Texture Unit 3
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, m_oilDrum.texture);

	// Set shader to use Texture Unit 3
	glUniform1i(m_currentTextureID, 3);

	glBindVertexArray(m_oilDrum.VAO_ID);

	for (int i = 0; i < m_gameWorld->getOilDrumPositions()->size(); ++i)
	{
		m_oilDrumModelMatrix = glm::translate(glm::mat4(1.0f), m_gameWorld->getOilDrumPositions()->at(i) / s_displayScale);
		m_oilDrumModelMatrix = glm::scale(m_oilDrumModelMatrix, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &m_oilDrumModelMatrix[0][0]);
		glDrawElements(GL_TRIANGLES, m_oilDrum.indices.size(), GL_UNSIGNED_SHORT, (void*)0);
	}

	glBindVertexArray(0);

	// ---------------------------------------------------------------------------------------------------------------------

	// Bind our texture in Texture Unit 4
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, m_fireExt.texture);

	// Set shader to use Texture Unit 4
	glUniform1i(m_currentTextureID, 4);

	glBindVertexArray(m_fireExt.VAO_ID);

	for (int i = 0; i < m_gameWorld->getFireExtPositions()->size(); ++i)
	{
		m_fireExtModelMatrix = glm::translate(glm::mat4(1.0f), m_gameWorld->getFireExtPositions()->at(i) / s_displayScale);
		m_fireExtModelMatrix = glm::scale(m_fireExtModelMatrix, glm::vec3(12.0f, 12.0f, 12.0f));
		glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &m_fireExtModelMatrix[0][0]);
		glDrawElements(GL_TRIANGLES, m_fireExt.indices.size(), GL_UNSIGNED_SHORT, (void*)0);
	}

	glBindVertexArray(0);

	// ---------------------------------------------------------------------------------------------------------------------

	// This section contains the rifle draw data
	if (gunNum == 2)
	{
		// Bind our texture in Texture Unit 5
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, m_rifle.texture);

		// Set shader to use Texture Unit 5
		glUniform1i(m_currentTextureID, 5);

		glBindVertexArray(m_rifle.VAO_ID);

		gunAnimation(m_rifleModelMatrix); // Does nothing if recoil is false
		reloadAnimation(m_rifleModelMatrix);

		glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &m_rifleModelMatrix[0][0]);
		glDrawElements(GL_TRIANGLES, m_rifle.indices.size(), GL_UNSIGNED_SHORT, (void*)0);
		glBindVertexArray(0);
	}

	// ---------------------------------------------------------------------------------------------------------------------

	// This section contains the pistol draw data
	if (gunNum == 1)
	{
		// Bind our texture in Texture Unit 6
		glActiveTexture(GL_TEXTURE6);
		glBindTexture(GL_TEXTURE_2D, m_pistol.texture);

		// Set shader to use Texture Unit 6
		glUniform1i(m_currentTextureID, 6);

		glBindVertexArray(m_pistol.VAO_ID);

		gunAnimation(m_pistolModelMatrix); // Does nothing if recoil is false
		reloadAnimation(m_pistolModelMatrix);

		glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &m_pistolModelMatrix[0][0]);
		glDrawElements(GL_TRIANGLES, m_pistol.indices.size(), GL_UNSIGNED_SHORT, (void*)0);
		glBindVertexArray(0);
	}

	// ---------------------------------------------------------------------------------------------------------------------

	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, m_enemy.texture);

	// Set shader to use Texture Unit 7
	glUniform1i(m_currentTextureID, 7);
	glBindVertexArray(m_enemy.VAO_ID);

	for (int i = 0; i < m_gameWorld->getActiveEnemyCount(); i++)
	{
		glm::vec3 enemyPos = glm::normalize(glm::vec3(m_gameWorld->getEnemyPosition(i).x, 0.0f, m_gameWorld->getEnemyPosition(i).y));
		glm::vec3 playerPos = glm::normalize(glm::vec3(m_gameWorld->getPlayerPosition().x, 0.0f, m_gameWorld->getPlayerPosition().y));

		float angle = getAngleBetweenVectors(enemyPos, playerPos);
		
		m_rotationMatrix = glm::rotate(originalEnemyRotationMatrix, angle, glm::vec3(0.0f, 1.0f, 0.0f));

		m_enemyModelMatrix = glm::translate(m_rotationMatrix, glm::vec3(m_gameWorld->getEnemyPosition(i).x / s_displayScale, 3, m_gameWorld->getEnemyPosition(i).y / s_displayScale));
		m_enemyModelMatrix = glm::scale(m_enemyModelMatrix, glm::vec3(m_gameWorld->getEnemySize(i), m_gameWorld->getEnemySize(i), m_gameWorld->getEnemySize(i)));

		glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &m_enemyModelMatrix[0][0]);
		glDrawElements(GL_TRIANGLES, m_enemy.indices.size(), GL_UNSIGNED_SHORT, (void*)0);
	}

	glBindVertexArray(0);

	// ---------------------------------------------------------------------------------------------------------------------

	glActiveTexture(GL_TEXTURE8);
	glBindTexture(GL_TEXTURE_2D, m_chair.texture);

	// Set shader to use Texture Unit 8
	glUniform1i(m_currentTextureID, 8);
	glBindVertexArray(m_chair.VAO_ID);

	for (int i = 0; i < m_gameWorld->getChairPositions()->size(); ++i)
	{
		m_chairModelMatrix = glm::translate(glm::mat4(1.0f), m_gameWorld->getChairPositions()->at(i) / s_displayScale);
		glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &m_chairModelMatrix[0][0]);
		glDrawElements(GL_TRIANGLES, m_chair.indices.size(), GL_UNSIGNED_SHORT, (void*)0);
	}
	   
	glBindVertexArray(0);

	//// ---------------------------------------------------------------------------------------------------------------------

	glActiveTexture(GL_TEXTURE9);
	glBindTexture(GL_TEXTURE_2D, m_table_1.texture);

	// Set shader to use Texture Unit 9
	glUniform1i(m_currentTextureID, 9);
	glBindVertexArray(m_table_1.VAO_ID);

	for (int i = 0; i < m_gameWorld->getTable1Positions()->size(); ++i)
	{
		m_table_1_modelMatrix = glm::translate(glm::mat4(1.0f), m_gameWorld->getTable1Positions()->at(i) / s_displayScale);
		glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &m_table_1_modelMatrix[0][0]);
		glDrawElements(GL_TRIANGLES, m_table_1.indices.size(), GL_UNSIGNED_SHORT, (void*)0);
	}

	glBindVertexArray(0);

	// ---------------------------------------------------------------------------------------------------------------------

	glActiveTexture(GL_TEXTURE10);
	glBindTexture(GL_TEXTURE_2D, m_table_2.texture);

	// Set shader to use Texture Unit 10
	glUniform1i(m_currentTextureID, 10);
	glBindVertexArray(m_table_2.VAO_ID);

	for (int i = 0; i < m_gameWorld->getTable2Positions()->size(); ++i)
	{
		m_table_2_modelMatrix = glm::translate(glm::mat4(1.0f), m_gameWorld->getTable2Positions()->at(i) / s_displayScale);
		m_table_2_modelMatrix = glm::scale(m_table_2_modelMatrix, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &m_table_2_modelMatrix[0][0]);
		glDrawElements(GL_TRIANGLES, m_table_2.indices.size(), GL_UNSIGNED_SHORT, (void*)0);
	}

	glBindVertexArray(0);

	// Ball spike
	glActiveTexture(GL_TEXTURE11);
	glBindTexture(GL_TEXTURE_2D, m_enemyBall.texture);

	// Set shader to use Texture Unit 11
	glUniform1i(m_currentTextureID, 11);
	glBindVertexArray(m_enemyBall.VAO_ID);

	for (int i = 0; i < 10; i++)
	{
		if (m_gameWorld->enemyBullet[i].active)
		{
			m_enemyBall_modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_gameWorld->enemyBullet[0].bullet.getPosition().x, 0.1f, m_gameWorld->enemyBullet[0].bullet.getPosition().y) * s_displayScale);
			m_enemyBall_modelMatrix = glm::scale(m_enemyBall_modelMatrix, glm::vec3(2.0f, 2.0f, 2.0f));
			glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &m_enemyBall_modelMatrix[0][0]);
			glDrawElements(GL_TRIANGLES, m_enemyBall.indices.size(), GL_UNSIGNED_SHORT, (void*)0);
		}
	}

	glBindVertexArray(0);

	// ---------------------------------------------------------------------------------------------------------------------

	// Bind our texture in Texture Unit 12
	//glActiveTexture(GL_TEXTURE12);
	//glBindTexture(GL_TEXTURE_2D, m_enemySkull.texture);

	//// Set shader to use Texture Unit 12
	//glUniform1i(m_currentTextureID, 12);
	//glBindVertexArray(m_enemySkull.VAO_ID);

	//glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &m_enemySkull_modelMatrix[0][0]);
	//glDrawElements(GL_TRIANGLES, m_enemySkull.indices.size(), GL_UNSIGNED_SHORT, (void*)0);
	//glBindVertexArray(0);

	// ---------------------------------------------------------------------------------------------------------------------

	// Bind our texture in Texture Unit 13
	//glActiveTexture(GL_TEXTURE13);
	//glBindTexture(GL_TEXTURE_2D, m_enemyEyeball.texture);

	//// Set shader to use Texture Unit 12
	//glUniform1i(m_currentTextureID, 13);
	//glBindVertexArray(m_enemyEyeball.VAO_ID);

	//glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &m_enemyEyeball_modelMatrix[0][0]);
	//glDrawElements(GL_TRIANGLES, m_enemyEyeball.indices.size(), GL_UNSIGNED_SHORT, (void*)0);
	//glBindVertexArray(0);

	// ---------------------------------------------------------------------------------------------------------------------

	// Particles! Particles! Particles!
	//glUseProgram(m_particleShader->m_programID);
	//m_particleEffect.generateParticles(m_eye);
	//m_particleEffect.drawParticles();

	// ---------------------------------------------------------------------------------------------------------------------

	// Reset OpenGL
	glBindVertexArray(GL_NONE);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);

	error = glGetError();

	if (error != GL_NO_ERROR)
	{
		DEBUG_MSG(error);
	}
}

/// <summary>
/// Gets the angle between two vectors
/// </summary>
double Game::getAngleBetweenVectors(glm::vec3 t_vector_1, glm::vec3 t_vector_2, double *reflexAngle)
{
	// Unitize the input vectors
	t_vector_1 = glm::normalize(t_vector_1);
	t_vector_2 = glm::normalize(t_vector_2);

	double dot = glm::dot(t_vector_1, t_vector_2);

	// Force the dot product of the two input vectors to
	// fall within the domain for inverse cosine, which
	// is -1 <= x <= 1. This will prevent runtime
	// "domain error" math exceptions.
	dot = (dot < -1.0 ? -1.0 : (dot > 1.0 ? 1.0 : dot));

	double angle = acos(dot);

	if (reflexAngle)
	{
		*reflexAngle = (glm::pi<double>() * 2) - angle;
	}	
	
	return angle;
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
void Game::loadVAO(std::string t_textureFilename, const char *t_modelFilename, Model &t_model)
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

	glGenTextures(1, &t_model.texture);
	glBindTexture(GL_TEXTURE_2D, t_model.texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, f_width, f_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, f_data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	stbi_image_free(f_data); // Unload data from CPU as it's on the GPU now

	// Load .obj file
	if (!tk::ModelLoader::loadOBJ(t_modelFilename, t_model.vertices, t_model.uvs, t_model.normals, t_model.indices))
	{
		std::cout << "Error loading model!" << std::endl;
	}

	// Initialise buffers for model
	glGenBuffers(1, &t_model.VBO_ID);
	glBindBuffer(GL_ARRAY_BUFFER, t_model.VBO_ID);
	glBufferData(GL_ARRAY_BUFFER, t_model.vertices.size() * sizeof(glm::vec3), &t_model.vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &t_model.uvBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, t_model.uvBufferID);
	glBufferData(GL_ARRAY_BUFFER, t_model.uvs.size() * sizeof(glm::vec2), &t_model.uvs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &t_model.normalBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, t_model.normalBufferID);
	glBufferData(GL_ARRAY_BUFFER, t_model.normals.size() * sizeof(glm::vec3), &t_model.normals[0], GL_STATIC_DRAW);

	// Element buffer object (used for indices)
	glGenBuffers(1, &t_model.elementBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, t_model.elementBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, t_model.indices.size() * sizeof(unsigned short), &t_model.indices[0], GL_STATIC_DRAW);

	// This VAO stores all states for model
	glGenVertexArrays(1, &t_model.VAO_ID);
	glBindVertexArray(t_model.VAO_ID);

	// Vertex buffer	
	glBindBuffer(GL_ARRAY_BUFFER, t_model.VBO_ID);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// UV buffer
	glBindBuffer(GL_ARRAY_BUFFER, t_model.uvBufferID);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Normal buffer
	glBindBuffer(GL_ARRAY_BUFFER, t_model.normalBufferID);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Element buffer (used for indices)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, t_model.elementBufferID);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 1, GL_UNSIGNED_SHORT, GL_FALSE, 0, (void*)0);

	glBindVertexArray(0);
}

/// <summary>
/// This function handles gun recoil
/// </summary>
void Game::gunAnimation(glm::mat4& t_gunMatrix)
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

/// <summary>
/// This function handles reloading the gun
/// </summary>
void Game::reloadAnimation(glm::mat4& t_gunMatrix)
{
	glm::vec3 gunDirection(camera.getDirection().x, 1.5f, camera.getDirection().z);
	currentAngle += reloadSpeed;
	if (down)
	{
		t_gunMatrix = glm::rotate(t_gunMatrix, glm::radians(camera.getYaw()), glm::vec3(0 + currentAngle, 1.0f, 0.0f));
		t_gunMatrix = glm::translate(glm::mat4(1.0f), camera.getEye());
	}
	else
	{
		t_gunMatrix = glm::translate(glm::mat4(1.0f), camera.getEye() + camera.getDirection());
	}

	t_gunMatrix = glm::rotate(t_gunMatrix, glm::radians(camera.getYaw()), glm::vec3(0.0f, 1.0f, 0.0f));
}

/// <summary>
/// This function handles gun fire
/// </summary>
void Game::fireGun()
{
	if (gunNum == 1) // Pistol
	{
		if (camera.controller.rightTriggerDown())
		{
			if (m_gameWorld->fireBullet(gunNum))
			{
				gunSoundEngine->play2D(pistolSound);

				m_time = sf::Time::Zero;
				m_time = m_time.Zero;

				if (camera.isCameraShaking() == false)
				{
					camera.setCameraShake(true);
				}

				vibrate = true;
				camera.controller.Vibrate(65535, 65535);
				m_vibrateLength = m_ShotDelay / (float)10;
				m_muzzleFlashIntensity = 300.0f;
				gunRecoil = true; // If the gun is being shot, create some recoil
			}
			else
			{
				m_time = sf::Time::Zero;
				m_time = m_time.Zero;
				gunSoundEngine->play2D(outOfAmmo);

				camera.controller.Vibrate(0, 0);
			}
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
			if (m_gameWorld->fireBullet(gunNum))
			{
				gunSoundEngine->play2D(shotgunQueue.front());
				m_time = sf::Time::Zero;
				m_time = m_time.Zero;

				if (camera.isCameraShaking() == false)
				{
					camera.setCameraShake(true);
				}

				vibrate = true;
				camera.controller.Vibrate(65535, 65535);
				m_vibrateLength = m_ShotDelay * .8f;
				m_muzzleFlashIntensity = 300.0f;
				gunRecoil = true; // If the gun is being shot, create some recoil
			}
			else
			{
				m_time = sf::Time::Zero;
				m_time = m_time.Zero;
				gunSoundEngine->play2D(outOfAmmo);

				camera.controller.Vibrate(0, 0);
			}
		}
		else
		{
			m_muzzleFlashIntensity = 0.0f;
		}
	}
	else if (gunNum == 3 && m_time > m_ShotDelay / (float)6) // Machine gun
	{
		if (camera.controller.rightTrigger())
		{
			if (m_gameWorld->fireBullet(gunNum))
			{
				gunSoundEngine->play2D(machinegunSound);
				m_time = sf::Time::Zero;
				m_time = m_time.Zero;

				if (camera.isCameraShaking() == false)
				{
					camera.setCameraShake(true);
				}

				vibrate = true;
				camera.controller.Vibrate(65535, 65535);
				m_vibrateLength = m_ShotDelay / (float)2;
				m_muzzleFlashIntensity = 300.0f;
				gunRecoil = true; // If the gun is being shot, create some recoil
			}
			else
			{
				m_time = sf::Time::Zero;
				m_time = m_time.Zero;
				gunSoundEngine->play2D(outOfAmmo);

				camera.controller.Vibrate(0, 0);
			}
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


