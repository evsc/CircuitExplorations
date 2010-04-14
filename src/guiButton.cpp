#include "guiButton.h"
#include "ofMain.h"

guiButton::guiButton(void)
{
}

guiButton::~guiButton(void)
{
}

void guiButton::setup(int x, int y, int w, int h, char *on, char *off) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	name_on = on;
	name_off = off;
	_activated = false;
	_on = true;
	_over = false;
}

void guiButton::draw(ofTrueTypeFont *font) {
	ofPushMatrix();
	ofTranslate(x,y,0);

	ofFill();
	if(!_on) ofSetColor(200,200,200);
	else if((_activated && _over) || _over) ofSetColor(50,50,50);
	else if(_activated && !_over) ofSetColor(0,0,0);
	else if(!_over && !_activated) ofSetColor(100,100,100);
	
	ofRect(0,0,w,h);

	ofSetColor(255,255,255);
	font->drawString( (_activated) ? name_off : name_on, 5,10);

	ofPopMatrix();
}

void guiButton::checkMouse(int x, int y) {
	if(_on) {
		int d = 0;
		_over = ( x > this->x-d && x < this->x+w+d && y > this->y-d && y < this->y+h+d) ? true : false;
	}
}

void guiButton::click() {
	if(_over && _on) {
		_activated = !_activated;
	}
}

void guiButton::update() {
	
}