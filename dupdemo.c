/*
 *dup select demo
 *author: jeeva
 *date: 11/05/2017
 */

#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

int main(){

  int file;
  if((file = open("dog.txt", O_WRONLY|O_CREAT))<0){
    //perror("open failled", errno);
    fprintf(stderr, strerror(errno));
    exit(1);
  }
  printf("%d\n", file);
  dup2(STDOUT_FILENO, file);
  printf("this is from the program");
  
  
  return 0;
}
