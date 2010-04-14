#pragma once

#include "ofTrueTypeFont.h"


class analysisDisplay
{
public:
	analysisDisplay(void);
	~analysisDisplay(void);

	void draw(ofTrueTypeFont * font);
	void setup(int x, int y);
	void update();

	int x;
	int y;

	

};
