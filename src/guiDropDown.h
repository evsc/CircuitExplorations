#pragma once

#include "ofTrueTypeFont.h"

class guiDropDown
{
public:
	guiDropDown(void);
	~guiDropDown(void);

	float x;
	float y;
	float w;

	bool _on;
	bool _over;
	
	void setup(float x, float y) {
		this->x = x;
		this->y = y;
	}

};
