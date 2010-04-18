#include "channelDisplay.h"
#include "ofMath.h"

float constrainF(float v, float low, float high) {
    return (v < low) ? low : ( (v > high) ? high : v );
}

channelDisplay::channelDisplay(void)
{
}

channelDisplay::~channelDisplay(void)
{
}


void channelDisplay::setup(float x, float y, char* n) {
	this->x = x;
	this->y = y;

	ax = x+100;
	ay = y;
	aw = 300;
	ah = 40;

	DC = true;
	len = 1024;
	voltage = 5;
	p = 0;

	_run = true;
	_show = true;

	name = n;

	clear();
	// fill with random numbers for testing
	//for(int i=0; i<len; i++) {
	//	data[i] = ofRandom(0,1);
	//}

	//buttons
	guiButton* b_run = new guiButton();
	b_run->setup(x,y+20,40,17,"run", "stop");
	b_run->_activated = true;
	buttons.push_back(*b_run);

	guiButton* b_show = new guiButton();
	b_show->setup(x+45,y+20,40,17,"show", "hide");
	b_show->_activated = true;
	buttons.push_back(*b_show);
}

void channelDisplay::draw(ofTrueTypeFont * font) {
	ofPushMatrix();
	ofTranslate(x,y,0);

	ofSetColor(0,0,0);
	font->drawString(name, 0,7);

	ofPopMatrix();

	if(_show) {
		drawArray();
	}

	for(int i=0; i<buttons.size(); i++) {
		buttons[i].draw(font);
	}
}

void channelDisplay::drawArray() {
	ofPushMatrix();
	ofTranslate(ax,ay,0);

	float mx = (float) aw / (float) (len-1);
	float my = (float) ah / 1.0f;

	ofFill();
	ofSetColor(255,0,0);
	ofBeginShape();
	ofVertex(0,ah);

	for(int i=0; i<len; i++) {
		ofVertex(i*mx, ah-getMemory(i)*my);
	}

	ofVertex((len-1)*mx,ah);
	ofEndShape();

	// draw outline
	ofSetColor(0,0,0);
	ofNoFill();
	ofRect(0,0,aw,ah);

	ofPopMatrix();
}

void channelDisplay::update() {

}

void channelDisplay::fileNewData(int v) {
	if(_run) {
		float fv = 0;
		if(DC) fv = (float) constrainF(v / 32767.0f,0,1);
		else fv = (float) constrainF(v / 32767.0f,-1,1);
		data[p] = fv;
		p++;
		if(p>=len) {
			p = 0;
			bool b = true;
			//ofNotifyEvent(filledArray, b, this);
		}
		//printf("file new data in %s: %i = %f\n", name, v, fv);
	}
}

void channelDisplay::clear() {
	p = 0;
	for(int i=0; i<len; i++) {
		data[i] = 0;
	}
}

void channelDisplay::setSize(float w, float h) {
	aw = w;
	ah = h;
}

void channelDisplay::setLen(int l) {
	len = l;
	if(len>MAX_LENGTH) len = MAX_LENGTH;
	clear();
	p = 0;
}

float channelDisplay::getMemory(int step) {
	int trueNo = p + step;
	if(trueNo>=len) trueNo-=len;
	return data[trueNo];
}


void channelDisplay::checkMouse(int x, int y) {
	for(int i=0; i<buttons.size(); i++) {
		buttons[i].checkMouse(x,y);
	}
}

void channelDisplay::click() {
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
