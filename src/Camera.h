#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class CameraDirection 
{
	NONE = -1,
	LEFT = 0,
	RIGHT = 1,
	FRONT = 2,
	BACK = 3,
};
const float SPEED = 2.0f;
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;
class Camera
{
private:
	// Directional Attributes
	glm::vec3 m_CameraPos;
	glm::vec3 m_CameraFront;
	glm::vec3 m_CameraUp;
	glm::vec3 m_CameraRight;
	glm::vec3 m_WorldUp;
	// Parameters
	float m_Speed;
	float m_Yaw;
	float m_Pitch;
	float m_MouseSensitivity;
	float m_Zoom;

	// Methods
	void updateCameraVectors();
public:
	Camera(glm::vec3 cameraPos = glm::vec3(0.0f), glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw = YAW, float pitch = PITCH);

	glm::mat4 GetViewMatrix() const;
	void ProcessKeyBoardInput(CameraDirection direction, float deltaTime);
	void ProcessMouseInput(float xoffset, float yoffset, bool constrainPitch);
	void ProcessMouseScroll(float yoffset);

	inline float GetZoom() const { return m_Zoom; }
};