#pragma once

#include "ofTrueTypeFont.h"
#include "guiButton.h"
//#include "ofEvents.h"

#define MAX_LENGTH	1024

class channelDisplay
{
public:
	channelDisplay(void);
	~channelDisplay(void);

	//ofEvent<bool> filledArray;

	void draw(ofTrueTypeFont * font);
	void setup(float x, float y, char* n);
	void update();

	float x;
	float y;

	// array placement and measurements
	float ax;
	float ay;
	float aw;
	float ah;
	// array values
	bool DC;	// true = DC, false = AC
	float voltage;	// max voltage level
	float data[MAX_LENGTH];
	int len;	// length of array
	int p;		// pointer of new data position 

	void setLen(int l);
	void fileNewData(int v);
	void setSize(float w, float h);
	float getMemory(int step);
	void clear();
	void drawArray();

	void checkMouse(int x, int y);
	void click();

	bool _run;
	bool _show;

	char* name;

	// buttons
	vector<guiButton> buttons;

};
