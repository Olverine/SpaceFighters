#include "Font.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Font::Font(const char* file)
{
	ifstream fontFile;
	fontFile.open("fonts/font");
	string output[256];
	int line = 0;
	if (fontFile.is_open()) {

		while (!fontFile.eof()) {
			getline(fontFile, output[line]);
			istringstream ss(output[line]);
			string token;

			int i = 0;
			while (getline(ss, token, ',')) {
				points[line][1 + i] = stof(token);
				//cout << points[line][1 + i] << ", ";
				i++;
			}
			//cout << " (" << i << ")" << endl;
			points[line][0] = (float)i + 1;

			line++;
		}
	}
	fontFile.close();
}

float* Font::GetCharVerts(int asciiValue) {
	return points[asciiValue];
}