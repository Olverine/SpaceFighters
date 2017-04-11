#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H 
#include <Engine.h>

class Text
{
	GLuint VertexArrayID;
	GLuint colorID;
public:
	Text(const char* font, int size, vec3 color);

	void RenderText(vec3 position, std::string text);
};