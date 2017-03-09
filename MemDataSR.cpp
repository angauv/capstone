/*
	Memory Read and Data Sorting
	
	might want a class for this stuff
*/

#include "MemDataSR.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

using namespace std;

// constants and variables, put somewhere else after done making .cpp file
static size_t dataSize = 4; 		// size in bytes of each element to be read
static size_t bufSize = 2048; 		// number of elements with each of size dataSize
static int arraySize = 2048;
static int memFin = 0; 				// memory read flag
static int threshold = 512; 		// sample threshold

// Read data from shared memory and make a copy to data buffer then sort it
// by magnitudes exceeding a threshold.
void *memReadSort(const char *path, int *data){
	FILE *shareMem = fopen(path, "r") ; // Connect to shared memory or open memory location
	int *sample;						// temporarily get samples from memory location
	
	if (shareMem == NULL){
		perror("Error opening file");
		exit(1);
	}
	else{
		if (fread(sample, dataSize, bufSize, shareMem) != bufSize){
			perror("Reading error, data buffer is not the specified size");
			exit(2);
		}
	}
	
	for (int i = 0; i < arraySize; i++){
		if (*sample++ > threshold)
			*data++ = *sample;
	}

	*data = 0; 	// terminate value for array 
	
	fclose(shareMem);
	memFin = 1;		// indicate that data has been read and sorted
}

// Sort the data for an hour block specified by a local time into that bin hour.
// bin will contain hour block, current timestamp, number of events, and magnitudes 
// in that order. Hour block is with respect to local time.
binData sortBin(int *data){
	binData bin;					// bin data

	time_t local = time(0);			// time in seconds since Jan 1, 1970
	tm *ltm = localtime(&local);		// local time
	bin.tmStamp = ctime(&local);	// timestamp with date and time

	bin.hour = ltm->tm_hour;
	bin.magnitude = getMax(data);

	// Determine number of events with magnitudes greater than 0 that occurred
	for (int i = 0; *data != 0 ; i++){
		bin.numEvent = i + 1;
		if (*data++ == 0 && i < 1)
			bin.numEvent = 0;
	}

	return bin;
}

// Find and return the largest number in the data array
int getMax(int *data){
	int max = *data;	// Largest number in the array

	// find largest number from data
	for (; *data++ != 0 ;){
		if (*data > max)
			max = *data;
	}
	return max;
}

// functions checks for existing file and if non exist, creates file
bool chkFile(const char *path){
	ifstream ifs;
	
	ifs.open(path, ios::in);

	if (ifs.good()){
		ifs.close();
		cout << "File exist!" << endl;
		return true;
	}
	else{
		ifs.close();
		cout << "File does not exist!" << endl;
		return false;
	}
}

// Store bin data in a file/database
bool binFile(binData *bin, const char *path){
	fstream binFile(NULL);
	string strFile;
	strFile.append(to_string(bin->day));
	strFile += "_" + to_string(bin->month); 
	strFile += "_" + to_string(bin->year) + ".csv";

	if(!chkFile(strFile.c_str())){
		binFile.open(strFile.c_str(),ios::in | ios::out | ios::trunc);
		if(binFile.is_open()){		
			binFile << "Hour,Magnitude,#Events,Timestamp\n"<<endl;
			binFile.close();
		}
		else{
			cout << "File not created" << endl;
			return false;
		}
	}

	binFile.open(strFile.c_str(), ios::app);
	if(binFile.is_open()){
		binFile << bin->hour;
		binFile << "," << bin->magnitude;
		binFile << "," << bin->numEvent;
		binFile << "," << bin->tmStamp << endl;
		binFile.close();
	}
	else{
		cout << "No File to append to" << endl;
		return false;
	}
	return true;
}