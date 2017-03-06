/*
	Header file to implement functions to access memory and sort data.
*/

#ifndef MEMDATASR_H_
#define MEMDATASR_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>

typedef struct{
	int et_sec;				// seconds (0-59)
	int et_min;				// minutes (0-59)
	int et_hour;			// hours (0-23)
} ExpandTime;

typedef struct{
	int hour;				// hour block
	char *tmStamp;			// timestamp of data being recorded
	int magnitude;			// largest magnitude of events
	int numEvent;			// number of exceeding threshold events
} binData;

// Read data from shared memory and make a copy on the ARM side then sort it
// by magnitudes exceeding a threshold.
void *memReadSort(const char path);

// Sort the data for an hour block specified by a local time into that bin hour.
// bin will contain hour block, current timestamp, number of events, and magnitudes 
// in that order. Hour block is with respect to local time.
binData sortBin(int *data);

// Find and return the largest number in the data array
int getMax(int *data);

#endif