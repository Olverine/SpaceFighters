#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <Engine.h>
#include <vector>
#include <BackgroundParticles.h>
#include <Bounds.h>
#include <MultiChaseCam.h>

void MainLoop();
GLFWwindow* window;
bool fullscreen = false;

std::list<Actor*> activeActors;

std::list<Actor*> spawnQueue;
std::list<Actor*> despawnQueue;
Camera* camera;
GLuint shaderMvp;

int main()
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(1366, 768, "Game", fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		system("pause");
		return -1;
	}
	glfwMakeContextCurrent(window); // Initialize GLEW
	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		system("pause");
		return -1;
	}

	// Vsync
	//glfwSwapInterval(1);

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	Input::Init();

	vec3 colors[] = {
		vec3(0, 0.5f, 1),
		vec3(1, 0, 0),
		vec3(0, 1, 0),
		vec3(1, 0, 1)
	};

	GLuint shaderProgram = LoadShaders("shaders/basicVertex.glsl", "shaders/basicFragment.glsl");

	camera = new MultiChaseCam();
	for (int i = 0; i < 4; i++) {
		if (glfwJoystickPresent(i)) {
			activeActors.push_back(new PlayerShip(i, shaderProgram, colors[i]));
			dynamic_cast<MultiChaseCam*>(camera)->targets.push_back(activeActors.back());
		}
	} 
	activeActors.push_back(new BackgroundParticles(vec3(1000, 1000, 200), 20000, shaderProgram));
	activeActors.push_back(new Bounds(vec2(500, 500), shaderProgram, vec3(0.2f, 1, 1)));
	activeActors.push_back(new ParticleEmitter(shaderProgram));

	for each (Actor* actor in activeActors) {
		actor->Initialize();
	}

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	MainLoop();

    return 0;
}

void MainLoop() {
	double lastFrame = 0;
	do {
		double deltaTime = glfwGetTime() - lastFrame;
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//camera->position = LerpVector(camera->position, activeActors.front()->position + vec3(0, 0, 64), 0.01f);
		//camera->lookAt = activeActors.front()->position;
		camera->Update();

		glm::mat4 Projection = camera->GetProjection();
		glm::mat4 View = camera->GetView();


		for each (Actor* actor in activeActors) {
			actor->Update(deltaTime * 100);
			glUseProgram(actor->shaderProgram);
			glm::quat rot = quat(actor->rotation);
			glm::mat4 model = glm::translate(glm::mat4(1.0f), actor->position) * glm::mat4_cast(rot);
			glm::mat4 mvp = Projection * View * model;
			glUniformMatrix4fv(shaderMvp, 1, GL_FALSE, &mvp[0][0]);
			actor->Render();
		}

		for each (Actor* actor in spawnQueue) {
			activeActors.push_back(actor);
		}
		spawnQueue.clear();
		for each (Actor* actor in despawnQueue) {
			activeActors.remove(actor);
			delete(actor);
		}
		despawnQueue.clear();

		lastFrame = glfwGetTime();
		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (!glfwWindowShouldClose(window));
}

void Spawn(Actor* actor) {
	spawnQueue.push_back(actor);
}

void Despawn(Actor* actor) {
	despawnQueue.push_back(actor);
}

GLFWwindow* GetWindow() {
	return window;
}

Camera* GetCamera() {
	return (camera);
}