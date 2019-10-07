#include "Shader.h"

tk::Shader::Shader(const std::string &t_vertexShaderFilename, const std::string &t_fragmentShaderFilename)
{
	std::string f_vertexShader = readFile(t_vertexShaderFilename);
	std::string f_fragmentShader = readFile(t_fragmentShaderFilename);
	createShader(f_vertexShader, f_fragmentShader);
	glUseProgram(m_programID);
}

tk::Shader::~Shader()
{
	if (m_programID != 0)
	{
		glDeleteProgram(m_programID);
	}
}

std::string tk::Shader::readFile(const std::string &t_filePath)
{
	std::ifstream f_fileStream(t_filePath, std::ios::in);

	if (!f_fileStream.is_open())
	{
		std::cerr << "Could not read file " << t_filePath << ". File does not exist." << std::endl;
		return "";
	}

	std::stringstream f_buffer;
	std::string f_line;

	while (std::getline(f_fileStream, f_line))
	{
		f_buffer << f_line << "\n";
	}

	f_fileStream.close();
	return f_buffer.str();
}

GLuint tk::Shader::compileShader(GLuint t_type, const std::string &t_source)
{
	GLuint f_shader = glCreateShader(t_type);

	// Load shader program into shader object
	const char *src = t_source.c_str();
	glShaderSource(f_shader, 1, &src, nullptr);

	// Compile the shader program
	glCompileShader(f_shader);

	GLint f_result;

	// Get result of shader compilation
	glGetShaderiv(f_shader, GL_COMPILE_STATUS, &f_result);

	if (f_result == GL_FALSE)
	{
		int f_length;

		// Assigns length with length of information log
		glGetShaderiv(f_shader, GL_INFO_LOG_LENGTH, &f_length);

		// Allocate on stack frame of caller
		char *infoLog = (char*)_malloca(f_length * sizeof(char));

		// Returns the information log for a shader object
		glGetShaderInfoLog(f_shader, f_length, &f_length, infoLog);

		// Display error message in console window
		std::cout << "Shader compiling failed: " << (t_type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << std::endl;
		std::cout << infoLog << std::endl;

		// Delete shader (it's of no use anymore!)
		glDeleteShader(f_shader);

		return static_cast<GLuint>(0);
	}

	return f_shader;
}

void tk::Shader::createShader(const std::string &t_vertexShader, const std::string &t_fragmentShader)
{
	// Compile the two shaders given as string reference
	GLuint f_vs = compileShader(GL_VERTEX_SHADER, t_vertexShader);
	GLuint f_fs = compileShader(GL_FRAGMENT_SHADER, t_fragmentShader);

	if (f_vs == 0 || f_fs == 0)
	{
		return;
	}

	// Create a container to attach shader objects to
	m_programID = glCreateProgram();

	// Attach the shader objects to the program object
	glAttachShader(m_programID, f_vs);
	glAttachShader(m_programID, f_fs);

	// Links all the shader objects together
	glLinkProgram(m_programID);

	GLint f_result;

	// Checks if everything has been successfully linked
	glGetShaderiv(m_programID, GL_COMPILE_STATUS, &f_result);

	if (f_result == GL_FALSE)
	{
		int f_length;

		// Assigns length with length of information log
		glGetShaderiv(m_programID, GL_INFO_LOG_LENGTH, &f_length);

		// Allocate on stack frame of caller
		char *f_infoLog = (char*)alloca(f_length * sizeof(char));

		// Returns the information log for a shader object
		glGetShaderInfoLog(m_programID, f_length, &f_length, f_infoLog);

		// Display error message in console window
		std::cout << "Vertex and fragment shader link failed." << std::endl;
		std::cout << f_infoLog << std::endl;

		// Delete shader (it's of no use anymore!)
		glDeleteProgram(m_programID);
	
		return;
	}

	glValidateProgram(m_programID);

	// Deletes intermediate objects
	glDeleteShader(f_vs);
	glDeleteShader(f_fs);
}