#include "file_descriptors.h"

void FileDescriptorsTable::init(int newSize) {
	totalSize = newSize;
	currentSize = 0;
	records = (FileDescriptorsRecord*)
		malloc(newSize * sizeof(FileDescriptorsRecord));
	for (int i = 0; i < newSize; ++i) {
		records[i].fileTableRef = -1;
	}
}

void FileDescriptorsTable::finit() {
	for (int i = 0; i < totalSize; ++i) {
		records[i].fileTableRef = -1;
	}
	free(records);
	currentSize = 0;
	totalSize = 0;
}

/*
int FileTable::search(char* filename) {
	int foundIndex = 0;
	while ((foundIndex < totalSize) && 
			(records[foundIndex].filename != filename)) {
		foundIndex++;
	}
	if (foundIndex == totalSize) {
		return -1;
	}
	return foundIndex;
}
*/

int FileDescriptorsTable::add(int fileTableRef) {
	if (currentSize > totalSize) {
		perror("FileTable: add: table is full");
		return -1;
	}

	records[currentSize].fileTableRef = fileTableRef;
	currentSize++;
	return currentSize - 1;
}

void FileDescriptorsTable::print() {
	printf("--- File descriptors table ---\n");
	printf("index\t");
	printf("FT\n");
	printf("\t");
	printf("ref\n");

	for (int i = 0; i < currentSize; ++i) {
		printf("[%i]\t", i);
		printf("%i\t", records[i].fileTableRef);
		printf("\n");
	}
}
