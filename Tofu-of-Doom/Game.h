#ifndef GAME_H
#define GAME_H

#include "libs/glew/glew.h"
#include "libs/glew/wglew.h"
#include "libs/glm/glm.hpp"
#include "libs/glm/gtc/matrix_transform.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <vector>
#include "Debug.h"
#include "Shader.h"
#include "ModelLoader.h"
#include "GameWorld.h"
#include "irrKlang.h"


#include "Camera.h"
#include "DisplayScale.h"

using namespace irrklang;
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

class Game
{
public:
	Game(sf::ContextSettings t_settings);
	~Game();
	void run();
	std::vector< vec3df > positions;
	ISoundEngine* soundEngine;
	ISound* music;
	ISound* background;
	ISound* zombie;

	bool vibrate = false;

	ISound* zombieEnemies[11];
	//vec3df positionEnemies[11];

	// 1 is pistol, 2 is rifle, 3 is machine gun)
	int gunNum = 1;

	ISound* pistol;
	ISound* shotgun;
	ISound* machinegun;

	sf::Time m_time;
	sf::Time m_ShotDelay;
	sf::Time m_vibrateLength;

private:


	enum DrawState
	{
		MAP,
		GAME
	};

	DrawState m_drawState = DrawState::GAME;

	sf::RenderWindow m_window; // Window
	sf::Time m_deltaTime;
	GameWorld *m_gameWorld = new GameWorld(m_window, m_deltaTime, camera); // Create a game world

	bool m_exitGame{ false };

	// Wall type 1
	unsigned char *wallType1_data;
	GLuint wallType1_VAO_ID;
	GLuint wallType1_VBO_ID;
	GLuint wallType1_normalBufferID;
	GLuint wallType1_textureID;
	GLuint wallType1_texture;
	GLuint wallType1_uvBufferID;
	std::vector<glm::vec3> wallType1_vertices;
	std::vector<glm::vec2> wallType1_uvs;
	std::vector<glm::vec3> wallType1_normals;

	// Wall type 2
	unsigned char *wallType2_data;
	GLuint wallType2_VAO_ID;
	GLuint wallType2_VBO_ID;
	GLuint wallType2_normalBufferID;
	GLuint wallType2_textureID;
	GLuint wallType2_texture;
	GLuint wallType2_uvBufferID;
	std::vector<glm::vec3> wallType2_vertices;
	std::vector<glm::vec2> wallType2_uvs;
	std::vector<glm::vec3> wallType2_normals;

	// Machine gun
	unsigned char *machineGun_data;
	GLuint machineGun_VAO_ID;
	GLuint machineGun_VBO_ID;
	GLuint machineGun_normalBufferID;
	GLuint machineGun_textureID;
	GLuint machineGun_texture;
	GLuint machineGun_uvBufferID;
	std::vector<glm::vec3> machineGun_vertices;
	std::vector<glm::vec2> machineGun_uvs;
	std::vector<glm::vec3> machineGun_normals;	

	// Oil drum
	unsigned char* oilDrum_data;
	GLuint oilDrum_VAO_ID;
	GLuint oilDrum_VBO_ID;
	GLuint oilDrum_normalBufferID;
	GLuint oilDrum_textureID;
	GLuint oilDrum_texture;
	GLuint oilDrum_uvBufferID;
	std::vector<glm::vec3> oilDrum_vertices;
	std::vector<glm::vec2> oilDrum_uvs;
	std::vector<glm::vec3> oilDrum_normals;

	// Fire extinguisher
	unsigned char* fireExtinguisher_data;
	GLuint fireExtinguisher_VAO_ID;
	GLuint fireExtinguisher_VBO_ID;
	GLuint fireExtinguisher_normalBufferID;
	GLuint fireExtinguisher_textureID;
	GLuint fireExtinguisher_texture;
	GLuint fireExtinguisher_uvBufferID;
	std::vector<glm::vec3> fireExtinguisher_vertices;
	std::vector<glm::vec2> fireExtinguisher_uvs;
	std::vector<glm::vec3> fireExtinguisher_normals;

	// Rifle
	unsigned char* rifle_data;
	GLuint rifle_VAO_ID;
	GLuint rifle_VBO_ID;
	GLuint rifle_normalBufferID;
	GLuint rifle_textureID;
	GLuint rifle_texture;
	GLuint rifle_uvBufferID;
	std::vector<glm::vec3> rifle_vertices;
	std::vector<glm::vec2> rifle_uvs;
	std::vector<glm::vec3> rifle_normals;

	// Pistol
	unsigned char* pistol_data;
	GLuint pistol_VAO_ID;
	GLuint pistol_VBO_ID;
	GLuint pistol_normalBufferID;
	GLuint pistol_textureID;
	GLuint pistol_texture;
	GLuint pistol_uvBufferID;
	std::vector<glm::vec3> pistol_vertices;
	std::vector<glm::vec2> pistol_uvs;
	std::vector<glm::vec3> pistol_normals;

	// Shader IDs
	GLuint m_lightID;
	GLuint m_modelMatrixID;
	GLuint m_viewMatrixID;
	GLuint m_projectionMatrixID;	
	GLuint m_currentTextureID;

	// Used for OpenGL error check
	GLenum error;

	// The model matrices will eventually be stored in an array (probably on the GPU)
	glm::mat4 model_1;
	glm::mat4 model_2;
	glm::mat4 model_3; // Machine gun matrix
	glm::mat4 model_4;
	glm::mat4 model_5;
	glm::mat4 model_6; // Rifle matrix
	glm::mat4 model_7; // Pistol matrix
	glm::mat4 projection;	

	tk::Shader *m_genericShader; // Shader object
	glm::vec3 m_eye{ 0.f, 4.0f, 0.f }; // Current camera position
	
	glm::mat4 m_rotationMatrix;
	glm::vec4 m_direction{ 0.f, 0.f, 1.f, 0.f }; // You move in this direction, it rotates when you rotate
	float m_speed = 0.05f; // This value dictates the speed of all game movement

	double m_yaw{ 0.0 }; // Look left and right (in degrees)
	double m_pitch{ 0.0 }; // Look up and down (in degrees)
	bool gunRecoil{ false };

	void initialise();
	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();
	void gameControls(sf::Time t_deltaTime);
	void loadVAO(std::string t_textureFilename, const char *t_modelFilename, GLuint &t_vaoID,
		GLuint &t_vboID, GLuint &t_normalBufferID, GLuint &t_textureID, GLuint &t_texture, GLuint &t_uvBufferID,
		std::vector<glm::vec3>& t_vertices, std::vector<glm::vec2>& t_UVs, std::vector<glm::vec3>& t_normals);
	void gunAnimation(glm::mat4 &t_gunMatrix);


	bool m_buttonPressed = false;
	//Player Camera
	Camera camera;
};

#endif // !GAME_H

