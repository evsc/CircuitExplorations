#include "testApp.h"

#define BUFFER_SIZE 30000

//--------------------------------------------------------------
void testApp::setup(){

	font.loadFont("verdana.ttf", 8);

	pico.setup(50,50);
	display.setup(50,150);
	storage.setup();
	

	ofAddListener(pico.setExpectedData, this, &testApp::setExpectedData);
	ofAddListener(pico.storeDataArray, this, &testApp::storeDataArray);
}

//--------------------------------------------------------------
void testApp::update(){
	pico.checkMouse(mouseX,mouseY);
	pico.update();
}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(255,255,255);

	ofSetColor(0,0,0);
    font.drawString("CIRCUIT EXPLORATIONS", 10,20);

	pico.draw(&font);
	display.draw(&font);
}

void testApp::setExpectedData(int &v) {
	nValues = v;
}

void testApp::storeDataArray(short**& overviewBuffers) {
	//printf("%i values: \n", nValues);
	int v1;
	int v2;
	for(int i=0; i<nValues; i++) {
		v1 = (*(*overviewBuffers+i));
		v2 = (*(*overviewBuffers+BUFFER_SIZE*2+i));
		storage.inputData(v1,v2);
		//printf("%i\t", v1);
		//printf("%i\t", v2);
	}
	//printf("\n");
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	switch(key) {
		case ' ':	pico.toggleScope();
			break;
		case 's':	pico.toggleStream();
			break;
	}
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	pico.click();
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

