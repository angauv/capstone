/*
	Source file to test code functionality.
*/

#include "MemDataSR.h"
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main (void){
	int len = 1024;
	const char *path = "testsample.csv";
	const char *port = "/dev/beaglelogic";
	
	int readStatus = 1; // Memory read status flag
	vector<int> bufLine;
	char buf[len] = {0};
	Samples samples;

	// Check port path
	//if (!chkFile(port)){
	//	cout << "File stream port not valid" << endl;
	//	return -1;
	//}

	// check file path
	if(!chkFile(port)){
		cout << "File stream path not valid" << endl;
		return -2;
	}

	ifstream pruPort(port, ios::binary); // open file path

	// check if the path was open again
	if(!pruPort.is_open()){
		cout << "File stream not open" << endl;
		return -3;
	}

	cout << "File stream is good" << endl;

	readStatus = memRead(pruPort,bufLine,len, buf);

	// check the state of the file reading process
	if (readStatus == 0)
		cout << "Buffer filled OK" << endl;
	else{
		cout << "Buffer failed to fill properly" << endl;
		return -4;
	}

	int x = 0;

	// Display sampled data to stdout
	for (int i = 0; i < bufLine.size() ; i++){
		if (i%9 == 0){
			cout << endl;
			x++;
			cout << dec << x << " ";
			cout <<  bufLine[i] << " ";
		}
		else
			cout <<  bufLine[i] << " ";
	}

	cout << endl;

	// sort samples from their respective channels into separte buffers
	if(sortSample(&samples,bufLine)){
		int y = 0;
		cout << "buf1 size: " << dec << samples.buf1.size() << endl;
		for (int i = 0; i < samples.buf1.size() ; i++){
			y++;
			cout << dec << y << " ";
			cout << samples.buf1[i] << " " << endl;
		}

		cout << endl;
		cout << "buf2 size: " << dec << samples.buf2.size() << endl;

		y = 0;
		for (int i = 0; i < samples.buf2.size() ; i++){
			y++;
			cout << dec << y << " ";
			cout << samples.buf2[i] << " " << endl;
		}
	}

	cout << endl;
	pruPort.close();
	return 0;
}
