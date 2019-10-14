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

glm::vec4 Camera::getDirection()
{
	return m_direction;
}

float Camera::getSpeed()
{
	return m_speed;
}

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::input(sf::Time t_deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		glm::vec3 tempDirection(m_direction.x, m_direction.y, m_direction.z);
		glm::normalize(tempDirection);
		m_eye -= tempDirection * static_cast<float>(t_deltaTime.asMilliseconds() * m_speed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		glm::vec3 tempDirection(m_direction.x, m_direction.y, m_direction.z);
		glm::normalize(tempDirection);
		m_eye += tempDirection * static_cast<float>(t_deltaTime.asMilliseconds() * m_speed);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_eye.x -= .1f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_eye.x += .1f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
	{
		m_yaw += 2.0;
		m_rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(-2.0f), glm::vec3(0.f, 1.f, 0.f));
		m_direction = m_direction * m_rotationMatrix;

		if (m_yaw >= 360.0)
		{
			m_yaw = 0.0;
			m_direction = glm::vec4(0.f, 0.f, 1.f, 0.f);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
	{
		m_yaw -= 2.0;
		m_rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(2.0f), glm::vec3(0.f, 1.f, 0.f));
		m_direction = m_direction * m_rotationMatrix;

		if (m_yaw <= -360.0)
		{
			m_yaw = 0.0;
			m_direction = glm::vec4(0.f, 0.f, 1.f, 0.f);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_pitch += 1.0;

		if (m_pitch >= 360.0)
		{
			m_pitch = 0.0;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_pitch -= 1.0;

		if (m_pitch <= -360.0)
		{
			m_pitch = 0.0;
		}
	}
}
