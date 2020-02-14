#include "Camera.h"


glm::mat4 Camera::camera(glm::vec3 t_eye, double t_pitch, double t_yaw)
{
	double cosPitch = cos(glm::radians(t_pitch));
	double sinPitch = sin(glm::radians(t_pitch));
	double cosYaw = cos(glm::radians(t_yaw));
	double sinYaw = sin(glm::radians(t_yaw));

	glm::vec3 xaxis = { cosYaw, 0, -sinYaw };
	glm::vec3 yaxis = { sinYaw * sinPitch, cosPitch, cosYaw * sinPitch };
	glm::vec3 zaxis = { sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw };

	// Create a 4x4 view matrix from the right, up, forward and eye position vectors
	glm::mat4 viewMatrix =
	{
		glm::vec4(xaxis.x,            yaxis.x,            zaxis.x,      0),
		glm::vec4(xaxis.y,            yaxis.y,            zaxis.y,      0),
		glm::vec4(xaxis.z,            yaxis.z,            zaxis.z,      0),
		glm::vec4(-dot(xaxis, m_eye), -dot(yaxis, m_eye), -dot(zaxis, m_eye), 1)
	};

	return viewMatrix;
}

// This obviously returns the current yaw value
float Camera::getYaw()
{
	return float(m_yaw);
}

void Camera::setCameraShake(bool t_bool)
{
	cameraShaking = t_bool;
}

void Camera::cameraShake()
{
	if (cameraShaking)
	{
		if (cameraShakeUp)
		{
			m_pitch += cameraShakeSpeed;

			if (m_pitch >= cameraShakeMax)
			{
				cameraShakeUp = false;
			}
		}
		else
		{
			m_pitch -= cameraShakeSpeed;

			if (m_pitch <= 0)
			{
				m_pitch = 0;
				cameraShaking = false;
				cameraShakeUp = true;
			}
		}
	} // end camerashaking = true

}

bool Camera::isCameraShaking()
{
	return cameraShaking;
}

void Camera::setCameraShakeSpeed(float t_speed)
{
	cameraShakeSpeed = t_speed;
}

void Camera::setCameraShakeMax(float t_max)
{
	cameraShakeMax = t_max;
}

glm::vec3 Camera::getEye()
{
	return m_eye;
}

void Camera::setEye(glm::vec3 t_values)
{
	m_eye = t_values;
}

glm::mat4 Camera::getView()
{
	return camera(m_eye, m_pitch, m_yaw);
}

glm::vec3 Camera::getDirection()
{
	return glm::vec3(m_direction.x, m_direction.y, m_direction.z);
}

float Camera::getSpeed()
{
	return m_speed;
}

Camera::Camera()
{
	// Used to position player, temporary for now
	transform.position.x = 25.0f;
	transform.position.y = 3.5f;
	transform.position.z = 25.0f;

	collider.bounds.x1 = -50;
	collider.bounds.y1 = -50;
	collider.bounds.x2 = -50;
	collider.bounds.y2 = -50;
}

Camera::~Camera()
{
}

void Camera::input(sf::Time t_deltaTime)
{

	glm::vec3 transformPos = { transform.position.x, transform.position.y,transform.position.z };

	float temp_speed = m_speed;


	if ((controller.upButton() || controller.downButton()) && (controller.leftButton() || controller.rightButton()))
	{
		temp_speed = temp_speed / 2;
	}


	if (controller.upButton())
	{
		if (canGoUp())
		{
			glm::vec3 tempDirection(m_direction.x, m_direction.y, m_direction.z);
			glm::normalize(tempDirection);



			transformPos -= tempDirection * static_cast<float>(t_deltaTime.asMilliseconds())* temp_speed;
		}

	}
	else if (controller.downButton())
	{
		if (canGoDown())
		{
			glm::vec3 tempDirection(m_direction.x, m_direction.y, m_direction.z);
			glm::normalize(tempDirection);
			transformPos += tempDirection * static_cast<float>(t_deltaTime.asMilliseconds())* temp_speed;
		}
	}

	// Strafe
	if (controller.rightButton())
	{
		if (canGoRight())
		{
			glm::vec3 tempDirection(m_directionStrafe.x, m_directionStrafe.y, m_directionStrafe.z);
			glm::normalize(tempDirection);



			transformPos += tempDirection * static_cast<float>(t_deltaTime.asMilliseconds())* temp_speed;
		}

	}
	else if (controller.leftButton())
	{
		if (canGoLeft())
		{
			glm::vec3 tempDirection(m_directionStrafe.x, m_directionStrafe.y, m_directionStrafe.z);
			glm::normalize(tempDirection);
			transformPos -= tempDirection * static_cast<float>(t_deltaTime.asMilliseconds())* temp_speed;
		}
	}
	// End Strafe

	//


	// Turn Camera
	if (controller.leftButtonRTS())
	{
		turnToLeft(t_deltaTime);
	}
	else if (controller.rightButtonRTS())
	{
		turnToRight(t_deltaTime);

	}
	// End turn player


	

	


	m_eye = transformPos;
	transform.position.x = m_eye.x;
	transform.position.y = m_eye.y;
	transform.position.z = m_eye.z;

	// DEBUG FOR COLLIDER BOUNDS
	collider.bounds.x1 = m_eye.x - 0.1f;
	collider.bounds.x2 = m_eye.x + 0.1f;
	collider.bounds.y1 = m_eye.z - 0.1f;
	collider.bounds.y2 = m_eye.z + 0.1f;

	setUpRays();

}


void Camera::getOutOfWall(sf::Time t_deltaTime)
{
	float escapeAmount = 1.5f;
	glm::vec3 transformPos = { transform.position.x, transform.position.y,transform.position.z };
	// escape from being stuck
	if (!canGoUp() && !canGoRight())
	{
		if (controller.upButton())
			turnToLeft(t_deltaTime);
	}
	else if (!canGoLeft	())
	{

		if (controller.upButton())
			turnToRight(t_deltaTime);
		
	}
	else if (!canGoUp())
	{
		// do nothing
	}





}

void Camera::setCanMoveUp(bool t_bool)
{
	canMoveUp = t_bool;
}

void Camera::setCanMoveDown(bool t_bool)
{
	canMoveDown = t_bool;
}

void Camera::setCanMoveLeft(bool t_bool)
{
	canMoveLeft = t_bool;
}

void Camera::setCanMoveRight(bool t_bool)
{
	canMoveRight = t_bool;
}

bool Camera::canGoUp()
{
	return canMoveUp;
}

bool Camera::canGoDown()
{
	return canMoveDown;
}

bool Camera::canGoLeft()
{
	return canMoveLeft;
}

bool Camera::canGoRight()
{
	return canMoveRight;
}

void Camera::turnToRight(sf::Time t_deltaTime)
{
	m_yaw -= m_turnSpeed * static_cast<float>(t_deltaTime.asMilliseconds());
	m_rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(m_turnSpeed * static_cast<float>(t_deltaTime.asMilliseconds())), glm::vec3(0.f, 1.f, 0.f));
	m_direction = m_direction * m_rotationMatrix;
	m_directionStrafe = m_directionStrafe * m_rotationMatrix;

	if (m_yaw <= -360.0 || m_yaw >= 360.0)
	{
		m_yaw = 0.0;
		m_direction = glm::vec4(0.f, 0.f, 1.f, 0.f);
		m_directionStrafe = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
	}
}

void Camera::turnToLeft(sf::Time t_deltaTime)
{
	m_yaw += m_turnSpeed * static_cast<float>(t_deltaTime.asMilliseconds());
	m_rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(-m_turnSpeed * static_cast<float>(t_deltaTime.asMilliseconds())), glm::vec3(0.f, 1.f, 0.f));
	m_direction = m_direction * m_rotationMatrix;
	m_directionStrafe = m_directionStrafe * m_rotationMatrix;

	if (m_yaw <= -360.0 || m_yaw >= 360.0)
	{
		m_yaw = 0.0;
		m_direction = glm::vec4(0.f, 0.f, 1.f, 0.f);
		m_directionStrafe = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
	}


}

void Camera::setUpRays()
{

	/// Non Diagonal
	/////// offset front and back
	glm::vec3 tempDirectionF(m_direction.x, m_direction.y, m_direction.z);
	glm::normalize(tempDirectionF);
	glm::vec3 offsetPosF = tempDirectionF * -4.0f;
	glm::vec3 offsetPosB = tempDirectionF * 4.0f;


	sf::Vector2f posF = sf::Vector2f((offsetPosF.x + transform.position.x) * 10,
		(offsetPosF.z + transform.position.z) * 10);
	sf::Vector2f posB = sf::Vector2f((offsetPosB.x + transform.position.x) * 10,
		(offsetPosB.z + transform.position.z) * 10);

	//////// offset right and left
	glm::vec3 tempDirectionR(m_directionStrafe.x, m_directionStrafe.y, m_directionStrafe.z);
	glm::normalize(tempDirectionR);
	glm::vec3 offsetPosR = tempDirectionR * 4.0f;
	glm::vec3 offsetPosL = tempDirectionR * -4.0f;

	// set up positions with offset
	sf::Vector2f posR = sf::Vector2f((offsetPosR.x + transform.position.x) * 10,
		(offsetPosR.z + transform.position.z) * 10);
	sf::Vector2f posL = sf::Vector2f((offsetPosL.x + transform.position.x) * 10,
		(offsetPosL.z + transform.position.z) * 10);


	glm::vec3 tempDirection(m_directionStrafe.x, m_directionStrafe.y, m_directionStrafe.z);
	glm::normalize(tempDirection);
	raycastToLeft.setRayValues(posL, sf::Vector2f(tempDirection.x, tempDirection.z), raycastLength);
	raycastToRight.setRayValues(posR, sf::Vector2f(-tempDirection.x, -tempDirection.z), raycastLength);

	glm::vec3 tempDirection2(m_direction.x, m_direction.y, m_direction.z);
	glm::normalize(tempDirection2);
	raycastForward.setRayValues(posF, sf::Vector2f(tempDirection2.x, tempDirection2.z), raycastLength);
	raycastBehind.setRayValues(posB, sf::Vector2f(-tempDirection2.x, -tempDirection2.z), raycastLength);




	/// Diagonal
	/////// offset topleft topright and bottom left and bottom right
	glm::vec3 tempDirectionTopLeft(-m_directionStrafe.x + m_direction.x, m_direction.y, -m_direction.z + m_directionStrafe.z);
	glm::normalize(tempDirectionTopLeft);

	glm::vec3 tempDirectionBottomLeft(-m_directionStrafe.x + m_direction.x, m_direction.y, m_direction.z + m_directionStrafe.z);
	glm::normalize(tempDirectionBottomLeft);

	glm::vec3 tempDirectionTopRight((m_directionStrafe.x + m_direction.x), m_direction.y, -(m_direction.z + m_directionStrafe.z));
	glm::normalize(tempDirectionTopRight);

	glm::vec3 tempDirectionBottomRight(m_directionStrafe.x + m_direction.x, m_direction.y, m_direction.z + m_directionStrafe.z);
	glm::normalize(tempDirectionBottomRight);



	glm::vec3 offsetPosTL = tempDirectionTopLeft * 4.0f;
	glm::vec3 offsetPosBL = tempDirectionBottomLeft * 4.0f;
	glm::vec3 offsetPosTR = tempDirectionTopRight * 4.0f;
	glm::vec3 offsetPosBR = tempDirectionBottomRight * 4.0f;


	sf::Vector2f posTL = sf::Vector2f((offsetPosTL.x + transform.position.x) * 10,
		(offsetPosTL.z + transform.position.z) * 10);

	sf::Vector2f posBL = sf::Vector2f((offsetPosBL.x + transform.position.x) * 10,
		(offsetPosBL.z + transform.position.z) * 10);

	sf::Vector2f posTR = sf::Vector2f((offsetPosTR.x + transform.position.x) * 10,
		(offsetPosTR.z + transform.position.z) * 10);

	sf::Vector2f posBR = sf::Vector2f((offsetPosBR.x + transform.position.x) * 10,
		(offsetPosBR.z + transform.position.z) * 10);




	raycastTopLeft.setRayValues(posTL, sf::Vector2f(tempDirectionTopLeft.x, -tempDirectionTopLeft.z), raycastLength);
	raycastTopRight.setRayValues(posTR, sf::Vector2f(tempDirectionTopRight.x, tempDirectionTopRight.z), raycastLength);

	raycastBottomLeft.setRayValues(posBL, sf::Vector2f(tempDirectionBottomLeft.x, tempDirectionBottomLeft.z), raycastLength);
	raycastBottomRight.setRayValues(posBR, sf::Vector2f(tempDirectionBottomRight.x, tempDirectionBottomRight.z), raycastLength);

}
