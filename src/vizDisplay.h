#pragma once

#include "ofTrueTypeFont.h"
#include "guiButton.h"
#include "ofImage.h"

class vizDisplay
{
public:
	vizDisplay(void);
	~vizDisplay(void);

	void draw(ofTrueTypeFont * font);
	void setup(float x, float y);
	void update();

	float x;
	float y;

	void checkMouse(int x, int y);
	void click();

	bool _run;
	bool _show;

	int vizMode;

	void saveImg();
	void randomImg();
	void clearImg();
	void setPixel(int index, unsigned char r, unsigned char g, unsigned char b);

	// buttons
	vector<guiButton> buttons;

	ofImage dImg;	// display image
	unsigned char * pixels;
	int iw;			// image dimensions
	int ih;
	int dw;			// display dimensions
	int dh;	
	unsigned int p;	// pointer for pixel manipulation

	vector<guiButton> chSettings;

	int settingOptions;
	int channels;
	bool vizSetting[2*10];
	int newValues[10];

	void clearData();
	void fileNewData(int ch, int v);
	void processData();
	void processBuffer();

	unsigned char buffer[1000*3];
	unsigned int bufferCount;

	unsigned char constrainC(unsigned char v, unsigned char min, unsigned char max);

	unsigned char int2char(int v);

};
