#include "PlayerShip.h"
#include "MultiChaseCam.h"
#include <PopText.h>

PlayerShip* players[4];
int numberOfPlayers;

std::string powerupNames[] = {
	"None",
	"Machine gun",
	"Multi barrel",
	"Turbo"
};

PlayerShip::PlayerShip(int controllerId, GLuint shaderProgram, vec3 color) {
	vertices = {
		-0.5f, -1.0f, 0.0f,
		0.5f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};

	Initialize();

	playerControllerId = controllerId;

	this->color = color;
	this->shaderProgram = shaderProgram;
	colorID = glGetUniformLocation(shaderProgram, "inColor");

	players[numberOfPlayers] = this;
	numberOfPlayers++;

	healthText = UIText(shaderProgram, GetDefaultFont());
	healthText.position = glm::vec3(1, 14 - 0.75f * (float)playerControllerId, 0);
	healthText.scale = glm::vec3(.2f, 0.2f, 1.0f);
	healthText.Initialize();
	healthText.color = color;
	Spawn(healthText);
	healthText.SetText("Player " + std::to_string(controllerId + 1) + ": " + std::to_string(health) + "       None");
}

void PlayerShip::Update(double deltaTime) {
	printf("%u (%f, %f)\n", id, position.x, position.y);
	vec2 inputVector = vec2(glm::radians(-Input::GetAxis(playerControllerId, 0)), glm::radians(Input::GetAxis(playerControllerId, 1)));
	if (length(inputVector) > 0) {
		float angle = atan2(inputVector.x, inputVector.y);
		rotation = vec3(0, 0, LerpAngle(rotation.z, angle, angularSpeed * float(deltaTime)));
	}

	velocity += vec3(-sin(rotation.z), cos(rotation.z), 0) * length(inputVector) * (float)(acceleration * deltaTime);
	position += velocity;
	velocity = LerpVector(velocity, vec3(0, 0, 0), drag);

	if (powerup == 1) {
		if (Input::GetButton(playerControllerId, 0)) {
			if (fireTime >= fireRate) {
				Shoot(rotation.z);
				fireTime = 0;
			}
			else {
				fireTime += float(deltaTime);
			}
		}
	}
	else {
		if (Input::GetButtonDown(playerControllerId, 0)) {
			if (powerup == 2) {
				for (int i = 0; i < 5; i++) {
					Shoot((rotation.z - glm::radians(10.0f)) + glm::radians((float)i * 4));
				}
			}
			else {
				Shoot(rotation.z);
			}
		}
	}

	if (position.x > 250) {
		position.x = 250;
		velocity.x *= -1;
	}
	else if (position.x < -250) {
		position.x = -250;
		velocity.x *= -1;
	}
	if (position.y > 250) {
		position.y = 250;
		velocity.y *= -1;
	}
	else if (position.y < -250) {
		position.y = -250;
		velocity.y *= -1;
	}
}

void PlayerShip::Shoot(float direction) {
	vec3 pVelocity = vec3(-sin(direction), cos(direction), 0);
	Spawn(Projectile(shaderProgram, position, (pVelocity * 2.0f) + velocity, this));
}

void PlayerShip::Render() {
	printf("RENDERAR :D\n");
	Actor::Render();

	glUniform3f(colorID, color.r, color.g, color.b);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
}  

void PlayerShip::Damage() {
	if (health <= 0) return;

	Spawn(PopText(shaderProgram, GetDefaultFont(), position - vec3(2,0,0), vec3(1, 1, 1), "hit"));

	health--;

	if (health <= 0) {
		healthText.SetText("Player " + std::to_string(playerControllerId + 1) + "  Dead \x07  None");
		GetCamera().RemoveTarget(id);
		Despawn(id);
	}

	UpdateText();
}

void PlayerShip::UpdateText() {
	if (health <= 0) {
		healthText.SetText("Player " + std::to_string(playerControllerId + 1) + "  Dead \x07  ");
	}
	else {
		healthText.SetText("Player " + std::to_string(playerControllerId + 1) + "  " + std::to_string(health) + "       None");
	}
}

PlayerShip* PlayerShip::GetShip(int playerController) {
	return players[playerController];
}

int PlayerShip::GetNumberOfplayers() {
	return numberOfPlayers;
}