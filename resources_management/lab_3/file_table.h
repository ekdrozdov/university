#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	// Mode states:
	// -1 -- not define;
	// 0 -- read;
	// 1 -- write;
	// 2 -- append.
	int mode;
	int offset;
	int counter;
	int inodeTableRef;
} FileTableRecord;

typedef struct {
	FileTableRecord* records;
	int totalSize;
	int currentSize;
	void init(int size);
	void finit();
	//int search(char* filename);
	void print();
	int add(int inodeTableRef, int mode);
} FileTable;
