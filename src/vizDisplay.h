#pragma once

#include "ofTrueTypeFont.h"


class vizDisplay
{
public:
	vizDisplay(void);
	~vizDisplay(void);

	void draw(ofTrueTypeFont * font);
	void setup(int x, int y);
	void update();

	int x;
	int y;
};
