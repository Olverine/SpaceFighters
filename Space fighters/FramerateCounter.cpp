#include "FramerateCounter.h"

int f = 0;
double t = 0;
double lrp = 0;

void FramerateCounter::Update(double deltaTime) {
	f++;
	t += deltaTime / 100;
	lrp = Lerp(lrp, deltaTime / 100, 0.01f);
	if (t >= 1.0) {
		SetText(std::to_string(f) + " frames/second " + std::to_string(lrp) + " seconds/frame");
		f = 0;
		t = 0;
	}
}