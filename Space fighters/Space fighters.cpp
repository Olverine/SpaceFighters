#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <Engine.h>
#include <vector>
#include <BackgroundParticles.h>
#include <Bounds.h>
#include <MultiChaseCam.h>
#include <Text.h>
#include <FramerateCounter.h>
#include <PowerupSpawner.h>

void MainLoop();
GLFWwindow* window;
bool fullscreen = false;

std::vector<Actor*> activeActors;

std::vector<Actor*> spawnQueue;
std::vector<Actor*> despawnQueue;
Camera* camera;
GLuint shaderMvp = 0;
Text* text;
Font* defaultFont;

const char* font = "fonts/ITCEDSCR.TTF";

int main()
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 1);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(1280, 720, "Game", fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
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

	defaultFont = new Font("fonts/font");

	//text = new Text(font, 48, vec3(1, 0, 0));
	
	// Load shaders
	GLuint shaderProgram = LoadShaders("shaders/basicVertex.glsl", "shaders/basicFragment.glsl");

	UIText* playerLabel = new UIText(shaderProgram, defaultFont);
	playerLabel->position = vec3(1, 15, 0);
	playerLabel->scale = vec3(0.2f, 0.2f, 0);
	playerLabel->SetText("Name      Health  Powerup");
	activeActors.push_back(playerLabel);

	// Create players
	vec3 colors[] = {
		vec3(0, 0.5f, 1),
		vec3(1, 0, 0),
		vec3(0, 1, 0),
		vec3(1, 1, 0)
	};

	camera = new MultiChaseCam();
	for (int i = 0; i < 4; i++) {
		if (glfwJoystickPresent(i)) {
			activeActors.push_back(new PlayerShip(i, shaderProgram, colors[i]));
			dynamic_cast<MultiChaseCam*>(camera)->targets.push_back(activeActors.back());
			activeActors.back()->position.x = -24 + i * 16;
		}
	} 
	activeActors.push_back(new BackgroundParticles(vec3(1000, 1000, 200), 20000, shaderProgram));
	activeActors.push_back(new Bounds(vec2(500, 500), shaderProgram, vec3(0.2f, 1, 1)));
	//activeActors.push_back(new ParticleEmitter(shaderProgram));

	activeActors.push_back(new PowerupSpawner(shaderProgram));

	for each (Actor* actor in activeActors) {
		actor->Initialize();
	}
	
	FramerateCounter* fc = new FramerateCounter(shaderProgram);
	fc->scale = vec3(0.2, 0.2, 0.2);
	fc->position = vec3(1, -0.5, 0);
	fc->Initialize();
	activeActors.push_back(fc);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	glfwSetTime(0);

	MainLoop();

    return 0;
}

double lastTime = 0;

void MainLoop() {
	do {
		double time = glfwGetTime();
		double deltaTime = (time - lastTime);
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//camera->position = LerpVector(camera->position, activeActors.front()->position + vec3(0, 0, 64), 0.01f);
		//camera->lookAt = activeActors.front()->position;
		camera->Update();

		glm::mat4 projection = camera->GetProjection();
		glm::mat4 UIProjection = glm::ortho(0.0f, 32.0f, -2.0f, 16.0f);
		glm::mat4 view = camera->GetView();
		glm::mat4 mvp;

		for each (Actor* actor in activeActors) {
			actor->Update(deltaTime * 100);
			glUseProgram(actor->shaderProgram);
			glm::quat rot = quat(actor->rotation);
			glm::mat4 model = glm::translate(glm::mat4(1.0f), actor->position) * glm::mat4_cast(rot) * glm::scale(mat4(1.0f),actor->scale);
			if (actor->fixedOnScreen) {
				mvp = /*mat4(1.0f)*/UIProjection * model;
			}
			else {
				mvp = projection * view * model;
			}
			glUniformMatrix4fv(shaderMvp, 1, GL_FALSE, &mvp[0][0]);
			actor->Render();
		}

		for each (Actor* actor in spawnQueue) {
			activeActors.push_back(actor);
		}
		spawnQueue.clear();
		for each (Actor* actor in despawnQueue) {
			for (int i = 0; i < activeActors.size(); i++) {
				if (activeActors[i] == actor) {
					activeActors.erase(activeActors.begin() + i);
				}
			}
			delete(actor);
		}
		despawnQueue.clear();

		glfwSwapBuffers(window);
		glfwPollEvents();
		lastTime = time;
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

Font* GetDefaultFont() {
	return defaultFont;
}