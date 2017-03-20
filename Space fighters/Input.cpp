#include "Input.h"

std::vector<std::vector<char>> lastButtonStates;

void Input::Init() {
	lastButtonStates.resize(4);
	int count;
	const unsigned char* axes = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &count);
	for (int i = 0; i < 4; i++) {
		lastButtonStates[i].resize(count);
	}
}

float Input::GetAxis(int controller, int axis) {
	if (!glfwJoystickPresent(controller)) return 0;
	int count;
	const float* axes = glfwGetJoystickAxes(controller, &count);
	return axes[axis];
}

bool Input::GetButton(int controller, int button) {
	if (!glfwJoystickPresent(controller)) return false;
	int count;
	const unsigned char* buttons = glfwGetJoystickButtons(controller, &count);
	return buttons[button] == GLFW_PRESS;
}

bool Input::GetButtonDown(int controller, int button) {
	if (!glfwJoystickPresent(controller)) return false;
	int count;
	char lastbuttonState = lastButtonStates[controller][button];
	char buttonState = glfwGetJoystickButtons(controller, &count)[button];
	if (buttonState == GLFW_PRESS && lastbuttonState == GLFW_RELEASE) {
		lastButtonStates[controller][button] = buttonState;
		return true;
	}
	lastButtonStates[controller][button] = buttonState;
	return false;
}