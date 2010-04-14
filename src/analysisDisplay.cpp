#include "analysisDisplay.h"

analysisDisplay::analysisDisplay(void)
{
}

analysisDisplay::~analysisDisplay(void)
{
}


void analysisDisplay::setup(int x, int y) {
	this->x = x;
	this->y = y;
}

void analysisDisplay::draw(ofTrueTypeFont * font) {
	ofPushMatrix();
	ofTranslate(x,y,0);
	
	ofSetColor(0,0,0);
	font->drawString("ANALYSIS", 0,0);

	ofPopMatrix();
}