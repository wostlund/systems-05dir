#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>


typedef struct stat sp;

int printDir(DIR *dirStream) {
  int acc = 0;
  struct dirent *thisFile;
  char directories[100];
  char file[100];
  char name[256];
  thisFile = readdir(dirStream);
  while(thisFile)
    {
      strcpy(name, thisFile->d_name);
      if(thisFile->d_type & DT_DIR){
	strcat(name, "\n");
	strcat(directories, "  ");
	strcat(directories, name);
      } else if(thisFile->d_type & DT_REG){
	sp fileStats;
	stat(name, &fileStats);
	acc += fileStats.st_size;
	strcat(name, "\n");
	strcat(file, "  ");
	strcat(file, name);
      }
      thisFile = readdir(dirStream);
    }
  free(thisFile);
  closedir(dirStream);
  printf("\nDirectories:\n%s\nFiles:\n%s\n", directories, file);
  return acc;
}


int main () {
  DIR *dirStream = opendir(".");
  int normalSize = printDir(dirStream);
  printf("Size of all files combined: %d bytes\n\n", normalSize);
}
