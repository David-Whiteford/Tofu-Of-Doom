#include "Room.h"
#include <string>
void Room::initialise()
{
	if (!textureValuesLoaded)
	{


		// Load texture
		filename = "cottage-texture.png";
		//	stbi_set_flip_vertically_on_load(false);
		texture_data = stbi_load(filename.c_str(), &width, &height, &comp_count, 3);
		textureValuesLoaded = true;
	}
	glGenTextures(1, &Texture);
	glBindTexture(GL_TEXTURE_2D, Texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	bool res = m_modelLoader.loadOBJ("plainCube.obj", vertices, uvs, normals);
	verticesInit = vertices;

	GLuint m_error = glewInit(); // Initialise GLEW

	// Load vertex and fragment shader files into shader objects
	m_genericShaderRoom = new tk::Shader("Standard.vert", "Standard.frag");

	GLint isCompiled = 0;
	GLint isLinked = 0;


	// Get a handle for our "myTextureSampler" uniform
	TextureID = glGetUniformLocation(m_genericShaderRoom->m_programID, "myTextureSampler");
	loaded += 1;
	std::cout << "Loaded " << std::to_string(loaded) << "%" << std::endl;
}

std::vector<glm::vec3> Room::getVertices()
{
	return vertices;
}

std::vector<glm::vec2> Room::getUvs()
{
	return uvs;
}

std::vector<glm::vec3> Room::getNormals()
{
	return normals;
}



GLuint Room::getVertexBuffer()
{
	return vertexbuffer;
}

void Room::setPosition()
{
	for (int i = 0; i < vertices.size(); i++)
	{
		vertices[i].x = verticesInit[i].x + transform.position.x;
		vertices[i].y = verticesInit[i].y + transform.position.y;
		vertices[i].z = verticesInit[i].z + transform.position.z;
	}
}

Room::Room()
{
}

Room::~Room()
{
}
