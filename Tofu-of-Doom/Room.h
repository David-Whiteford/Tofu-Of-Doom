#pragma once

#include "libs/glew/glew.h"
#include "libs/glew/wglew.h"
#include "libs/glm/glm.hpp"
#include "libs/glm/gtc/matrix_transform.hpp"
#include "Shader.h"
#include "ModelLoader.h"
#include "stb_image.h"


#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "Transform.h"

	static int loaded = 0;
	// Texture stuff
	static std::string filename;
	static int width; //width of texture
	static int height; //height of texture
	static int comp_count; //Component of texture
	static const int number = 4; //4 = RGBA
	static unsigned char* texture_data;
	static GLuint TextureID;
	static GLuint Texture;
	static GLuint uvbuffer;
	static bool textureValuesLoaded = false;

class Room
{
public:
	float x = 1000;
	Room();
	~Room();
	void initialise();
	std::vector<glm::vec3> getVertices();
	std::vector<glm::vec2> getUvs();
	std::vector<glm::vec3> getNormals();

	// Every Object has a transform
	Transform transform;
	
	GLuint getVertexBuffer();
	void setPosition();
	float getPositionX();
	float getPositionY();
	float getPositionZ();


	bool made = false;
private:



	// OpenGL stuff
	GLuint VertexArrayID;
	GLuint vertexbuffer; // This will identify our vertex buffer
	GLuint MatrixID;
	GLuint normalbuffer;
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

	tk::Shader* m_genericShaderRoom; // Shader object
	tk::ModelLoader m_modelLoader;
	glm::vec3 m_eye{ 0.f, 5.0f, 0.f }; // Current camera position
	glm::mat4 m_rotationMatrix;
	glm::vec4 m_direction{ 0.f, 0.f, 1.f, 0.f }; // You move in this direction
	float speed = 0.01f;

	// These vectors are for loading in external OBJ files
	//std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals; // Won't be used at the moment.
	std::vector<glm::vec3> vertices;
	// These vectors are for loading in external OBJ files
	std::vector<glm::vec3> verticesInit;

};
