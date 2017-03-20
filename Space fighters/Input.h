#pragma once
#include <Engine.h>

class Input
{
public:
	static void Init();
	static float GetAxis(int controller, int axis);
	static bool GetButton(int controller, int button);
	static bool GetButtonDown(int controller, int button);
};

