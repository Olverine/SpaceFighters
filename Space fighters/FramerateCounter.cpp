#include "FramerateCounter.h"

int f = 0;
double t = 0;

void FramerateCounter::Update(double deltaTime) {
	f++;
	t += deltaTime;
	position.x += 0.5f;
	printf("%f\n", position.x);
	if (t >= 1) {
		SetText(std::to_string(f) + " frames/second");
		f = 0;
		t = 0;
		ShrinkVector();
	}
}