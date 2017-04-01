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

using namespace std;

int main (void){
	int buf[8191] = {0};
	int len = 820;
	const char *path = "filetest.csv";
	int readStatus = 1; // Memory read status flag

	if(!portOpen(path)){
		cout << "File stream path not valid" << endl;
		return -1;
	}

	ifstream pruPort(path);

	if(!pruPort.is_open()){
		cout << "File stream not open" << endl;
		return -2;
	}

	cout << "File stream is good" << endl;

	//readStatus = memRead(pruPort,buf,len);

	string sampleLine;

	for (int i = 0; i < 2 ; i++){
		if(pruPort.is_open()){
			while (getline(pruPort,sampleLine)){
				istringstream iss(sampleLine);
				for (int y = 0; pruPort >> buf[y] ; y++){
					;
				}
			}
		}
		else
			readStatus = -1;
	}

	cout << "good: " << pruPort.good() << endl;
	cout << "eof: " << pruPort.eof() << endl;

	if (readStatus == 0 || readStatus == -2)
		cout << "Buffer filled OK" << endl;
	else
		return -3;

	cout << 1 << " ";
	int x = 2;

	for (int i = 0; i < 8190 ; i++){
		if (buf[i] == 0){
			cout << endl;
			cout << x << " ";
			x++;
			i++;
		}
		cout << buf[i] << " ";
	}

	cout << endl;
	pruPort.close();
	return 0;
}