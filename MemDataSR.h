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
#include <fstream>
#include <ctime>
#include <string>
#include <sstream>
#include <vector>

typedef struct{
	int hour;				// hour block
	int day;				// day wrt to localtime
	int month;				// month wrt to localtime
	int year;				// year wrt to localtime
	char *tmStamp;			// timestamp of data being recorded
	int magnitude;			// largest magnitude of events
	int numEvent;			// number of exceeding threshold events
	const char *filename;	// .csv filename
} binData;

typedef struct{
	std::vector<int> buf1;
	std::vector<int> buf2;
} Samples;

// Read file stream that contains samples and put it in provided buffer
// assumes file data was dumped by hexdump -d -v command
int memRead(std::ifstream& ifs,std::vector<int> &buf,int len);

// Sort sampled data into separate buffers of their respective channel
// assumes the data was originally sorted by default hexdump -d -v command
bool sortSample(Samples *data, std::vector<int> &buf);

// Sort the data for an hour block specified by a local time into that bin hour.
// bin will contain hour block, current timestamp, number of events, and magnitudes 
// in that order. Hour block is with respect to local time.
binData sortBin(int *data);

// Find and return the largest number in the data array
int getMax(int *data);

// Sort bin data into a file and return true if file created, false otherwise;
bool binFile(binData *bin);

// functions checks for existing file
bool chkFile(const char *path);

#endif