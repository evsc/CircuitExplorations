#pragma once

#include "guiButton.h"
#include "ofTrueTypeFont.h"


class picoComm
{
public:

	picoComm();

	ofEvent<int> sendBufferData1;
	ofEvent<int> sendBufferData2;
	ofEvent<int> setExpectedData;
	ofEvent<short**> storeDataArray;

	void update();
	void checkMouse(int x, int y);
	void click();

	int x;
	int y;

	void setup(int x, int y);
	void draw(ofTrueTypeFont * font);

	int sampleRate;

	//

	void openScope();
	void closeScope();

	void toggleScope();
	void toggleStream();

	void setStreamRate(int interval);
	void startStreaming();
	void stopStreaming();

	void showError();

	// handles

	short _open;
	short _streaming;
	short _getvalues;
	short _overrun;
	short _close;

	// counters
	unsigned int _sampleCount;
	unsigned int _frameCount;
	unsigned int _secondCount;
	unsigned int _frame;
	unsigned int _fr;	// frameRate
	unsigned int _inputSampleRate;

	// buttons
	vector<guiButton> buttons;

	static void * pObject;

	static void __stdcall callBackBitWise_Wrapper( short **overviewBuffers,
                                short overflow,
                                unsigned long triggeredAt,
                                short triggered,
                                short auto_stop,
                                unsigned long nValues);

	void __stdcall callBackBitWise( short **overviewBuffers,
                                short overflow,
                                unsigned long triggeredAt,
                                short triggered,
                                short auto_stop,
                                unsigned long nValues);


};
