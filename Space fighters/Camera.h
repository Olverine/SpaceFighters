#pragma once
#include <Engine.h>
class Camera
{
public:
	float fov = 60;
	float aspectRatio = 16.0f / 9.0f; 
	float nearClip = 0.1f;
	float farClip = 600.0f;

	glm::vec3 position;
	glm::vec3 lookAt;
	Camera();
	Camera(glm::vec3 position);
	virtual void Update();

	glm::mat4 GetProjection();
	glm::mat4 GetView();
};

Camera* GetCamera();