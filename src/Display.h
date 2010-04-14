#pragma once

#include "ofTrueTypeFont.h"
#include "analysisDisplay.h"
#include "channelDisplay.h"
#include "vizDisplay.h"
#include "guiButton.h"

class Display
{
public:
	Display(void);
	~Display(void);

	int x;
	int y;

	void setup(int x, int y);
	void update();
	void draw(ofTrueTypeFont * font);

	analysisDisplay aBay;
	channelDisplay chBay;
	vizDisplay viz;

	bool _run;

	// buttons
	vector<guiButton> buttons;

};
