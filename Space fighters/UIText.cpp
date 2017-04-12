#include "UIText.h"
#include <sstream>
#include <algorithm>

using namespace std;

void UIText::SetText(string text) {
	transform(text.begin(), text.end(), text.begin(), ::toupper);
	vertices.clear(); 
	numberOfVerts = 0;
	string::const_iterator c;
	int cursorPosition = 0;
	for (c = text.begin(); c != text.end(); c++) {
		for (int i = 1; i < font->GetCharVerts((int)*c)[0]; i++){
			vertices.push_back(font->GetCharVerts((int)*c)[i] + (i % 2 == 1 ? (float)cursorPosition * 1.5f : 0));
			numberOfVerts++;
		}
		cursorPosition++;
	}

	RebindVertices();
}

void UIText::Render() {
	Actor::Render();

	glUniform3f(colorID, color.r, color.g, color.b);
	glDrawArrays(GL_LINES, 0, numberOfVerts);
	glDisableVertexAttribArray(0);
}