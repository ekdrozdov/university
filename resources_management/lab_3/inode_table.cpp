#include "inode_table.h"

void InodeTable::init(int newSize) {
	totalSize = newSize;
	currentSize = 0;
	records = (InodeRecord*)malloc(newSize * sizeof(InodeRecord));
	for (int i = 0; i < newSize; ++i) {
		records[i].filename = (char*)malloc(FNAME_LEN * sizeof(char));
		records[i].filename[0] = '\0';
		records[i].inodeNumber = 0;
		records[i].counter = 0;
	}
}

void InodeTable::finit() {
	for (int i = 0; i < totalSize; ++i) {
		records[i].filename[0] = '\0';
		free(records[i].filename);
		records[i].inodeNumber = 0;
		records[i].counter = 0;
	}
	free(records);
	currentSize = 0;
	totalSize = 0;
}

int InodeTable::search(char* filename) {
	int foundIndex = 0;
	char* temp = records[0].filename;

	while ((foundIndex < totalSize) && 
			(strcmp(records[foundIndex].filename, filename)) == 0) {
		++foundIndex;
	}
	if (foundIndex < totalSize) {
		return foundIndex;
	}

	return -1;
}

int InodeTable::add(char* filename, int inodeNumber) {
	if (currentSize > totalSize) {
		perror("InodeTable: add: table is full");
		return -1;
	}

	int index = search(filename);
	if (index != -1) {
		printf("byehi\n");
		printf("byehi\n");
		printf("byehi\n");
		printf("byehi\n");
		records[index].counter++;
		return index;
	}
	else {
		strcpy(records[currentSize].filename, filename);
		printf("hi\n");
		printf("hi\n");
		printf("hi\n");
		printf("hi\n");
		//records[currentSize].filename = filename;
		records[currentSize].inodeNumber = inodeNumber;
		records[currentSize].counter = 1;
		currentSize++;
		return currentSize - 1;
	}
}

void InodeTable::print() {
	printf("--- Inode table ---\n");
	printf("index\t");
	printf("file\t");
	printf("inode\t");
	printf("counter\n");
	printf("\t");
	printf("name\t");
	printf("number\n");
	for (int i = 0; i < currentSize; ++i) {
		printf("[%i]\t", i);
		printf("%s\t", records[i].filename);
		printf("%i\t", records[i].inodeNumber);
		printf("%i\t", records[i].counter);
		printf("\n");
	}
}
