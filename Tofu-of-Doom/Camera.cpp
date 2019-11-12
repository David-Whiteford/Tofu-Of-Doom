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
}

Camera::~Camera()
{
}

void Camera::input(sf::Time t_deltaTime)
{
	// Declae a temp Transform

	glm::vec3 transformPos = { transform.position.x, transform.position.y,transform.position.z };

	/*if (vibrationStarted + vibrationLength < t_deltaTime)
	{
		vibrate = false;
		Player1->Vibrate();
	////*/

	Player1 = new CXBOXController(1);
	if (Player1->IsConnected())
	{
		if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			//	Player1->Vibrate(65535, 0);
		}

		if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_B)
		{
			//Player1->Vibrate(0, 65535);
		}

		if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_X)
		{
			//if (!vibrate)
			//{
			//	vibrate = true;
			//	Player1->Vibrate(65535, 65535);
			//	//vibrationStarted = t_deltaTime.asMilliseconds();
			//	//std::cout << vibrationStarted << std::endl;
			//}

		}

		if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_Y)
		{
			//	Player1->Vibrate();
		}

		if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
		{
		}

		if (Player1->GetState().Gamepad.sThumbLY > 7849)
		{
			glm::vec3 tempDirection(m_direction.x, m_direction.y, m_direction.z);
			glm::normalize(tempDirection);



			transformPos -= tempDirection * static_cast<float>(t_deltaTime.asMilliseconds() * m_speed);

		}
		else if (Player1->GetState().Gamepad.sThumbLY < -7849)
		{
			glm::vec3 tempDirection(m_direction.x, m_direction.y, m_direction.z);
			glm::normalize(tempDirection);
			transformPos += tempDirection * static_cast<float>(t_deltaTime.asMilliseconds() * m_speed);
		}	
		
		// Strafe
		if (Player1->GetState().Gamepad.sThumbLX > 17849)
		{
			glm::vec3 tempDirection(m_directionStrafe.x, m_directionStrafe.y, m_directionStrafe.z);
			glm::normalize(tempDirection);



			transformPos += tempDirection * static_cast<float>(t_deltaTime.asMilliseconds() * m_speed);

		}
		else if (Player1->GetState().Gamepad.sThumbLX < -17849)
		{
			glm::vec3 tempDirection(m_directionStrafe.x, m_directionStrafe.y, m_directionStrafe.z);
			glm::normalize(tempDirection);
			transformPos -= tempDirection * static_cast<float>(t_deltaTime.asMilliseconds() * m_speed);
		}
		// End Strafe



		if (Player1->GetState().Gamepad.sThumbRX < -7849)
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
		else if (Player1->GetState().Gamepad.sThumbRX > 7849)
		{
			m_yaw -= m_turnSpeed;
			m_rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(m_turnSpeed), glm::vec3(0.f, 1.f, 0.f));
			m_direction = m_direction * m_rotationMatrix;
			m_directionStrafe = m_directionStrafe * m_rotationMatrix;

			if (m_yaw <= -360.0)
			{
				m_yaw = 0.0;
				m_direction = glm::vec4(0.f, 0.f, 1.f, 0.f);
				m_directionStrafe = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
			}
		}
		if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_Y)
		{
			if (canClimb)
			{
				glm::vec3 tempDirection(0, 1, 0);
				glm::normalize(tempDirection);
				transformPos += tempDirection * static_cast<float>(t_deltaTime.asMilliseconds() * m_speed);
			}

		}
		else if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			if (canClimb)
			{
				glm::vec3 tempDirection(0, 1, 0);
				glm::normalize(tempDirection);
				transformPos -= tempDirection * static_cast<float>(t_deltaTime.asMilliseconds() * m_speed);
			}

		}

		m_eye = transformPos;
		transform.position.x = m_eye.x;
		transform.position.y = m_eye.y;
		transform.position.z = m_eye.z;
		delete(Player1);
	}
}
