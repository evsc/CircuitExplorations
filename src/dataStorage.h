#pragma once

#define MAX_SIZE 100000

class dataStorage
{
public:
	dataStorage(void);
	~dataStorage(void);


	int storage[2*MAX_SIZE];
	int channels;

	int p;	// pointer position

	void setup();

	void inputDataToCh(int ch, int v);
	void inputData(int v1, int v2);

	void countUp();

};
