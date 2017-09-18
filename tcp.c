/* Trivial copy program *
* input: Source and destination filename with path *
* output: The files will be copied to the destination *
* Author: Jeeva *
* date: 09/18/2017 */

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<libgen.h>

#define SUCCESS 0
#define FAIL 2
#define BUFFSIZE 8
#define READ 1
#define WRITE 2

int printerror(int errn);
int usage(void);
int verbose(void);
int options(char *opt[]);

int main(int argc, char *argv[]){
  int destination, source;
  ssize_t nr, nw;
  char *buff[BUFFSIZE];
/* check if the number of inputs is one */
  if(argc == 2){
    options(argv);
    return SUCCESS;
  }
  
  /* check if there is enough inputs to process */
  else if(argc !=3){
    fprintf(stderr, "Enter correct number of inputs\n");
    usage();
    return FAIL;
  }
/* get the file descriptor for the source file */
  if((source = open(argv[1], O_RDONLY)) > 0){

    /* get the file descriptor for the destination file */
    if((destination = open(argv[2], O_WRONLY|O_CREAT))>0){

      /* read the data from the source and copy to the dest using buffer */
      while((nr = read(source, buff, 8)) != -1 && nr!=0){

	if((nw = write(destination, buff, nr)) != -1 && nw !=0)
	  ;
	else {
	  printerror(errno);
	  return FAIL;
	}
      }     
      close(source);
      close(destination);
      return SUCCESS;
    }
    else {
      printerror(errno);
      return FAIL;
    }
    
  }
  else {
    printerror(errno);
    return FAIL;
  }
}

/* function to print the error message *
* input: error number *
* output: displays the error to the screen */

int printerror(int errn){
  fprintf(stderr, strerror(errn));
  return SUCCESS;
}

/* function to print the usage of the TCP *
* input: Void *
* output: displays the usage of TCP */

int usage(void){
  printf("Trivial Copy\n");
  printf("syntax: tcp <source> <destination>\n");
  return SUCCESS;
}

/* function to print the usage of the TCP *
* input: Void *
* output: displays the verbose of TCP */

int verbose(void){
  printf("Trivial Copy\n");
  printf("Copies the data from source file to destination\n");
  printf("syntax: tcp <source> <destination>\n");
  printf("-h help\n");
  printf("-v verbose\n");
  printf("-p program name\n");
  return SUCCESS;

}

int options(char *opt[]){
  int argc, ch;
  argc =2
    ;
  ch = getopt(argc, opt, "HPVhpv");
  switch(ch){
  case('h'):
    verbose();
    break;
  case('p'):
    printf("Trivial Copy\n");
    break;
  case('v'):
    verbose();
    break;
  case('H'):
    usage();
    break;
  case('P'):
    printf("Trivial Copy\n");
    break;
  case('V'):
    verbose();
    break;
  default:
    usage();
  }

  return SUCCESS;
}
