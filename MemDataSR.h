/*
	Author: Andy Ngauv
	File: 	MemDataSR.h
	Date:	09/03/2017

	Header file to implement functions to access memory and sort data.
	And to store the sorted data into a .csv file.
*/

#ifndef MEMDATASR_H_
#define MEMDATASR_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <string>

typedef struct{
	int hour;				// hour block
	int day;				// day wrt to localtime
	int month;				// month wrt to localtime
	int year;				// year wrt to localtime
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

// Sort bin data into a file and return true if file created, false otherwise;
bool binFile(binData *bin, const char *path);

// functions checks for existing file
bool chkFile(const char *path);

#endif