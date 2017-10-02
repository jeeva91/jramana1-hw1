/*my getcwd test
 *author:jeeva
 * date: 09/01/2017
 */

#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<stdlib.h>
//#include<sys/types.h>
//#include<sys/stat.h>


#define BUFFSIZE 50

int
main(void){
  char *dirname;
  if((dirname = getcwd(dirname))==NULL){
      fprintf(stderr, "can't get the CWD %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
  printf("the directory is %s", dirname);
  return 0;
  
}
