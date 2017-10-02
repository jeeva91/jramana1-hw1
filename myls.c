/*my ls program
 * Advanced Unix Programming
 * Midterm project
 * Author: Jeeva
 *Date: 10/01/2017
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
//#include <sys/types.h>
#include<dirent.h>
#include<unistd.h>
#include<sys/stat.h>



typedef struct{
  char* name;
  
}dirdetails;

int lexcomparator(const void*, const void*);

void printType(const struct stat);

int
main(int argc, char *argv[]){
  DIR *dp;
  struct dirent *dirp;
  char* dirname;
  char* filelist;
  struct stat *statlist, *statiter;
  int countstat;
  statlist = calloc(10, sizeof(struct stat));
  countstat = 0;
  statiter = statlist;
  if(argc ==1){
    if((dirname = getwd(dirname))==NULL){
      fprintf(stderr, "can't get the CWD %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
    if((dp = opendir(dirname))==NULL){
      fprintf(stderr, "can't get the CWD %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
    while((dirp = readdir(dp))!=NULL){
      struct stat sb;
      if (stat(dirp->d_name, &sb) == -1) {
	fprintf(stderr, "Can't stat %s: %s\n", dirp->d_name,
		strerror(errno));
	
	if (lstat(dirp->d_name, &sb) == -1) {
	  fprintf(stderr,"Can't stat %s: %s\n", dirp->d_name,
		  strerror(errno));
	  continue;
	}
      }
      *statiter = sb;
      statiter++;
      countstat++;
      
      
    }
  }

  closedir(dp);
  printf("the count of the stat is %d", countstat);
  return 0;
}

int
lexcomparator(const void* fir,
	      const void* sec){

}


/*  char *dirname, *dirn; */
/*   if((dirname = getwd(dirname))==NULL){ */
/*       fprintf(stderr, "can't get the CWD %s\n", strerror(errno)); */
/*       exit(EXIT_FAILURE); */
/*     } */
/*   printf("the directory is %s", dirname); */
/*   return 0; */
  
/* } */

void
printType(const struct stat sb) {
	if (S_ISREG(sb.st_mode))
		printf("regular file");
	else if (S_ISDIR(sb.st_mode))
		printf("directory");
	else if (S_ISCHR(sb.st_mode))
		printf("character special");
	else if (S_ISBLK(sb.st_mode))
		printf("block special");
	else if (S_ISFIFO(sb.st_mode))
		printf("FIFO");
	else if (S_ISLNK(sb.st_mode))
		printf("symbolic link");
	else if (S_ISSOCK(sb.st_mode))
		printf("socket");
	else
		printf("unknown");
}



int arraycomparator(const void* fir, const void* sec){
  int *first, *second;
  first = (int*) fir;
  second = (int*) sec;
  if(*first > *second) return 1;
  else if(*first < *second) return -1;
  else return 0;

}
