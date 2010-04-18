#include "ofMain.h"
#include "picoComm.h"
#include "ps2000.h"
#include "resource.h"
#include "stdio.h"


#define BUFFER_SIZE 30000
#define VOLTAGE PS2000_5V
#define VOLTAGE_NUMBER 5
#define CHANNELS 2



void * picoComm::pObject;

/*
char picoOutput2Char(int v) {
	if(v < -32767) {
		printf("buffer overrun in fast streaming mode \n");
		return 'x';
	} else {
		float fv = 0;
		fv = (float) constrainF(v / 32767.0f,0,1);
		char cv = 0;
		cv = (char) (fv*127);
		return cv;
	}
}
*/

picoComm::picoComm() {
	
}

void picoComm::setup(int x, int y) {
	
	pObject = this;

	this->x = x;
	this->y = y;

	sampleRate = 500000;

	_fr = 0;
	_secondCount = 0;
	_inputSampleRate = 0;

	_open = 0;
	_streaming = 0;
	_overrun = 0;

	//buttons
	guiButton* b_open = new guiButton();
	b_open->setup(x,y+10,80,17,"open scope", "close scope");
	buttons.push_back(*b_open);

	guiButton* b_stream = new guiButton();
	b_stream->setup(x+85,y+10,90,17,"start stream", "stop stream");
	b_stream->_on = false;
	buttons.push_back(*b_stream);
}

void picoComm::update() {

	if(_streaming) {
		_getvalues = ps2000_get_streaming_last_values(_open, callBackBitWise_Wrapper); 
      
        short _testoverrun = ps2000_overview_buffer_status(_open,&_overrun);
        if(_overrun!=0) printf("overrun : %i  ... successful: %i \n", _overrun, _testoverrun);
	}


	for(int i=0; i<buttons.size(); i++) {
		buttons[i].update();
	}

	_frameCount = _sampleCount;
	_secondCount += _frameCount;
	_sampleCount = _frameCount = 0;
	_frame++;
	_fr = ofGetFrameRate();
	if(_frame >= _fr) {
		_frame = 0;
		_inputSampleRate = _secondCount;
		_secondCount = 0;
	}

	
}

void __stdcall picoComm::callBackBitWise( short **overviewBuffers,
                                short overflow,
                                unsigned long triggeredAt,
                                short triggered,
                                short auto_stop,
								unsigned long nValues) {
	    //printf("callback : %i values, %i overflow, %i triggeredAt, %i triggered, %i autostop\n", nValues, overflow, triggeredAt, triggered, auto_stop);
	
/*
	int v1, v2;
	if(nValues > 0) {
		for(int i=0; i<nValues; i++) {
			for(int c=0; c<CHANNELS; c++) {
				int v = (*(*overviewBuffers + BUFFER_SIZE*(c*2) +i));
				if(c==0) {
					v1 = v;
				} else if(c==1) {
					v2 = v;
				}
			}
			ofNotifyEvent(sendBufferData1, v1, this );
			ofNotifyEvent(sendBufferData2, v2, this );
			//printf(".\t%i.\t%i", v1,v2);
		}

	}
	printf("\n");
	*/
	int v = (int) nValues;
	ofNotifyEvent(setExpectedData, v, this);
	ofNotifyEvent(storeDataArray, overviewBuffers, this);
	
	_sampleCount += nValues;
	//printf("callback : %i values -> %i / %i\n", nValues,_sampleCount,_secondCount);
}

void __stdcall picoComm::callBackBitWise_Wrapper( short **overviewBuffers,
                                short overflow,
                                unsigned long triggeredAt,
                                short triggered,
                                short auto_stop,
								unsigned long nValues) {
	//printf("callback_wrapper : %i values\n", nValues);
	picoComm *pPicoCommClass = (picoComm*)pObject;
	pPicoCommClass->callBackBitWise(overviewBuffers,overflow,triggeredAt,triggered,auto_stop,nValues);
}


void picoComm::checkMouse(int x, int y) {
	for(int i=0; i<buttons.size(); i++) {
		buttons[i].checkMouse(x,y);
	}
}

void picoComm::click() {
	for(int i=0; i<buttons.size(); i++) {
		if(buttons[i]._over) {
			switch(i) {
				case 0:	// open/close scope
					buttons[i].click();
					toggleScope();
					break;
				case 1:	// start/stop stream
					buttons[i].click();
					toggleStream();
			}
		}
	}
}

void picoComm::draw(ofTrueTypeFont * font) {
	ofPushMatrix();
	ofTranslate(x,y,0);

	font->drawString("PICOSCOPE", 0,0);

	char prstr[100]; 

	sprintf(prstr, "/ %03i fps", _fr);
	font->drawString(prstr, 80,0);
	sprintf(prstr, "/ %i Hz",_inputSampleRate);
	font->drawString(prstr, 140,0);

	ofPopMatrix();

	for(int i=0; i<buttons.size(); i++) {
		buttons[i].draw(font);
	}
}

void picoComm::openScope() {
	_open = ps2000_open_unit();
	printf("open: %i \n", _open);

	if(_open > 0) {
		// select channel ranges and AC/DC coupling
		short _channel = ps2000_set_channel(_open, 0, true, true, VOLTAGE);
		
		if(CHANNELS>1) {
			_channel = ps2000_set_channel(_open, 1, true, true, VOLTAGE);
		}
		printf("set channels: %i \n", _channel);

		char str[80];
        printf("\n");
        short _info = ps2000_get_unit_info(_open, str, sizeof(str), 0);
        printf("info: dll = %s \n", str);
        _info = ps2000_get_unit_info(_open, str, sizeof(str), 1);
        printf("info: usb = %s \n", str);
        _info = ps2000_get_unit_info(_open, str, sizeof(str), 2);
        printf("info: hardware version = %s \n", str);
        _info = ps2000_get_unit_info(_open, str, sizeof(str), 3);
        printf("info: picoScope variant = %s \n", str);
        _info = ps2000_get_unit_info(_open, str, sizeof(str), 4);
        printf("info: batch+serial = %s \n",str);
        _info = ps2000_get_unit_info(_open, str, sizeof(str), 5);
        printf("info: calibration = %s \n", str);

		showError();
        printf("\n");

		// set the trigger
        try {
            short _trigger = ps2000_set_trigger(_open, 5,0,0,0,0 );
            printf("set trigger: %i \n",_trigger);
        } catch (int n) {
            printf("no trigger \n");
        }

	}
}

void picoComm::closeScope() {
	_close = ps2000_close_unit(_open);
	printf("close: %i \n", _close);
	_open = 0;
}

void picoComm::toggleScope() {
	if(_open > 0) {
		// turn streaming possiblity off
		buttons[1]._on = false;
		closeScope();
	} else {
		// turn streaming possiblity on
		buttons[1]._on = true;
		openScope();
	}
}

void picoComm::toggleStream() {
	if(_streaming) {
		stopStreaming();
	} else {
		startStreaming();
	}
}

void picoComm::setStreamRate(int interval) {
	sampleRate = interval;
}

void picoComm::startStreaming() {
	if(_open > 0) {
		try {
            // handle, sample_interval, time_units, max_samples, auto_stop, samples_per_aggregate, buffer_size
            _streaming = ps2000_run_streaming_ns(_open,sampleRate,PS2000_NS,100000,0,1,BUFFER_SIZE); //(_open,v,PS2000_US,100000,0,1,100000);
            printf("start streaming: %i every %i ns\n",_streaming,sampleRate);

			_frameCount = 0;
			_secondCount = 0;
			_sampleCount = 0;
			_frame = 0;

			_getvalues = ps2000_get_streaming_last_values(_open, picoComm::callBackBitWise_Wrapper); //ps2000FastBitwise

		} catch (int n) {
            printf("no run \n");
        }

	}
}

void picoComm::stopStreaming() {
    if(_streaming) {
        short _stop = ps2000_stop(_open);
        printf("stop streaming: %i \n", _stop);
        _streaming = 0;
		_inputSampleRate = 0;
    }
}

void picoComm::showError() {
	char str[80];
    short _info = ps2000_get_unit_info(_open, str, sizeof(str), 6);
    printf("info: error codes = %s \n", str);
}