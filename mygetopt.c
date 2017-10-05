/*my get_opt function trial
 *author: jeeva
 *date: 10/02/2017
 */

#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<stdlib.h>

#define FILENAMESIZE 255

int main(int argc, char *argv[]){
  //  Å|AacCdFfhiklnqRrSstuwx1

  int A, a, c, C, d, F, f, h, i, k, l, n, q, R, r, S, s, t, u, w, x, one = 0;
  char *fileptr, *current_fileptr; //ptrs to get the operands(filenames)
  //  char filename[FILENAMESIZE];
  int filenms_memsize =5;          // number of filenames the fileptr can hold
  int filecnt = 0;                 // number of filenames present in the fileptr
  int opt;
  int iterator;

  if((fileptr = malloc(filenms_memsize*FILENAMESIZE))==NULL){
    fprintf(stderr, "Error while allocating the memory fo rthe filenames");
    exit(EXIT_FAILURE);
  }
  current_fileptr = fileptr;

  while(optind < argc){
    if((opt = getopt(argc, argv, "AacCdFfhiklnqRrSstuwx1")) != -1){
      switch(opt){
      case 'A':
	A = 1;
      case 'a':
	a = 1;
      case 'c':
	c = 1;
      case 'C':
	C = 1;
      case 'd':
	d = 1;
      case 'F':
	F = 1;
      case 'f':
	f = 1;
      case 'h':
	h = 1;
      case 'i':
	i = 1;
      case 'k':
	k = 1;
      case 'l':
	l = 1;
      case 'n':
	n = 1;
      case 'q':
	q = 1;
      case 'R':
	R = 1;
      case 'r':
	r = 1;
      case 'S':
	S = 1;
      case 's':
	s = 1;
      case 't':
	t = 1;
      case 'u':
	u =1;
      case 'w':
	w = 1;
      case 'x':
	x = 1;
      case '1':
	one =1;

      }	
    }
    /*
     *The else gets the operands if any and stores in the fileptr
     */
    else{ 
      if(filecnt == filenms_memsize){
	filenms_memsize = filenms_memsize*2;
	if((fileptr = realloc(fileptr, filenms_memsize*FILENAMESIZE))==NULL){
	  fprintf(stderr, "Error while allocating the memory fo rthe filenames");
	  exit(EXIT_FAILURE);
	}
      }
      strcpy(current_fileptr, argv[optind]);
      optind++;
      filecnt++;
      current_fileptr +=FILENAMESIZE; 
      
    }
  }

  if(A)
    printf("got A\n");
  current_fileptr = fileptr;
  for(iterator = 0;iterator<filecnt; iterator++){
    printf("%s\n", current_fileptr);
    current_fileptr = current_fileptr + FILENAMESIZE;
  }

  free(fileptr);


  return 0;
}
