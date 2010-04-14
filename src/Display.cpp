#include "Display.h"

Display::Display(void)
{
}

Display::~Display(void)
{
}

void Display::setup(int x, int y) {
	this->x = x;
	this->y = y;

	chBay.setup(x,y+50);
	aBay.setup(x,y+250);
	viz.setup(x,y+400);

	_run = true;
}

void Display::draw(ofTrueTypeFont * font) {
	ofPushMatrix();
	ofTranslate(x,y,0);

	ofSetColor(0,0,0);
	font->drawString("DISPLAY", 0,0);

	ofPopMatrix();

	chBay.draw(font);
	aBay.draw(font);
	viz.draw(font);
}

void Display::update() {
	if(_run) {
		chBay.update();
		aBay.update();
		viz.update();
	}
}