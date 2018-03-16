/*
 * Resource management Variant 5
 * main.cpp
 *
 * Purpose: OS UNIX file handling (open/close, read/write)
 * behaivor demonstration.
 *
 * @author Edward Drozdov
 * @author Mozhaev Alexandr
 * @version 1.0 02/03/18
 */

/* 
 * Program scenario example:
 * 	implicit stdin opening
 * 	implicit stdout opening
 * 	implicit stderr opening
 * 	first user file opening
 * 	second user file opening
 * 	write 20 bytes in first file
 * 	read 15 bytes from second file
 * 	write 45 bytes in first file
 */

#include <sys/types.h> 
#include <sys/stat.h> 
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <cstring>
#include "inode_table.h"
#include "file_descriptors.h"
#include "file_table.h"

int fileOpen(char* filename, int mode);
void fileWrite(int FDTRef, int bytes);
void fileRead(int FDTRef, int bytes);
void printAllTables();

InodeTable inodeTable;
FileTable fileTable;
FileDescriptorsTable fileDescTable;

int main(int argc, char** argv) {
	inodeTable.init(10);
	fileTable.init(10);
	fileDescTable.init(10);

	fileOpen("stdin", 0);
	printAllTables();
	fileOpen("stdout", 1);
	printAllTables();
	fileOpen("stderr", 1);
	printAllTables();
	int file1 = fileOpen("file1", 1);
	printAllTables();
	int file2 = fileOpen("file2", 2);
	printAllTables();

	fileWrite(file1, 20);
	printAllTables();
	fileRead(file2, 15);
	printAllTables();
	fileWrite(file1, 45);
	printAllTables();

	inodeTable.finit();
	fileTable.finit();
	fileDescTable.finit();

	return 0;
}

int getInode(char* filename) {
	int inode = 0;
	for (char* c = filename; *c != '\0'; ++c) {
		inode += (int)(*c);
	}
	return inode;
}

int fileOpen(char* filename, int mode) {
	int inode = getInode(filename);
	int inodeTableRef = inodeTable.add(filename, inode);
	int fileTableRef = fileTable.add(inodeTableRef, mode);
	int fileDescTableRef = fileDescTable.add(fileTableRef);

	return fileDescTableRef; 
}

void fileWrite(int FDTRef, int bytes) {
	int FTRef = fileDescTable.records[FDTRef].fileTableRef;
	fileTable.records[FTRef].offset += bytes;
}

void fileRead(int FDTRef, int bytes) {
	int FTRef = fileDescTable.records[FDTRef].fileTableRef;
	fileTable.records[FTRef].offset += bytes;
}


void printAllTables() {
	inodeTable.print();
	fileTable.print();
	fileDescTable.print();
	printf("\n");
}
