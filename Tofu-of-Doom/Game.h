#ifndef GAME_H
#define GAME_H

#include "libs/glew/glew.h"
#include "libs/glew/wglew.h"
#include "libs/glm/glm.hpp"
#include "libs/glm/gtc/matrix_transform.hpp"
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include "Enum.h"
#include "sfml.h"
#include "Debug.h"
#include "Shader.h"
#include "ModelLoader.h"
#include "GameWorld.h"
#include "irrKlang.h"
#include "ParticleEffect.h"
#include "SplashScreen.h"
#include "GameOver.h"
#include "SFML.h"
#include "MainMenu.h"
#include <iostream>
#include <fstream>
#include <string>
#include "aStarStuff/Graph.h"
#include "aStarStuff/NodeData.h"
#include <map>
#include "Options.h"
#include "Camera.h"
#include "DisplayScale.h"
#include "Collider2D.h"

using namespace irrklang;
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

class SplashScreen;
class SFML;
class MainMenu;
class Options;
class GameOver;

typedef GraphNode<NodeData, int> Node;

class Game
{
public:	
	Game(sf::ContextSettings t_settings);
	~Game();

	void run();
	std::vector< vec3df > positions;
	ISoundEngine* bgSoundEngine;
	ISoundEngine* soundEngine;
	ISoundEngine* gunSoundEngine;
	ISound* music;
	ISound* background;
	sf::Font m_font; // Font used by message
	sf::Font m_bloodFont; // Font used by message

	sf::Sprite m_backgroundLooseSprite;
	sf::Sprite m_backgroundWinSprite;
	sf::Texture m_backgroundLooseTexture; //bgtexture
	sf::Texture m_backgroundWinTexture; //bgtexture

	irrklang::ISoundSource* zombie;
	irrklang::ISoundSource* shotgunSound;
	irrklang::ISoundSource* machinegunSound;
	irrklang::ISoundSource* pistolSound;
	irrklang::ISoundSource* outOfAmmo;
	irrklang::ISoundSource* weaponLoad;
	irrklang::ISoundSource* ricochetOne;
	irrklang::ISoundSource* ricochetTwo;
	irrklang::ISoundSource* ricochetThree;
	irrklang::ISoundSource* ricochetFour;
	irrklang::ISoundSource* ricochetFive;

	std::vector<irrklang::ISoundSource*> ricochet;
	bool vibrate = false;
	vec3df zombiePosition;
	ISound* zombieEnemies[11];
	sf::Sprite m_sfmlSprite;
	sf::Texture m_sfmlTexture;
	int gunNum = 1;
	void resetScreenTrans();
	// Menu screens
	SplashScreen* m_splashScreen; // The splash screen
	SFML* m_sfmlScreen;
	MainMenu* m_mainMenu;
	Options* m_optionsMenu;
	GameOver* m_gameOver;
	void initialise();

	// A* stuff with graph for storing nodes
	GameState m_currentGameState{ GameState::Main }; // used for whatever mode game starts

	bool sound = false;

	bool yButtonPressed{ false }; // This is used so that a gun is only changed when Y is released
	bool backButtonPressed{ false }; // This is used so that the map is only displayed when the Back button is released

	ISound* pistol;
	ISound* shotgun;
	ISound* machinegun;


	sf::Time m_time;
	sf::Time m_ShotDelay;
	sf::Time m_vibrateLength;

	std::queue <ISoundSource*> shotgunQueue;

	enum class DrawState
	{
		MAP,
		GAME,
		MAIN,
		OPTIONS,
		SPLASH,
		EXIT,
		GAMEOVER
	};

	DrawState m_drawState = DrawState::SPLASH;

private:
	struct Model
	{
		unsigned char* data;
		GLuint VAO_ID;
		GLuint VBO_ID;
		GLuint normalBufferID;
		GLuint textureID;
		GLuint texture;
		GLuint uvBufferID;
		GLuint elementBufferID;
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> uvs;
		std::vector<glm::vec3> normals;
		std::vector<unsigned short> indices;
	};

	// Models
	Model m_wallType1;
	Model m_wallType2;
	Model m_fireExt;
	Model m_oilDrum;
	Model m_chair;
	Model m_table_1;
	Model m_table_2;
	Model m_table_and_chair;
	Model m_pistol;
	Model m_machineGun;
	Model m_rifle;
	Model m_enemy;
	Model m_enemyBall;
	Model m_enemySkull;
	Model m_enemyEyeball;

	sf::RenderWindow m_window;		
	Camera camera; // Player camera
	sf::Time m_deltaTime;
	GameWorld* m_gameWorld = new GameWorld(m_window, m_deltaTime, &camera); // Create a game world

	bool m_exitGame{ false };
	bool m_buttonPressed = false;

	// Shader IDs
	const static int LIGHT_AMOUNT = 25;
	GLuint m_lightID;
	GLuint m_lightPositionsID;
	GLuint m_muzzleFlashIntensityID;
	float m_muzzleFlashIntensity{ 0.0f };
	std::vector<glm::vec3> m_lightPositions;
	GLuint m_modelMatrixID;
	GLuint m_viewMatrixID;
	GLuint m_projectionMatrixID;	
	GLuint m_currentTextureID;

	// Used for OpenGL error check
	GLenum error;

	// Matrices for various models
	glm::mat4 model_1;
	glm::mat4 m_fireExtModelMatrix;
	glm::mat4 m_oilDrumModelMatrix;
	glm::mat4 m_chairModelMatrix;
	glm::mat4 m_table_1_modelMatrix;
	glm::mat4 m_table_2_modelMatrix;
	glm::mat4 m_pistolModelMatrix;
	glm::mat4 m_rifleModelMatrix;
	glm::mat4 m_machineGunModelMatrix;
	glm::mat4 m_enemyModelMatrix;
	glm::mat4 m_rotationMatrix; // Generic, used for anything
	glm::mat4 m_enemyBall_modelMatrix;
	glm::mat4 m_enemySkull_modelMatrix;
	glm::mat4 m_enemyEyeball_modelMatrix;

	// Projection matrix
	glm::mat4 projection;	

	// Shaders
	tk::Shader *m_mainShader;
	tk::Shader *m_particleShader;

	glm::vec3 m_eye{ 0.f, 4.0f, 0.f }; // Current camera position		
	glm::vec4 m_direction{ 0.f, 0.f, 1.f, 0.f }; // You move in this direction, it rotates when you rotate
	float m_speed = 0.05f; // This value dictates the speed of all game movement
	double m_yaw{ 0.0 }; // Look left and right (in degrees)
	double m_pitch{ 0.0 }; // Look up and down (in degrees)
	bool gunRecoil{ false };

	bool gunReloading = false;
	bool down = true;
	float reloadSpeed = 0.0014f;
	float currentAngle = 0;
	void reload();
	void reloadAnimation(glm::mat4& t_gunMatrix);

	// Create particle object
	ParticleEffect m_particleEffect = ParticleEffect(m_deltaTime);

	// Functions
	void processEvents();
	void update(sf::Time t_deltaTime);
	void updateWorld(sf::Time t_deltaTime);
	void render();
	void gameControls(sf::Time t_deltaTime);
	void loadVAO(std::string t_textureFilename, const char* t_modelFilename, Model& t_model);
	void gunAnimation(glm::mat4& t_gunMatrix);
	void fireGun();
	void drawGameScene();
};

#endif // !GAME_H

