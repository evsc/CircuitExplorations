#pragma once

#include "ofTrueTypeFont.h"


class guiButton
{
public:
	guiButton(void);
	~guiButton(void);

	int x;
	int y;
	int w;
	int h;

	char * name;
	char * name_on;
	char * name_off;

	bool _over;
	bool _activated;
	bool _on;

	void setup(int x, int y, int w, int h, char * on, char * off);

	void draw(ofTrueTypeFont * font);

	void checkMouse(int x, int y);

	void click();

	void update();

};
