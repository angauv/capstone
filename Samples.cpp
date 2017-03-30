/*
	Author:	Andy Ngauv
	File:	MemDataSR.cpp
	Date:	29/03/2017

	Connect to continuous data stream and pull samples from that
	stream and store in buffer.
*/

#include "Samples.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

using namespace std;

ifstream sampleStreamConnect(char* port){
	istream ifs(port);

	// Return connected stream otherwise NULL if not connected
	if (ifs.good()){
		cout << port << " is now connected." << endl;
		return ifs;
	}
	else{
		cout << *port << " is not connected. Is the stream path correct?" << endl;
		ifs.close();
		return NULL;
	}
}

void readSamples(int *buf, ifstream ifs){
	
}