#pragma once

#include "ofTrueTypeFont.h"

class guiButton
{
public:
	guiButton(void);
	~guiButton(void);

	float x;
	float y;
	float w;
	float h;

	char * name;
	char * name_on;
	char * name_off;

	bool _over;
	bool _activated;
	bool _on;

	void setup(float x, float y, float w, float h, char * on, char * off);

	void draw(ofTrueTypeFont * font);

	void checkMouse(int x, int y);

	void click();

	void update();

};
