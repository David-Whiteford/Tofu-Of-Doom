// Shader class
//
// Constructor takes two arguments: 
// The filename of the vertex shader and the filename of the fragment shader.
// Example: Shader *m_shader = new Shader("Filename.vert", "Filename.frag");
//
// The shader's program ID is accessed by using the public member m_programID
// Example: GLuint shaderID = m_shader->m_programID;

#ifndef SHADER_H
#define SHADER_H

#include "libs/glew/glew.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

namespace tk
{
	class Shader
	{
	public:
		GLuint m_programID;

		Shader(const std::string &t_vertexShaderFilename, const std::string &t_fragmentShaderFilename);
		~Shader();

	private:
		std::string readFile(const std::string &t_filePath);
		GLuint compileShader(GLuint t_type, const std::string &t_source);
		void createShader(const std::string &t_vertexShader, const std::string &t_fragmentShader);
	};
}

#endif // !SHADER_H