#include "PlayerShip.h"
#include "MultiChaseCam.h"
#include <PopText.h>

PlayerShip* players[4];
int numberOfPlayers;

PlayerShip::PlayerShip(int controllerId, GLuint shaderProgram, vec3 color) {
	vertices = {
		-0.5f, -1.0f, 0.0f,
		0.5f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};

	playerControllerId = controllerId;

	this->color = color;
	this->shaderProgram = shaderProgram;
	colorID = glGetUniformLocation(shaderProgram, "inColor");

	players[numberOfPlayers] = this;
	numberOfPlayers++;

	healthText = new UIText(shaderProgram, GetDefaultFont());
	healthText->position = glm::vec3(1, 14 - 0.75f * (float)playerControllerId, 0);
	healthText->scale = glm::vec3(.2f, 0.2f, 1.0f);
	healthText->Initialize();
	healthText->color = color;
	Spawn(healthText);
	healthText->SetText("Player " + std::to_string(controllerId + 1) + ": " + std::to_string(health) + "       None");

	//engineParticles = new ParticleEmitter(shaderProgram);
	//Spawn(engineParticles);
	//engineParticles->Initialize();
}

void PlayerShip::Update(double deltaTime) {
	vec2 inputVector = vec2(glm::radians(-Input::GetAxis(playerControllerId, 0)), glm::radians(Input::GetAxis(playerControllerId, 1)));
	if (length(inputVector) > 0) {
		float angle = atan2(inputVector.x, inputVector.y);
		rotation = vec3(0, 0, LerpAngle(rotation.z, angle, angularSpeed * deltaTime));
	}

	velocity += vec3(-sin(rotation.z), cos(rotation.z), 0) * length(inputVector) * (float)(acceleration * deltaTime);
	position += velocity;
	velocity = LerpVector(velocity, vec3(0, 0, 0), drag);
//	engineParticles->position = position;
	if (Input::GetButtonDown(playerControllerId, 0)) {
		vec3 pVelocity = vec3(-sin(rotation.z), cos(rotation.z), 0);
		Projectile *tmp_spawn = new Projectile(shaderProgram, position, (pVelocity * 2.0f) + velocity, this);
		Spawn(tmp_spawn);
	}
	//engineParticles->Emit(position, vec3(sin(rotation.z), -cos(rotation.z), 0) * length(inputVector));'

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

void PlayerShip::Render() {
	Actor::Render();

	glUniform3f(colorID, color.r, color.g, color.b);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
}  

void PlayerShip::Damage() {
	if (health <= 0) return;

	new PopText(shaderProgram, GetDefaultFont(), position - vec3(2,0,0), vec3(1, 1, 1), "hit");

	health--;
	healthText->SetText("Player " + std::to_string(playerControllerId + 1) + "  " + std::to_string(health) + "       None");

	if (health <= 0) {
		healthText->SetText("Player " + std::to_string(playerControllerId + 1) + "  Dead \x07  None");
		dynamic_cast<MultiChaseCam*>(GetCamera())->RemoveTarget(this);
		Despawn(this);
	}
}

PlayerShip* PlayerShip::GetShip(int playerController) {
	return players[playerController];
}

int PlayerShip::GetNumberOfplayers() {
	return numberOfPlayers;
}