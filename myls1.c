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
  char f_name[FILESIZE];
  struct stat sb;
}dirdetails;

int dirdts_size;
int dirdts_cnt;

dirdetails* get_dirdts(char *filename, dirdetails *);

int
main(int argc, char *argv[]){
  char* filename;
  dirdetails *dirdts, *current_dirdts;
  dirdts_size = 10;
  dirdts_cnt = 0;
  if((dirdts = calloc(dirdts_size, sizeof(dirdetails)))==NULL){
    fprintf(stderr,
	    "Error while getting the Memory allocated%s\n",
	    strerror(errno));
    exit(EXIT_FAILURE);
  }
  /*  
  if(argc ==1){
    if((filename = getwd(filename))==NULL){
      fprintf(stderr, "can't get the CWD %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
    dirdts_cnt = get_dirdts(filename, dirdts, dirdts_cnt);
    /*
     *include the print here
     *
   
    
  }
*/

  dirdts = get_dirdts("tcp.c", dirdts);
  printf("the file count is %d\n",dirdts_cnt);
  
  

  return 0;
}

/*
 *read the stat of the file given in the filename/ in case of dir, 
 *read all the files in the dirdts
 *file_cnt in the global variable is updated, which can be accessed 
 *to get the number of files.
 * returns the pointer to the dirdetails.
 */

dirdetails*
get_dirdts(char *filename, dirdetails *dirdts){
  struct dirent *dirp;
  DIR* dp;
  struct stat f_stat, sb_stat;
  dirdetails *current_dirdts, sb_dirdts;
  current_dirdts = dirdts + dirdts_cnt;

  if((stat(filename, &f_stat))==-1){
    fprintf(stderr,
	    "Can't stat the file %s, %s\n",
	    filename,
	    strerror(errno));
    if(errno == ENOENT){
      return dirdts;
    }
    else{
    exit(EXIT_FAILURE);
    }
  }

  
  //if it's directory, then read dir and add allthe files to the dirdts
  if(S_ISDIR(f_stat.st_mode)){
    dp = opendir(filename);
    while((dirp = readdir(dp)) != NULL){
        //check if there is enough space in the dirdts
      if(dirdts_size == dirdts_cnt){
	dirdts_size *=2; 
	dirdts = realloc(dirdts,
			 dirdts_size*sizeof(dirdetails));
      }
      strcpy(sb_dirdts.f_name, dirp->d_name); /* to be checked in debugging */
      if((stat(dirp->d_name, &sb_stat)) ==-1){
	fprintf(stderr, "Can't stat the file %s, %s\n",
		filename, strerror(errno));
	exit(EXIT_FAILURE);
      }
      else{
	sb_dirdts.sb = sb_stat; /* to be checked in debugging */
	memcpy(current_dirdts, &sb_dirdts, sizeof(dirdetails));
      }
      current_dirdts++;
      dirdts_cnt++;
    }
  }
  // if not a directory, push the stat of the file to the dirdts
  else{
    strcpy(sb_dirdts.f_name, filename);
    sb_dirdts.sb = f_stat;
    //check for enough space in the dirdts
    if(dirdts_size == dirdts_cnt){
      dirdts_size *=2; 
      dirdts = realloc(dirdts, dirdts_size*sizeof(dirdetails));
    }
    memcpy(current_dirdts, &sb_dirdts, sizeof(dirdetails));
    current_dirdts++;
    dirdts_cnt++;

  }
  
  return dirdts;
}



