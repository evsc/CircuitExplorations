#pragma once

#include "ofEvents.h"
#include "ofTrueTypeFont.h"
#include "analysisDisplay.h"
#include "channelDisplay.h"
#include "vizDisplay.h"
#include "guiButton.h"
#include "guiToggle.h"


class Display
{
public:
	Display(void);
	~Display(void);

	float x;
	float y;

	int channels;

	void fileNewData(int v1, int v2);

	void setup(float x, float y);
	void update();
	void draw(ofTrueTypeFont * font);

	analysisDisplay aBay;
	vector<channelDisplay> chBay;
	vizDisplay viz;

	void checkMouse(int x, int y);
	void click();

	bool _run;
	bool _show;

	// buttons
	vector<guiButton> buttons;

};
