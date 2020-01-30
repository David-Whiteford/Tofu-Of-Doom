#ifndef CAMERA_H
#define CAMERA_H

#include "Transform.h"
#include "libs/glew/glew.h"
#include "libs/glew/wglew.h"
#include "libs/glm/glm.hpp"
#include "libs/glm/gtc/matrix_transform.hpp"
#include <SFML/Graphics.hpp>
#include "Controller.h"
#include "Collider2D.h"
#include "Raycast.h"

class Camera
{
public:

	bool vibrate = false;
	float vibrationLength = 0.3f;
	float vibrationStarted = 0.0f;
	bool canClimb = false;
	Camera();
	~Camera();
	void input(sf::Time t_deltaTime);
	// Camera and controls
	Transform transform;

	glm::vec3 getEye();
	void setEye(glm::vec3 t_values);
	glm::mat4 getView();
	glm::vec3 getDirection();
	float getSpeed();
	glm::mat4 camera(glm::vec3 t_eye, double t_pitch, double t_yaw);
	float getYaw();

	void setCameraShake(bool t_bool);
	void cameraShake();
	bool isCameraShaking();

	void setCameraShakeSpeed(float t_speed);
	void setCameraShakeMax(float t_max);

	CXBOXController controller;

	Collider2D collider;

	Raycast raycastForward,raycastBehind,raycastToLeft,raycastToRight;

	void setCanMoveUp(bool t_bool);
	void setCanMoveDown(bool t_bool);
	void setCanMoveLeft(bool t_bool);
	void setCanMoveRight(bool t_bool);

	bool canGoUp();
	bool canGoDown();
	bool canGoLeft();
	bool canGoRight();

private:
	bool cameraShaking = false;
	bool cameraShakeUp = true;
	float cameraShakeSpeed = 2;
	float cameraShakeMax = 4;

	bool canMoveUp, canMoveDown, canMoveLeft, canMoveRight;



	glm::mat4 view;
	// glm::vec3 m_eye{ transform.position.x,transform.position.y,transform.position.z }; // Current camera position
	glm::vec3 m_eye;
	glm::mat4 m_rotationMatrix;
	glm::vec4 m_direction{ 0.f, 0.f, 1.f, 0.f }; // You move in this direction(z)
	glm::vec4 m_directionStrafe{ 1.0f, 0.f, 0.f, 0.f }; // You move in this direction(z)
	float m_speed = 0.04f;
	float m_turnSpeed = 3;

	double m_yaw{ 0.0 }; // In degrees
	double m_pitch{ 0.0 }; // This isn't really used anymore
};

#endif // !GAME_H