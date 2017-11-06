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

  int file, r;
  if((file = open("dog.txt", O_WRONLY|O_CREAT))<0){
    //perror("open failled", errno);
    fprintf(stderr, strerror(errno));
    exit(1);
  }
  printf("%d\n", file);
  if(r=(dup2(file, STDOUT_FILENO))!=file){
    fprintf(stderr, strerror(errno));
  }
  printf("%d\n",r);
  // printf("this is from the program");
  if((r = write(STDOUT_FILENO, "hi\n", 4))==1){
    printf("%d\n",r);
    fprintf(stderr, strerror(errno));
    exit(1);
  }
  printf("%d\n",r);
  printf("%d\n",STDOUT_FILENO);
  close(file);
  
  return 0;
}
