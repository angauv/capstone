/*
	Memory Read and Data Sorting
	
	might want a class for this stuff
*/

#include "MemDataSR.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>

// constants and variables, put somewhere else after done making .cpp file
size_t dataSize = 4; // size in bytes of each element to be read
size_t bufSize = 2048; // number of elements with each of size dataSize
boolean read = false; // read flag
int threshold = 512; // sample threshold
int recordSize = 

// Move data from shared memory to ARM side
void memMove(void){
	
	
}

int *memReadSort(char path){
	FILE *shareMem = fopen(path, "r") ;
	int *sample;
	static int data[bufSize];
	
	if (shareMem == NULL){
		perror("Error opening file");
		exit(1);
	}
	else{
		if (fread(sample, dataSize, bufSize, shareMem) != bufSize){
			perror("Reading error");
			exit(2);
		}
	}
	
	for (int i = 0; i < bufSize; i++){
		if (*sample++ > threshold)
			data[i] = *sample;
	}
	
	fclose(shareMem);
	read = true;
	return &data;
}

int *sortBin(int *data){
	int numEvent; // number of PD events
	int timeRange = 24; // 24 hours
	int magRange; // magnitude range
	
	return &bin
}