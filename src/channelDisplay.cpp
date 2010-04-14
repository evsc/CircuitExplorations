#include "channelDisplay.h"

channelDisplay::channelDisplay(void)
{
}

channelDisplay::~channelDisplay(void)
{
}


void channelDisplay::setup(int x, int y) {
	this->x = x;
	this->y = y;
}

void channelDisplay::draw(ofTrueTypeFont * font) {
	ofPushMatrix();
	ofTranslate(x,y,0);

	ofSetColor(0,0,0);
	font->drawString("CHANNEL", 0,0);

	ofPopMatrix();
}