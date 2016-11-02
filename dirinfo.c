#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <dirent.h>

typedef struct stat* sp;

/*
int printDir(DIR* dirStream)
{
	int acc = 0;
	while(dirStream)
	{
		DIR* status = opendir(dirStream);
		if(status) printDir(opendir(dirStream));
		else
		{
			struct dirent* thisFile = readdir(dirStream);
			printf("%s\n", thisFile->d_name);
			sp fileStats = (sp) malloc(sizeof(sp));
			stat(thisFile->d_name, fileStats);
			acc += fileStats->st_size;
		}
	}
	return acc;
}
*/

int printDir(DIR* dirStream)
{
	int acc = 0;
	struct dirent* thisFile = readdir(dirStream);
	while(thisFile)
	{
		printf("%s\n", thisFile->d_name);
		if(thisFile->d_type == 4) printDir(opendir(thisFile->d_name)); //look at this

		else
		{
			sp fileStats = (sp) malloc(sizeof(sp));
			stat(thisFile->d_name, fileStats);
			acc += fileStats->st_size;
			free(fileStats);
		}
		thisFile = readdir(dirStream);
	}
	closedir(dirStream);
	return acc;
}


int main () {

	DIR* dirStream = opendir("../systems-05dir");
	int normalSize = printDir(dirStream);
	printf("size of files: %d\n", normalSize);
}
