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