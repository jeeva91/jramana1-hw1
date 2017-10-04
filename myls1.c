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



typedef struct{
  struct dirent dirp;
  struct stat sb;
}dirdetails;

int dirdts_size;

int get_dirdts(char *filename, dirdetails * dirdts, int dirdts_cnt);

int
main(int argc, char *argv[]){
  char* filename;
  dirdetails *dirdts, *current_dirdts;
  int dirdts_cnt;
  dirdts_size = 10;
  dirdts_cnt = 0;
  if((dirdts = calloc(dirdts_size, sizeof(dirdetails)))==NULL){
    fprintf(stderr, "Error while getting the Memory allocated");
    exit(EXIT_FAILURE);
  }
  
  if(argc ==1){
    if((filename = getwd(filename))==NULL){
      fprintf(stderr, "can't get the CWD %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
    
  }



  return 0;
}
