#include "vizDisplay.h"

vizDisplay::vizDisplay(void)
{
}

vizDisplay::~vizDisplay(void)
{
}

void vizDisplay::setup(int x, int y) {
	this->x = x;
	this->y = y;
}

void vizDisplay::draw(ofTrueTypeFont * font) {
	ofPushMatrix();
	ofTranslate(x,y,0);

	ofSetColor(0,0,0);
	font->drawString("VISUALIZATION", 0,0);

	ofPopMatrix();
}