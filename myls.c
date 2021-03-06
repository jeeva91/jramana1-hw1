/*my ls program
 * Advanced Unix Programming
 * Midterm project
 * Author: Jeeva
 *Date: 09/28/2017
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
//#include <sys/types.h>
#include<dirent.h>
#include<unistd.h>
#include<sys/stat.h>

#define FILESIZE 255

typedef struct{
  char* name;
  
}dirdetails;

int lexcomparator(const void*, const void*);

void printType(const struct stat);

int
main(int argc, char *argv[]){
  DIR *dp;
  struct dirent *dirp, *direntlist, *cdirent;
  char *dirname;
  int dirnsize,dirnite;
  dirnsize = 10;
  direntlist = calloc(dirnsize, sizeof(struct dirent));
  cdirent = direntlist;
  dirnite = 0;
  dirname= NULL;
  if(argc ==1){
    if((dirname = getcwd(dirname, 0))==NULL){
      fprintf(stderr, "can't get the CWD %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
    if((dp = opendir(dirname))==NULL){
      fprintf(stderr, "can't open the %s: %s\n", dirname, strerror(errno));
      exit(EXIT_FAILURE);
    }
    while((dirp = readdir(dp))!=NULL){
      if(dirnsize == dirnite){
	dirnsize *=2;
	direntlist = realloc((void *)direntlist, dirnsize*sizeof(struct dirent));
	cdirent=direntlist+dirnite;
      }
      memcpy(cdirent, dirp, sizeof(struct dirent));
      dirnite++;
      cdirent++;
    }
  }

  closedir(dp);
  printf("the count of the stat is %d\n", dirnite);
  int i;
  cdirent = direntlist;
  for(i =0; i<dirnite; cdirent++, i++){
    printf("%d:\t%u\t\t%s", i,cdirent->d_ino, cdirent->d_name);
    printf("\t%u, %u, %u\n",strlen(cdirent->d_name), sizeof(*cdirent), sizeof(cdirent->d_ino));
  }
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
