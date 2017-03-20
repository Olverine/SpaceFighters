#include <stdio.h>
#include <glm\glm.hpp>

float Lerp(float v1, float v2, float t) {
	return (1 - t) * v1 + t * v2;
}

float LerpAngle(float a1, float a2, float t) {
	float x = Lerp(glm::sin(a1), glm::sin(a2), t);
	float y = Lerp(glm::cos(a1), glm::cos(a2), t);
	return atan2(x, y);
}

glm::vec3 LerpVector(glm::vec3 v1, glm::vec3 v2, float t) {
	float x = Lerp(v1.x, v2.x, t);
	float y = Lerp(v1.y, v2.y, t);
	float z = Lerp(v1.z, v2.z, t);
	return(glm::vec3(x, y, z));
}

float Distance(glm::vec2 p1, glm::vec2 p2) {
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}