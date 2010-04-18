#include "Display.h"

Display::Display(void)
{
}

Display::~Display(void)
{
}

void Display::setup(float x, float y) {
	this->x = x;
	this->y = y;

	channels = 2;

	channelDisplay* ch1 = new channelDisplay();
	ch1->setup(x,y+50,"CHANNEL 1");
	//ch1->setLen(128);
	chBay.push_back(*ch1);
	channelDisplay* ch2 = new channelDisplay();
	ch2->setup(x,y+100,"CHANNEL 2");
	//ch2->setLen(128);
	chBay.push_back(*ch2);

	aBay.setup(x+400,y);
	viz.setup(x,y+200);

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

void Display::draw(ofTrueTypeFont * font) {
	ofPushMatrix();
	ofTranslate(x,y,0);

	ofSetColor(0,0,0);
	font->drawString("DISPLAY", 0,0);

	ofPopMatrix();

	for(int i=0; i<buttons.size(); i++) {
		buttons[i].draw(font);
	}

	if(_show) {
		for(int i=0; i<chBay.size(); i++) {
			chBay[i].draw(font);
		}

		//aBay.draw(font);
		viz.draw(font);
	}
}

void Display::update() {
	
	if(_run) {
		for(int i=0; i<chBay.size(); i++) {
			chBay[i].update();
		}
		
		aBay.update();
		viz.update();
		
	}
	
}

void Display::fileNewData(int v1, int v2) {
	
	if(_run) {
		if(chBay[0]._run) {
			chBay[0].fileNewData(v1);
		}
		if(chBay[1]._run) {
			chBay[1].fileNewData(v2);
		}

		viz.clearData();
		viz.fileNewData(0,v1);
		viz.fileNewData(1,v2);
		viz.processData();
	}
}

void Display::checkMouse(int x, int y) {
	for(int i=0; i<buttons.size(); i++) {
		buttons[i].checkMouse(x,y);
	}
	
	if(_run) {
		for(int i=0; i<chBay.size(); i++) {
			chBay[i].checkMouse(x,y);
		}

		aBay.checkMouse(x,y);
		viz.checkMouse(x,y);

	}

}

void Display::click() {
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
	
	if(_run) {
		for(int i=0; i<chBay.size(); i++) {
			chBay[i].click();
		}
		aBay.click();
		viz.click();
	}
}
