#ifndef GAME_H
#define GAME_H

#include "libs/glew/glew.h"
#include "libs/glew/wglew.h"
#include "libs/glm/glm.hpp"
#include "libs/glm/gtc/matrix_transform.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "Debug.h"
#include "Shader.h"
#include "ModelLoader.h"

#include "Room.h"
#include "Camera.h"


class Game
{
public:
	Game(sf::ContextSettings t_settings);
	~Game();
	void run();
	
private:
	static const int ROOM_NUMBERS = 200;
	sf::RenderWindow m_window;
	bool m_exitGame{ false };

	// Texture stuff
	std::string filename;
	int width; //width of texture
	int height; //height of texture
	int comp_count; //Component of texture
	const int number = 4; //4 = RGBA
	unsigned char *texture_data;
	GLuint TextureID;
	GLuint Texture;
	GLuint uvbuffer;

	// OpenGL stuff
	GLuint VertexArrayID;
	GLuint vertexbuffer[ROOM_NUMBERS]; // This will identify our vertex buffer
	GLuint MatrixID;
	GLuint normalbuffer;
	GLuint LightID;
	GLuint ViewMatrixID;
	GLuint ModelMatrixID;

	GLint positionID; // Vertex position ID (for shader)
	GLint colorID; // Vertex color ID (for shader)
	GLint mvpID; // Model, view and projection ID (for shader)
	GLint m_offsetID; // Game object offset ID (for shader)
	GLenum error; // OpenGL error check

	// Matrices for model, view and projection (and everything combined)
	glm::mat4 mvp;
	glm::mat4 projection;
	
	glm::mat4 model; // This matrix will eventually come from the model

	tk::Shader *m_genericShader; // Shader object
	tk::ModelLoader m_modelLoader;

	void initialise();
	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();
	void DrawRooms();


	// Rooms
	Room anotherRoom[ROOM_NUMBERS];

	// Camera
	Camera camera;
	
};

#endif // !GAME_H

