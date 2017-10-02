/* program to get the filename from the given path */
/* author:jeeva */
/* date: 09/16/2017 */

#include<stdio.h>
#include<libgen.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

#define SUCCESS 0
#define FAIL -1
#define BUFFSIZE 32
#define NBYTES 32

int main(int argc, char *argv[]){
  char *filename;
  char *pathdir;
  char *buff[BUFFSIZE];
  size_t nbytes;
  nbytes = NBYTES;
  int sourcefile;
  ssize_t nr;
  filename = basename(argv[1]);
  pathdir = dirname(argv[1]);
  printf("the filename is %s and dirname is %s\n", filename, pathdir);
  char cwd[1024];
  if (getcwd(cwd, sizeof(cwd)) != NULL)
    fprintf(stdout, "Current working dir: %s\n", cwd);
  if(sourcefile = open(argv[1], O_RDONLY) > 0){
    sourcefile = open(argv[1], O_RDONLY);
    printf("the filedescriptor is %d.. reading the file\n", sourcefile);
    nr = read(sourcefile, buff, 2);
    close(sourcefile);
    printf("%d", (int)nr);
    printf("read the file");
    if(nr != -1 && nr!=0)
      printf("%s", buff);
    else{
      fprintf(stderr, strerror(errno));
      return FAIL;
    }
 
  }
  else{
    fprintf(stderr, strerror(errno));
    return FAIL;
  }
  return SUCCESS;
}
