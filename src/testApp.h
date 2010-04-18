#pragma once

#include "ofMain.h"
#include "picoComm.h"
#include "dataStorage.h"
#include "ofEvents.h"
#include "Display.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);	

		ofTrueTypeFont font;

		picoComm pico;

		dataStorage storage;

		Display display;

		//vizDisplay viz;

		void setExpectedData(int &v);
		void storeDataArray(short**& overviewBuffers);
		void toggleDisplayRun(bool &v);
		int nValues;

};

