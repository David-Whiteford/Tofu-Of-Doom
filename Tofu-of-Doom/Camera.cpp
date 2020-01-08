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
	transform.position.x = 225.0f;
	transform.position.y = 0.0f;
	transform.position.z = 225.0f;

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





	if (controller.upButton())
	{
		glm::vec3 tempDirection(m_direction.x, m_direction.y, m_direction.z);
		glm::normalize(tempDirection);



		transformPos -= tempDirection * static_cast<float>(t_deltaTime.asMilliseconds() * m_speed);

	}
	else if (controller.downButton())
	{
		glm::vec3 tempDirection(m_direction.x, m_direction.y, m_direction.z);
		glm::normalize(tempDirection);
		transformPos += tempDirection * static_cast<float>(t_deltaTime.asMilliseconds() * m_speed);
	}

	// Strafe
	if (controller.rightButton())
	{
		glm::vec3 tempDirection(m_directionStrafe.x, m_directionStrafe.y, m_directionStrafe.z);
		glm::normalize(tempDirection);



		transformPos += tempDirection * static_cast<float>(t_deltaTime.asMilliseconds() * m_speed);

	}
	else if (controller.leftButton())
	{
		glm::vec3 tempDirection(m_directionStrafe.x, m_directionStrafe.y, m_directionStrafe.z);
		glm::normalize(tempDirection);
		transformPos -= tempDirection * static_cast<float>(t_deltaTime.asMilliseconds() * m_speed);
	}
	// End Strafe


	// Turn Camera
	if (controller.leftButtonRTS())
	{
		m_yaw += m_turnSpeed;
		m_rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(-m_turnSpeed), glm::vec3(0.f, 1.f, 0.f));
		m_direction = m_direction * m_rotationMatrix;
		m_directionStrafe = m_directionStrafe * m_rotationMatrix;

		if (m_yaw >= 360.0)
		{
			m_yaw = 0.0;
			m_direction = glm::vec4(0.f, 0.f, 1.f, 0.f);
			m_directionStrafe = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
		}
	}
	else if (controller.rightButtonRTS())
	{
		m_yaw -= m_turnSpeed;
		m_rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(m_turnSpeed), glm::vec3(0.f, 1.f, 0.f));
		m_direction = m_direction * m_rotationMatrix;
		m_directionStrafe = m_directionStrafe * m_rotationMatrix;


	}
	// End turn player


		if (m_yaw <= -360.0 || m_yaw >= 360.0)
		{
			m_yaw = 0.0;
			m_direction = glm::vec4(0.f, 0.f, 1.f, 0.f);
			m_directionStrafe = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
		}

	


	m_eye = transformPos;
	transform.position.x = m_eye.x;
	transform.position.y = m_eye.y;
	transform.position.z = m_eye.z;

	// DEBUG FOR COLLIDER BOUNDS
	collider.bounds.x1 = m_eye.x - 0.1f;
	collider.bounds.x2 = m_eye.x + 0.1f;
	collider.bounds.y1 = m_eye.z - 0.1f;
	collider.bounds.y2 = m_eye.z + 0.1f;

}
