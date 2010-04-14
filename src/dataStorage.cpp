#include "dataStorage.h"
#include "ofMain.h"

dataStorage::dataStorage(void)
{
}

dataStorage::~dataStorage(void)
{
}

void dataStorage::setup() {
	channels = 2;
	p = 0;
	//storage = new int[channels*MAX_SIZE];
}

void dataStorage::inputDataToCh(int ch, int v) {
	storage[p*2 + ch] = v;
	countUp();
}

void dataStorage::inputData(int v1, int v2) {
	storage[p*2] = v1;
	storage[p*2 + 1] = v2;
	countUp();
}

void dataStorage::countUp() {
	p++;
	if(p>=MAX_SIZE) {
		printf("full! : %i \n",MAX_SIZE);
		p=0;
	}
}