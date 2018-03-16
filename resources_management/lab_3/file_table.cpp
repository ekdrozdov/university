#include "file_table.h"

void FileTable::init(int newSize) {
	totalSize = newSize;
	currentSize = 0;
	records = (FileTableRecord*)malloc(newSize * sizeof(FileTableRecord));
	for (int i = 0; i < newSize; ++i) {
		records[i].mode = -1;
		records[i].offset = -1;
		records[i].counter = 0;
		records[i].inodeTableRef = -1;
	}
}

void FileTable::finit() {
	for (int i = 0; i < totalSize; ++i) {
		records[i].mode = -1;
		records[i].offset = -1;
		records[i].counter = 0;
		records[i].inodeTableRef = -1;
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

int FileTable::add(int inodeTableRef, int mode) {
	if (currentSize > totalSize) {
		perror("FileTable: add: table is full");
		return -1;
	}

	records[currentSize].mode = mode;
	records[currentSize].offset = 0;
	records[currentSize].counter = 1;
	records[currentSize].inodeTableRef = inodeTableRef; 
	currentSize++;
	return currentSize - 1;
}

void FileTable::print() {
	printf("--- File table ---\n");
	printf("index\t");
	printf("IT\t");
	printf("mode\t");
	printf("offset\t");
	printf("counter\n");
	printf("\t");
	printf("ref\t");
	printf("(bytes)\n");

	for (int i = 0; i < currentSize; ++i) {
		printf("[%i]\t", i);
		printf("%i\t", records[i].inodeTableRef);
		printf("%i\t", records[i].mode);
		printf("%i\t", records[i].offset);
		printf("%i\t", records[i].counter);
		printf("\n");
	}
}
