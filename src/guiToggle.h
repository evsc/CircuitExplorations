#pragma once

#include "ofTrueTypeFont.h"

class guiToggle
{
public:
	guiToggle(void);
	~guiToggle(void);

	bool _on;
	bool _activated;

	bool _over;

	char* name;

	float x;
	float y;
	float w;
	float h;

	void setup(float x, float y, char* n, bool a) {
		this->x = x;
		this->y = y;
		w = h = 10;
		_on = true;
		_activated = a;
		name = n;
	}

	void checkMouse(int x, int y) {
		if(_on) {
			int d = 2;
			_over = ( x > this->x-d && x < this->x+w+d && y > this->y-d && y < this->y+h+d) ? true : false;
		}
	}

	void click() {
		if(_over && _on) {
			_activated = !_activated;
		}
	}

	void draw(ofTrueTypeFont *font) {
		ofPushMatrix();
		ofTranslate(x,y,0);

		if(!_on) ofSetColor(100,100,100); else ofSetColor(0,0,0);
		if(_activated) ofFill(); else ofNoFill();
		ofRect(0,0,w,h);

		if(!_activated) ofSetColor(100,100,100);
		font->drawString(name, w+2,7);

		ofPopMatrix();
	}
	

};
