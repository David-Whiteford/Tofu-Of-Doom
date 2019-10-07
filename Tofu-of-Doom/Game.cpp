#include "Game.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

/// <summary>
/// Constructor for the Game class
/// </summary>
Game::Game(sf::ContextSettings t_settings)
	:
	m_window{ sf::VideoMode{ 1920, 1080, 32 }, "Tofu of Doom", sf::Style::Default, t_settings }
{
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
	// Load texture
	filename = "cottage-texture.png";
	stbi_set_flip_vertically_on_load(false);
	texture_data = stbi_load(filename.c_str(), &width, &height, &comp_count, 3);

	glGenTextures(1, &Texture);
	glBindTexture(GL_TEXTURE_2D, Texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	bool res = m_modelLoader.loadOBJ("cottage.obj", vertices, uvs, normals);

	GLuint m_error = glewInit(); // Initialise GLEW

	// Load vertex and fragment shader files into shader objects
	m_genericShader = new tk::Shader("Standard.vert", "Standard.frag");

	GLint isCompiled = 0;
	GLint isLinked = 0;
	
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Initialise buffers (vertices, UV and normals)
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

	// Projection matrix 
	projection = glm::perspective(45.0f, 4.0f / 3.0f, 1.0f, 500.0f);

	// View (camera)
	view = camera(m_eye, 0, 0);

	// Model matrix (for now)
	model = glm::mat4(1.0f);

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
	// Update game controls
	gameControls(t_deltaTime);

	// Update view (camera)
	view = camera(m_eye, m_pitch, m_yaw);

	// Update model view projection
	mvp = projection * view * model;

	// Send our transformation to the currently bound shader, in the "MVP" uniform
	// This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &view[0][0]);

	glm::vec3 lightPos = glm::vec3(0, 3, 0);
	// glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z); // Static light position
	glUniform3f(LightID, m_eye.x, m_eye.y, m_eye.z);
}

/// <summary>
/// Render
/// </summary>
void Game::render()
{
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// This is where any SFML related stuff can be drawn
	m_window.pushGLStates();

	/////////////////////////////////////
	// SFML draw stuff can go in here! //
	/////////////////////////////////////

	m_window.popGLStates(); // End of SFML stuff

	// Use our shader
	glUseProgram(m_genericShader->m_programID);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);

	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(TextureID, 0);

	// Vertices buffer
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
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
		(void*)0                          // array buffer offset
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
		(void*)0                          // array buffer offset
	);

	// Draw
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	m_window.display();

	// Check for OpenGL error code
	error = glGetError();

	if (error != GL_NO_ERROR)
	{
		DEBUG_MSG(error);
	}
}

// TODO: Create a camera class
/// <summary>
/// Camera
/// </summary>
glm::mat4 Game::camera(glm::vec3 t_eye, double t_pitch, double t_yaw)
{
	double cosPitch = cos(glm::radians(t_pitch));
	double sinPitch = sin(glm::radians(t_pitch));
	double cosYaw = cos(glm::radians(t_yaw));
	double sinYaw = sin(glm::radians(t_yaw));

	glm::vec3 xaxis = { cosYaw, 0, -sinYaw };
	glm::vec3 yaxis = { sinYaw * sinPitch, cosPitch, cosYaw * sinPitch };
	glm::vec3 zaxis = { sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw };

	// Create a 4x4 view matrix from the right, up, forward and eye position vectors
	glm::mat4 viewMatrix =
	{
		glm::vec4(xaxis.x,            yaxis.x,            zaxis.x,      0),
		glm::vec4(xaxis.y,            yaxis.y,            zaxis.y,      0),
		glm::vec4(xaxis.z,            yaxis.z,            zaxis.z,      0),
		glm::vec4(-dot(xaxis, m_eye), -dot(yaxis, m_eye), -dot(zaxis, m_eye), 1)
	};

	return viewMatrix;
}

// Game controls
void Game::gameControls(sf::Time t_deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		glm::vec3 tempDirection(m_direction.x, m_direction.y, m_direction.z);
		glm::normalize(tempDirection);
		m_eye -= tempDirection * static_cast<float>(t_deltaTime.asMilliseconds() * speed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		glm::vec3 tempDirection(m_direction.x, m_direction.y, m_direction.z);
		glm::normalize(tempDirection);
		m_eye += tempDirection * static_cast<float>(t_deltaTime.asMilliseconds() * speed);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_eye.x -= .1f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_eye.x += .1f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
	{
		m_yaw += 2.0;
		m_rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(-2.0f), glm::vec3(0.f, 1.f, 0.f));
		m_direction = m_direction * m_rotationMatrix;
		
		if (m_yaw >= 360.0)
		{
			m_yaw = 0.0;
			m_direction = glm::vec4(0.f, 0.f, 1.f, 0.f);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
	{
		m_yaw -= 2.0;
		m_rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(2.0f), glm::vec3(0.f, 1.f, 0.f));
		m_direction = m_direction * m_rotationMatrix;

		if (m_yaw <= -360.0)
		{
			m_yaw = 0.0;
			m_direction = glm::vec4(0.f, 0.f, 1.f, 0.f);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_pitch += 1.0;

		if (m_pitch >= 360.0)
		{
			m_pitch = 0.0;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_pitch -= 1.0;

		if (m_pitch <= -360.0)
		{
			m_pitch = 0.0;
		}
	}
}
