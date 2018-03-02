/*
 * Resource management Variant 5
 * main.cpp
 * Purpose: list names of directories that contained
 * in a current directory and also contain a subdirectories 
 * (exclude '.' and '..' ) by themselves.
 *
 * @author Edward Drozdov
 * @author Mozhaev Alexandr
 * @version 1.0 02/03/18
 */

#include <sys/types.h> 
#include <sys/stat.h> 
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <cstring>


int isDirectory(dirent* dirEntry) {
	if ((strcmp(dirEntry->d_name, ".") == 0) || 
			(strcmp(dirEntry->d_name, "..") == 0)) {
		return 0;
	}
	
	struct stat entryStat;
	if (stat(dirEntry->d_name, &entryStat) != -1) {
		if (S_ISDIR(entryStat.st_mode)) {
			return 1;
		}
		return 0;
	}

	perror("isDirecotry: stat");
	printf("info %s\n", dirEntry->d_name);
	return 0;
}

int isContainSubdir(dirent* dirEntry) {
	if (isDirectory(dirEntry) == 0) {
		return 0;
	}
	DIR* dirDesc = opendir(dirEntry->d_name);
	chdir(dirEntry->d_name);
	dirEntry = readdir(dirDesc);
	while (dirEntry) {
		if (isDirectory(dirEntry)) {
			chdir("..");
			return 1;
		}
		dirEntry = readdir(dirDesc);
	}

	chdir("..");
	return 0;
}

void printUsage() {
	printf("USAGE:\nlsd directory\n");
}

int main(int argc, char** argv) {
	char* rootDir;
	if (argv[1] == NULL) {
		rootDir = ".";
	}
	else {
		rootDir = argv[1];
	}

	DIR* dirDesc = opendir(rootDir);
	dirent* dirEntry;
	dirEntry = readdir(dirDesc);

	while (dirEntry) {
		if (isContainSubdir(dirEntry)) {
			printf("%s\n", dirEntry->d_name);
		}
		dirEntry = readdir(dirDesc);
	}

	return 0;
}

//struct stat { 
//	dev_t st_dev; /* device file */ 
//	ino_t st_ino; /* file serial inode */ 
//	ushort st_mode; /* file mode */ 
//	short st_nlink; /* number of links */ 
//	ushort st_uid; /* user ID */ 
//	ushort st_gid; /* group ID */ 
//	dev_t st_rdev; /* device ident */ 
//	off_t st_size; /* size of file */ 
//	time_t st_atime; /* last access time */ 
//	time_t st_mtime; /* last modify time */ 
//	time_t st_ctime; /* last status change */ 
//};

//struct dirent { 
//	ino_t d_ino; /* номер индексного дескриптора */ 
//	char d_name[DIRSIZ]; /* имя файла */ 
//}

