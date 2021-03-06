/*
	Source file to test code functionality.
*/

#include "MemDataSR.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

using namespace std;

int main (void){
	int buf[2049];
	binData bin;

	for(int i = 0; i < 2048 ; i++)
		i < 2048 ? buf[i] = i+1 : buf[i] = 0;

	buf[2048] = 0;

	bin = sortBin(buf);
	cout << "Hour block: " << bin.hour << endl;
	cout << "Timestamp: " << bin.tmStamp << endl;
	cout << "Largest Magnitude: " << bin.magnitude << endl;
	cout << "Number of Events: " << bin.numEvent << endl;

	if (!binFile(&bin)){
		cout << bin.filename << "file does not exist" << endl;
	}
	else{
		cout << "Data written to " << bin.filename << endl;
	}

	return 0;
}