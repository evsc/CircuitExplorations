#pragma once

#include "ofTrueTypeFont.h"
#include "guiButton.h"

class analysisDisplay
{
public:
	analysisDisplay(void);
	~analysisDisplay(void);

	void draw(ofTrueTypeFont * font);
	void setup(float x, float y);
	void update();

	float x;
	float y;

	void checkMouse(int x, int y);
	void click();

	bool _run;
	bool _show;

	// buttons
	vector<guiButton> buttons;

};
