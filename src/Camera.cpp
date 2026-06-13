#include "Camera.h"
#include <iostream>

Camera::Camera(glm::vec3 cameraPos, glm::vec3 worldUp, float yaw, float pitch)
	: m_CameraPos(cameraPos), m_CameraFront(glm::vec3(0.0f,0.0f,-1.0f)), m_WorldUp(worldUp), m_Speed(SPEED), m_Yaw(yaw), m_Pitch(pitch),
	  m_MouseSensitivity(SENSITIVITY), m_Zoom(ZOOM)
{
	updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
: m_Speed(SPEED), m_Yaw(yaw), m_Pitch(pitch), m_MouseSensitivity(SENSITIVITY), m_Zoom(ZOOM) 
{
	m_CameraPos = glm::vec3(posX, posY, posZ);
	m_WorldUp = glm::vec3(upX, upY, upZ);
	updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAt(m_CameraPos,m_CameraPos + m_CameraFront,m_CameraUp);
}

void Camera::updateCameraVectors()
{
	// calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	front.y = sin(glm::radians(m_Pitch));
	front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_CameraFront = glm::normalize(front);
	// also re-calculate the Right and Up vector
	m_CameraRight = glm::normalize(glm::cross(m_CameraFront, m_WorldUp));  // normalize the vectors
	m_CameraUp = glm::normalize(glm::cross(m_CameraRight, m_CameraFront));
}

void Camera::ProcessKeyBoardInput(CameraDirection direction, float deltaTime)
{
	float velocity = m_Speed * deltaTime;
	switch (direction) 
	{
	case CameraDirection::LEFT:
		m_CameraPos -= velocity * m_CameraRight;
		break;
	case CameraDirection::RIGHT:
		m_CameraPos += velocity * m_CameraRight;
		break;
	case CameraDirection::FRONT:
		m_CameraPos += velocity * m_CameraFront;
		break;
	case CameraDirection::BACK:
		m_CameraPos -= velocity * m_CameraFront;
		break;
	default:
		break;
	}
}

void Camera::ProcessMouseInput(float xoffset, float yoffset, bool constrainPitch)
{
	xoffset *= m_MouseSensitivity;
	yoffset *= m_MouseSensitivity;

	m_Yaw += xoffset;
	m_Pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (m_Pitch > 89.0f)
			m_Pitch = 89.0f;
		if (m_Pitch < -89.0f)
			m_Pitch = -89.0f;
	}

	// update Front, Right and Up Vectors using the updated Euler angles
	updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
	m_Zoom -= yoffset;
	if (m_Zoom < 1.0f)
		m_Zoom = 1.0f;
	if (m_Zoom > 45.0f)
		m_Zoom = 45.0f;
}
