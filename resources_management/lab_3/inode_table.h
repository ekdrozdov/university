#pragma once
#include <stdio.h>
#include <stdlib.h>

const int FNAME_LEN = 16;

typedef struct {
	char* filename;
	int inodeNumber;
	int counter;
} InodeRecord;

typedef struct {
	InodeRecord* records;
	int totalSize;
	int currentSize;
	void init(int size);
	void finit();
	int search(char* filename);
	void print();
	int add(char* filename, int inodeNumber);
} InodeTable;
