#include "analysisDisplay.h"

analysisDisplay::analysisDisplay(void)
{
}

analysisDisplay::~analysisDisplay(void)
{
}


void analysisDisplay::setup(float x, float y) {
	this->x = x;
	this->y = y;

	_run = true;
	_show = true;

	//buttons
	guiButton* b_run = new guiButton();
	b_run->setup(x,y+10,40,17,"run", "stop");
	b_run->_activated = true;
	buttons.push_back(*b_run);

	guiButton* b_show = new guiButton();
	b_show->setup(x+45,y+10,40,17,"show", "hide");
	b_show->_activated = true;
	buttons.push_back(*b_show);
}

void analysisDisplay::draw(ofTrueTypeFont * font) {
	ofPushMatrix();
	ofTranslate((float)x,(float)y,0);
	
	ofSetColor(0,0,0);
	font->drawString("ANALYSIS", 0,0);

	ofPopMatrix();

	for(int i=0; i<buttons.size(); i++) {
		buttons[i].draw(font);
	}
}

void analysisDisplay::update() {

}

void analysisDisplay::checkMouse(int x, int y) {
	for(int i=0; i<buttons.size(); i++) {
		buttons[i].checkMouse(x,y);
	}
}

void analysisDisplay::click() {
	for(int i=0; i<buttons.size(); i++) {
		if(buttons[i]._over) {
			switch(i) {
				case 0:	// run / stop
					buttons[i].click();
					_run = !_run;
					break;
				case 1:
					buttons[i].click();
					_show = !_show;
					break;
			}
		}
	}
}
