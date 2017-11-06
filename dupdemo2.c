#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>

int main(void){
  int file, r;
  if((file = open("dog", O_WRONLY|O_CREAT)),0){
    perror("unable to open the file");
    exit(1);
  }
  if((r = dup2(file, STDOUT_FILENO))!=STDOUT_FILENO){
    perror("unable to dupe the stdout to file");
  }
  
  printf("stdout is %d\n", STDOUT_FILENO);
  printf("file is %d\n", file);
  printf("r is %d\n", r);

  if((r = write(STDOUT_FILENO, "HI\n", 4))<0){
    perror("error in writing");
  }


  
  return 0;
}  
  
