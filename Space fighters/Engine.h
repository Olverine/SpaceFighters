#pragma once
#include <GL\glew.h>
#include <glfw3.h>
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <Actor.h>
#include <Camera.h> 
#include <Input.h>
#include <PlayerShip.h>
#include <map>
#include <string>
#include <Font.h>
using namespace glm;

GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
GLFWwindow* GetWindow();

void Spawn(Actor actor);
void Despawn(unsigned);
void ShrinkVector();

float Lerp(float, float, float);
float LerpAngle(float, float, float);
vec3 LerpVector(vec3, vec3, float);

float Distance(glm::vec2 p1, glm::vec2 p2);

Font* GetDefaultFont();