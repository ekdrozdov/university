#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int fileTableRef;
} FileDescriptorsRecord;

typedef struct {
	FileDescriptorsRecord* records;
	int totalSize;
	int currentSize;
	void init(int size);
	void finit();
	//int search(char* filename);
	void print();
	int add(int fileTableRef);
} FileDescriptorsTable;
