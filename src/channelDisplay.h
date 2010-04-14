#pragma once

#include "ofTrueTypeFont.h"


class channelDisplay
{
public:
	channelDisplay(void);
	~channelDisplay(void);

	void draw(ofTrueTypeFont * font);
	void setup(int x, int y);
	void update();

	int x;
	int y;
};
