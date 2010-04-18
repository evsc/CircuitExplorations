#include "vizDisplay.h"
#include "ofImage.h"

vizDisplay::vizDisplay(void)
{
}

vizDisplay::~vizDisplay(void)
{
}

void vizDisplay::setup(float x, float y) {
	this->x = x;
	this->y = y;

	_run = true;
	_show = true;

	iw = 500;
	ih = 500;

	dImg.allocate(iw,ih,OF_IMAGE_COLOR);
	
	dw = 500;
	dh = 500;

	vizMode = 1;
	p = 0;
	bufferCount = 0;

	channels = 2;
	settingOptions = 3;
	for(int i=0; i<channels*settingOptions; i++) {
		vizSetting[i] = false;
	}

	randomImg();

	//buttons
	guiButton* b_run = new guiButton();
	b_run->setup(x,y+10,40,17,"run", "stop");
	b_run->_activated = true;
	buttons.push_back(*b_run);

	guiButton* b_show = new guiButton();
	b_show->setup(x+45,y+10,40,17,"show", "hide");
	b_show->_activated = true;
	buttons.push_back(*b_show);

	guiButton* b_clear = new guiButton();
	b_clear->setup(x,y+30,40,17,"clear", "clear");
	buttons.push_back(*b_clear);

	guiButton* b_save = new guiButton();
	b_save->setup(x+45,y+30,40,17,"save", "save");
	buttons.push_back(*b_save);


	// channel settings buttons
	guiButton* ch1_r = new guiButton();
	ch1_r->setup(x+300,y+10,20,17,"R","R");
	chSettings.push_back(*ch1_r);
	guiButton* ch1_g = new guiButton();
	ch1_g->setup(x+325,y+10,20,17,"G","G");
	chSettings.push_back(*ch1_g);
	guiButton* ch1_b = new guiButton();
	ch1_b->setup(x+350,y+10,20,17,"B","B");
	chSettings.push_back(*ch1_b);

	guiButton* ch2_r = new guiButton();
	ch2_r->setup(x+300,y+30,20,17,"R","R");
	chSettings.push_back(*ch2_r);
	guiButton* ch2_g = new guiButton();
	ch2_g->setup(x+325,y+30,20,17,"G","G");
	chSettings.push_back(*ch2_g);
	guiButton* ch2_b = new guiButton();
	ch2_b->setup(x+350,y+30,20,17,"B","B");
	chSettings.push_back(*ch2_b);
}

void vizDisplay::draw(ofTrueTypeFont * font) {
	ofPushMatrix();
	ofTranslate(x,y,0);

	ofSetColor(0,0,0);
	font->drawString("VISUALIZATION", 0,0);

	if(_show) {
		ofSetColor(0xFFFFFF);
		dImg.draw(0,50,dw,dh);

		// channel settings
		ofSetColor(0,0,0);
		font->drawString("Channel 1", 230,20);
		font->drawString("Channel 2", 230,40);
	}

	ofPopMatrix();

	for(int i=0; i<buttons.size(); i++) {
		buttons[i].draw(font);
	}
	for(int i=0; i<chSettings.size(); i++) {
		chSettings[i].draw(font);
	}
	
}

void vizDisplay::update() {
	if(_run) {
		processBuffer();
		//randomImg();
	} else {
		//setPixel(5250,(unsigned char)(ofRandomuf() * 255),(unsigned char)(ofRandomuf() * 255),(unsigned char)(ofRandomuf() * 255));
	}
}

void vizDisplay::checkMouse(int x, int y) {
	for(int i=0; i<buttons.size(); i++) {
		buttons[i].checkMouse(x,y);
	}
	for(int i=0; i<chSettings.size(); i++) {
		chSettings[i].checkMouse(x,y);
	}
}

void vizDisplay::click() {
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
				case 2:
					clearImg();
					break;
				case 3:
					saveImg();
					break;
			}
		}
	}
	for(int i=0; i<chSettings.size(); i++) {
		if(chSettings[i]._over) {
			switch(i) {
				case 0:	// ch1 R
					chSettings[i].click();
					vizSetting[i] = !vizSetting[i];
					break;
				case 1:	// ch1 G
					chSettings[i].click();
					vizSetting[i] = !vizSetting[i];
					break;
				case 2:	// ch1 B
					chSettings[i].click();
					vizSetting[i] = !vizSetting[i];
					break;
				case 3:	// ch2 R
					chSettings[i].click();
					vizSetting[i] = !vizSetting[i];
					break;
				case 4:	// ch2 G
					chSettings[i].click();
					vizSetting[i] = !vizSetting[i];
					break;
				case 5:	// ch2 B
					chSettings[i].click();
					vizSetting[i] = !vizSetting[i];
					break;
			}
		}
	}
}

void vizDisplay::randomImg() {
	pixels  = dImg.getPixels();
	int iw = dImg.getWidth();
	int ih = dImg.getHeight();
	//printf("randomize dImg: %i|%i\n",iw,ih);
	int index = 0;
	for(int i=0; i<iw; i++) {
		for(int j=0; j<ih; j++) {
			index = (j*iw + i)*3;
			//if(i==0 && j==0) printf("%i %i %i  \n",pixels[index+0],pixels[index+1],pixels[index+2]);
			pixels[index + 0] = (unsigned char)(ofRandomuf() * 255);
			pixels[index + 1] = (unsigned char)(ofRandomuf() * 255);
			pixels[index + 2] = (unsigned char)(ofRandomuf() * 255);
			//if(i==0 && j==0) printf("-> %i %i %i  \n",pixels[index+0],pixels[index+1],pixels[index+2]);
		}
	}
	dImg.update();
}

void vizDisplay::setPixel(int index, unsigned char r, unsigned char g, unsigned char b) {
	pixels  = dImg.getPixels();
	pixels[index*3 + 0] = r;
	pixels[index*3 + 1] = g;
	pixels[index*3 + 2] = b;
	dImg.update();
}

void vizDisplay::clearData() {
	if(_run) {
		//printf("clear\n");
		for(int i=0; i<channels; i++) {
			newValues[i] = 0;
		}
	}
}

void vizDisplay::clearImg() {
	p = 0;
	pixels  = dImg.getPixels();
	int iw = dImg.getWidth();
	int ih = dImg.getHeight();
	int index = 0;
	for(int i=0; i<iw; i++) {
		for(int j=0; j<ih; j++) {
			index = (j*iw + i)*3;
			pixels[index + 0] = 0;
			pixels[index + 1] = 0;
			pixels[index + 2] = 0;
		}
	}
}

void vizDisplay::processData() {
	if(_run) {
		//printf("process\n");
		unsigned char r = 0;
		unsigned char g = 0;
		unsigned char b = 0;
		
		for(int i=0; i<channels; i++) {
			if(vizSetting[i*settingOptions + 0]==true) {
				//printf("CH%i: R ", (i+1));
				r = constrainC(r+int2char(newValues[i]), 0, 255);
			}
			if(vizSetting[i*settingOptions + 1]==true) {
				//printf("CH%i: G ", (i+1));
				g = constrainC(g+int2char(newValues[i]), 0, 255);
			}
			if(vizSetting[i*settingOptions + 2]==true) {
				//printf("CH%i: B ", (i+1));
				b = constrainC(b+int2char(newValues[i]), 0, 255);
			}
		}
		buffer[bufferCount*3 +0] = r;
		buffer[bufferCount*3 +1] = g;
		buffer[bufferCount*3 +2] = b;
		bufferCount++;
		printf("process data buffercount = %i : (%i|%i) %i %i %i \n", bufferCount, newValues[0], newValues[1], r, g, b);
		//setPixel(p,r,g,b);
		//p++;
		//if(p>iw*ih) p=0;
	}
}

void vizDisplay::processBuffer() {
	if(bufferCount>0) {
		pixels  = dImg.getPixels();
		int index = p;
		for(int i=0; i<bufferCount; i++) {
			index = p + i;
			if(index>iw*ih) index-=(iw*ih);
			pixels[index*3 + 0] = buffer[bufferCount*3 +0];
			pixels[index*3 + 1] = buffer[bufferCount*3 +1];
			pixels[index*3 + 2] = buffer[bufferCount*3 +2];
			printf("%i: %i %i %i \n", p, buffer[bufferCount*3 +0], buffer[bufferCount*3 +1], buffer[bufferCount*3 +2]);
			p++;
			if(p>iw*ih) p=0;
		}
		dImg.update();
		printf("--------------process buffer : %i \n", bufferCount);
		bufferCount = 0;
	}
}

void vizDisplay::fileNewData(int ch, int v) {
	if(_run) {
		newValues[ch] = v;
	}
}

unsigned char vizDisplay::constrainC(unsigned char v, unsigned char min, unsigned char max) {
	return (v < min) ? min : ( (v > max) ? max : v );
}

unsigned char vizDisplay::int2char(int v) {
	return constrainC( (unsigned char)((v/32767.0f)*255), 0, 255);
}

void vizDisplay::saveImg() {
	char fileN[100];
	sprintf(fileN, "viz_px_%i%02i%02i_%02i%02i%02i.png", ofGetYear(),ofGetMonth(),ofGetDay(),ofGetHours(),ofGetMinutes(),ofGetSeconds());
	dImg.saveImage(fileN);
	printf("save out img: %s \n", fileN);
}