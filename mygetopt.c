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
  int A, a, c, C, d, F, f, h, i, k, l, n, q, R, r, S, s, t, u, w, x, one = 0;
  char *fileptr, *current_fileptr; //ptrs to get the operands(filenames)
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
	break;
      case 'a':
	a = 1;
	break;
      case 'c':
	c = 1;
	break;
      case 'C':
	C = 1;
	break;
      case 'd':
	d = 1;
	break;
      case 'F':
	F = 1;
	break;
      case 'f':
	f = 1;
	break;
      case 'h':
	h = 1;
	break;
      case 'i':
	i = 1;
	break;
      case 'k':
	k = 1;
	break;
      case 'l':
	l = 1;
	break;
      case 'n':
	n = 1;
	break;
      case 'q':
	q = 1;
	break;
      case 'R':
	R = 1;
	break;
      case 'r':
	r = 1;
	break;
      case 'S':
	S = 1;
	break;
      case 's':
	s = 1;
	break;
      case 't':
	t = 1;
	break;
      case 'u':
	u =1;
	break;
      case 'w':
	w = 1;
	break;
      case 'x':
	x = 1;
	break;
      case '1':
	one =1;
	break;
      default:
	printf("this is ls");
	/*
	 *print the usage
	 */
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

  if(A){
  }
  if(a){
  }
  if(c){
  }
  if(C){
  }
  if(d){
  }
  if(F){
  }
  if(f){
  }
  if(h){
  }
  if(i){
  }
  if(k){
  }
  if(l){
  }
  if(n){
  }
  if(q){
  }
  if(R){
  }
  if(r){
  }
  if(S){
  }
  if(s){
  }
  if(t){
  }
  if(u){
  }
  if(w){
  }
  if(x){
  }
  if(one){
  }
  
  
  
    printf("got A\n");
  current_fileptr = fileptr;
  for(iterator = 0;iterator<filecnt; iterator++){
    printf("%s\n", current_fileptr);
    current_fileptr = current_fileptr + FILENAMESIZE;
  }






  free(fileptr);


  return 0;
}
