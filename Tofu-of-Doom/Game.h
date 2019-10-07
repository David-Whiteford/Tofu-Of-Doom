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

class Game
{
public:
	Game(sf::ContextSettings t_settings);
	~Game();
	void run();

private:
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
	GLuint vertexbuffer; // This will identify our vertex buffer
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
	glm::mat4 view;
	glm::mat4 model; // This matrix will eventually come from the model

	tk::Shader *m_genericShader; // Shader object
	tk::ModelLoader m_modelLoader;
	glm::vec3 m_eye{ 0.f, 5.0f, 0.f }; // Current camera position
	glm::mat4 m_rotationMatrix;
	glm::vec4 m_direction{ 0.f, 0.f, 1.f, 0.f }; // You move in this direction
	float speed = 0.01f;

	// These vectors are for loading in external OBJ files
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals; // Won't be used at the moment.

	double m_yaw{ 0.0 }; // In degrees
	double m_pitch{ 0.0 }; // For the love of Jebus, do NOT pitch more that 90 degress pos or neg! Thanks.

	void initialise();
	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();
	glm::mat4 camera(glm::vec3 t_eye, double t_pitch, double t_yaw);
	void gameControls(sf::Time t_deltaTime);
};

#endif // !GAME_H

