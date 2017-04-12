#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <Engine.h>
#include <vector>
#include <BackgroundParticles.h>
#include <Bounds.h>
#include <MultiChaseCam.h>
#include <FramerateCounter.h>
#include <PowerupPickup.h>

void MainLoop();
GLFWwindow* window;
bool fullscreen = false;

std::vector<Actor> activeActors;

std::vector<Actor> spawnQueue;
std::vector<unsigned> despawnQueue;
MultiChaseCam camera;
GLuint shaderMvp = 0;
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

	UIText playerLabel = UIText(shaderProgram, defaultFont);
	playerLabel.position = vec3(1, 15, 0);
	playerLabel.scale = vec3(0.2f, 0.2f, 0);
	playerLabel.SetText("Name      Health  Powerup");
	Spawn(playerLabel);

	Spawn(PowerupPickup(shaderProgram));

	// Create players
	vec3 colors[] = {
		vec3(0, 0.5f, 1),
		vec3(1, 0, 0),
		vec3(0, 1, 0),
		vec3(1, 1, 0)
	};

	camera = MultiChaseCam();
	for (int i = 0; i < 4; i++) {
		if (glfwJoystickPresent(i)) {
			printf("HEJ :) \x07");
			PlayerShip ps = PlayerShip(i, shaderProgram, colors[i]);
			ps.position.x = -24 + i * 16;
			Spawn(ps);
			camera.targets.push_back((PlayerShip *)&ps);
		}
	} 
	Spawn(BackgroundParticles(vec3(1000, 1000, 200), 20000, shaderProgram));
	Spawn(Bounds(vec2(500, 500), shaderProgram, vec3(0.2f, 1, 1)));
	Spawn(ParticleEmitter(shaderProgram));

	for each (Actor actor in activeActors) {
		actor.Initialize();
	}
	
	FramerateCounter fc = FramerateCounter(shaderProgram);
	fc.scale = vec3(0.2, 0.2, 0.2);
	fc.position = vec3(1, -0.5, 0);
	fc.Initialize();
	Spawn(fc);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	MainLoop();

    return 0;
}

double lastFrame = 0;

void MainLoop() {
	do {
		double time = glfwGetTime();
		double deltaTime = time - lastFrame;
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//camera->position = LerpVector(camera->position, activeActors.front()->position + vec3(0, 0, 64), 0.01f);
		//camera->lookAt = activeActors.front()->position;
		camera.Update();

		glm::mat4 projection = camera.GetProjection();
		glm::mat4 UIProjection = glm::ortho(0.0f, 32.0f, -2.0f, 16.0f);
		glm::mat4 view = camera.GetView();
		glm::mat4 mvp;

		for each (Actor actor in activeActors) {
			printf("GGWP %u\n", actor.id);
			actor.Update(deltaTime * 100);
			glUseProgram(actor.shaderProgram);
			glm::quat rot = quat(actor.rotation);
			glm::mat4 model = glm::translate(glm::mat4(1.0f), actor.position) * glm::mat4_cast(rot) * glm::scale(mat4(1.0f),actor.scale);
			if (actor.fixedOnScreen) {
				mvp = /*mat4(1.0f)*/UIProjection * model;
			}
			else {
				mvp = projection * view * model;
			}
			glUniformMatrix4fv(shaderMvp, 1, GL_FALSE, &mvp[0][0]);
			actor.Render();
		}

		for each (Actor actor in spawnQueue) {
			activeActors.push_back(actor);
			printf("Spawned: %u\n%i\n", actor.id, activeActors.size());
			activeActors.back().Render();
		}
		spawnQueue.clear();
		for each (unsigned id in despawnQueue) {
			for (int i = 0; i < activeActors.size(); i++) {
				if (activeActors[i].id == id) {
					activeActors.erase(activeActors.begin() + i);
					printf("Despawned: %u\n", id);
				}
			}
		}
		despawnQueue.clear();

		glfwSwapBuffers(window);
		glfwPollEvents();
		lastFrame = time;
	} while (!glfwWindowShouldClose(window));
}

unsigned id = 0;
void Spawn(Actor actor) {
	actor.id = id++;
	spawnQueue.push_back(actor);
	printf("%u %f %f\n", actor.id, actor.position.x, actor.position.y);
}

void Despawn(unsigned id) {
	despawnQueue.push_back(id);
}

GLFWwindow* GetWindow() {
	return window;
}

MultiChaseCam GetCamera() {
	return (camera);
}

Font* GetDefaultFont() {
	return defaultFont;
}

void ShrinkVector() {
	//activeActors.shrink_to_fit();
	activeActors.swap(activeActors);
}