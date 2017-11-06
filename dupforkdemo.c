#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/wait.h>

/* this program is to demo the fork and file descriptor */

int
main(void){

  int file, result;
  pid_t pid;
  if((file = open("dog", O_WRONLY|O_CREAT))==-1){
    perror("error when opening the file");
    exit(-1);
  }

  if((pid = fork())<0){
    perror("fork failed");
  }

  if(pid==0){ 			/* child */
    
    if((result = write(file, "hi\n", 4))==-1){
      perror("error in writing to the file");
    }
    close(file);
  }
  else{                      /* parent */
    if((result = dup2(file, STDOUT_FILENO))!=STDOUT_FILENO){
      perror("unable to dup the stdout");
      
    }
    printf("hello from the parent\n");
    close(file);
  }
  

  return 0;
}
