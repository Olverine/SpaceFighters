#pragma once
class Font
{
	float points[256][40];
public:
	Font(const char*);
	float* GetCharVerts(int asciiValue);
};

