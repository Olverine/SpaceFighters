#include "Camera.h"

Camera::Camera() {

}

Camera::Camera(vec3 position) {
	this->position = position;
}

glm::mat4 Camera::GetProjection() {
	return glm::perspective(glm::radians(fov), 16.0f/9.0f, nearClip, farClip);
}

glm::mat4 Camera::GetView() {
	return glm::lookAt(position, lookAt, glm::vec3(0, 1, 0));
} 

void Camera::Update(){}