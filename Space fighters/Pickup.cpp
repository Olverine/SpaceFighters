#include "Pickup.h"
#include "Engine.h"

Pickup::Pickup(GLuint shaderProgram, std::string text, glm::vec3 color)
{
	this->shaderProgram = shaderProgram;
	this->text = text;
	this->color = color;
	//position.x = (rand() % 1000);
	//position.y = (rand() % 1000) - 500;
	label = new UIText(shaderProgram, GetDefaultFont());
	label->position = position;
	label->fixedOnScreen = false;
	label->scale = glm::vec3(1, 1, 1);
	label->position = glm::vec3(-0.75f * text.length(), 1, 2);
	label->Initialize();
	label->SetText(text);
	Spawn(label);

	vertices.push_back(0);
	vertices.push_back(-3);
	vertices.push_back(0);

	vertices.push_back(-3);
	vertices.push_back(0);
	vertices.push_back(0);

	vertices.push_back(3);
	vertices.push_back(0);
	vertices.push_back(0);

	vertices.push_back(0);
	vertices.push_back(3);
	vertices.push_back(0);

	colorID = glGetUniformLocation(shaderProgram, "inColor");

	Initialize();
}

Pickup::~Pickup() {
	Despawn(label);
	delete(label);
}

void Pickup::Render() {
	Actor::Render();

	glUniform3f(colorID, color.r, color.g, color.b);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glDisableVertexAttribArray(0);
}

void Pickup::Update(double deltaTime) {
	rotation.y += 0.02f * deltaTime;
	for (int i = 0; i < PlayerShip::GetNumberOfplayers(); i++) {
		if (Distance(glm::vec2(position.x, position.y), glm::vec2(PlayerShip::GetShip(i)->position.x, PlayerShip::GetShip(i)->position.y)) <= 3) {
			OnPicked(PlayerShip::GetShip(i));
			break;
		}
	}
}

void Pickup::OnPicked(PlayerShip* player) {

}