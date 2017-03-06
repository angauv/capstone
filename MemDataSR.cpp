/*
	Memory Read and Data Sorting
	
	might want a class for this stuff
*/

#include "MemDataSR.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>
#include <ctime>

// constants and variables, put somewhere else after done making .cpp file
size_t dataSize = 4; 		// size in bytes of each element to be read
size_t bufSize = 2048; 		// number of elements with each of size dataSize
boolean memFin = false; 	// memory read flag
int threshold = 512; 		// sample threshold

struct ExpandTime{
	int et_sec;				// seconds (0-59)
	int et_min;				// minutes (0-59)
	int et_hour;			// hours (0-23)
};

struct binData{
	int hour;				// hour block
	char *tmStamp;			// timestamp of data being recorded
	int magnitude;			// largest magnitude of events
	int numEvent;			// number of exceeding threshold events
};

// Read data from shared memory and make a copy on the ARM side then sort it
// by magnitudes exceeding a threshold.
int *memReadSort(char path){
	FILE *shareMem = fopen(path, "r") ; // Connect to shared memory or open memory location
	int *sample;						// temporarily get samples from memory location
	int data[bufSize+1];				// store sample data into local buffer
	
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
	
	for (int i = 0; i < bufSize; i++){
		if (*sample++ > threshold)
			data[i] = *sample;
	}

	data[bufSize] = 0; 	// terminate value for array 
	
	fclose(shareMem);
	read = true;		// indicate that data has been read and sorted
	return &data;
}

// Sort the data for an hour block specified by a local time into that bin hour.
// bin will contain hour block, current timestamp, number of events, and magnitudes 
// in that order. Hour block is with respect to local time.
binData *sortBin(int *data){
	binData *bin;					// bin data
	size_t len = 10					// timestamp length

	time_t local = time(0);			// time in seconds since Jan 1, 1970
	ExpandTime et;					// format time structure
	tm *ltm = localtime(&time);		// local time
	bin.tmStamp = &ctime(local);	// timestamp with date and time

	et.et_hour = ltm->tm_hour + 1;
	et.et_min = ltm->tm_min + 1
	et.et_sec = ltm->tm_sec + 1

	bin.hour = et.et_hour;
	// snprintf(bin.tmStamp, len, "%02d:%02d:%02d", et.et_hour, et.et_min, et.et_sec);
	bin.magnitude = getMax(data);

	// Determine number of events with magnitudes greater than 0 that occurred
	for (int i = 0; *data++ != 0 ; i++){
		if (*++data == 0)
			bin.numEvent = i;
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