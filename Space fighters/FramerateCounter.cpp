#include "FramerateCounter.h"

int f = 0;
int t = 0;

void FramerateCounter::Update(double deltaTime) {
	f++;
	t += deltaTime;
	if (t >= 1) {
		SetText(std::to_string(f) + " frames/second");
		f = 0;
		t = 0;
	}
}