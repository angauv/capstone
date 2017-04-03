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
	const char *path = "filetest.csv";
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

	if (!bufLine.empty())
		cout << endl << 1 << " " << bufLine[0] << " ";
	else{
		cout << "Buffer empty!" << endl;
		return -4;
	}

	int x = 2;

	for (int i = 1; i < bufLine.size() ; i++){
		if (bufLine[i] == 1 || bufLine[i] == 9){
			cout << bufLine[i] << endl;
			i++;

			if (bufLine[i] == 0)
				break;
			cout << x << " ";
			x++;
		}
		cout << bufLine[i] << " ";
	}

	cout << endl;
	pruPort.close();
	return 0;
}