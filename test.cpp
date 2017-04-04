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
	int buf[8190] = {0};
	int len = 8199;
	const char *path = "testsample.csv";
	int readStatus = 1; // Memory read status flag
	vector<int> bufLine;

	if(!portOpen(path)){
		cout << "File stream path not valid" << endl;
		return -1;
	}

	ifstream pruPort(path);
	cout << "good: " << pruPort.good() << endl;
	cout << "eof: " << pruPort.eof() << endl;

	if(!pruPort.is_open()){
		cout << "File stream not open" << endl;
		return -2;
	}

	cout << "File stream is good" << endl;

	readStatus = memRead(pruPort,bufLine,len);
	cout << "Vector size: " << bufLine.size() << endl;

	cout << "good: " << pruPort.good() << endl;
	cout << "eof: " << pruPort.eof() << endl;

	if (readStatus == 0 || readStatus == -2)
		cout << "Buffer filled OK" << endl;
	else
		return -3;

	int x = 0;
	cout << x << " ";

	// Display sampled data to stdout
	for (int i = 0; i < bufLine.size() ; i++){
		if (i%9 == 0){
			cout << endl;

			x++;
			cout << x << " ";

			cout << hex << bufLine[i] << " ";
		}
		else
			cout << hex << bufLine[i] << " ";
	}

	cout << endl;
	pruPort.close();
	return 0;
}