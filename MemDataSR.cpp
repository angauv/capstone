/*
	Author:	Andy Ngauv
	File:	MemDataSR.cpp
	Date:	09/03/2017

	Memory Read and Data Sorting source file.
	Sorts data from a memory location into bins.
	And creates a .csv of data in day blocks.
*/

#include "MemDataSR.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

// constants and variables, put somewhere else after done making .cpp file
static size_t dataSize = 4; 		// size in bytes of each element to be read
static size_t bufSize = 2048; 		// number of elements with each of size dataSize
static int arraySize = 4096;
static int memFin = 0; 				// memory read flag
static int threshold = 512; 		// sample threshold

// opens a port and keeps it opens.
bool portOpen(const char *path){
	if(!chkFile(path)){
		cout << *path << " File does not exist" << endl;
		return false;
	}
	return true;
}

// Read file stream that contains samples and put it in provided buffer
int memRead(std::ifstream& ifs,std::vector<int> &buf,int len){
	if(!ifs.is_open()){
		cout << "File stream not connected" << endl;
		return -1;
	}

	cout << "good: " << ifs.good() << endl;
	cout << "eof: " << ifs.eof() << endl;

	string sampleLine;

	
	if(ifs.is_open()){
		int val;
		int i = 0;
		while (getline(ifs,sampleLine)){
			if(i > len)
				break;
			istringstream iss(sampleLine);
			while(iss >> val){
				buf.push_back(val);
				i++;
			}
		}
	}

	return 0;
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

	bin.day = ltm->tm_mday;
	bin.month = ltm->tm_mon + 1;
	bin.year = ltm->tm_year + 1900;

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

// functions checks for existing file and returns true if it exists
bool chkFile(const char *path){
	ifstream ifs(path); // open file for reading

	// Return true if the file exists otherwise false
	if (ifs.is_open()){
		ifs.close();
		return true;
	}
	else{
		ifs.close();
		return false;
	}
}

// Store bin data in a file/database. Returns true if file successfully loaded,
// false otherwise.
bool binFile(binData *bin){
	ofstream binFile(NULL);
	string strFile;		// filename string
	strFile.append(to_string(bin->day));
	strFile += "_" + to_string(bin->month); 
	strFile += "_" + to_string(bin->year) + ".csv";
	bin->filename = strFile.c_str();

	// Check if file exists, if not make new file and add new heading
	if(!chkFile(bin->filename)){
		binFile.open(bin->filename, ios::out);
		if(binFile.is_open()){		
			binFile << "Hour,Magnitude,#Events,Timestamp\n"<<endl;
			binFile.close();
		}
		else{
			cout << "File exists" << endl;
			return false;
		}
	}

	// Append bin data into .csv file
	binFile.open(bin->filename, ios::app);
	if(binFile.is_open()){
		binFile << bin->hour << "," << bin->magnitude << ",";
		binFile << bin->numEvent << "," << bin->tmStamp << endl;
		binFile.close();
	}
	else{
		cout << "No File to append to" << endl;
		return false;
	}
	return true;
}
