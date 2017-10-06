/*my get_opt function trial
 *author: jeeva
 *date: 10/02/2017
 */

#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/param.h>
#include<sys/stat.h>
#include<dirent.h>

#define FILENAMESIZE 255

#define FILESIZE 255

typedef struct{
  char f_name[FILESIZE];
  struct stat sb;
}dirdetails;

int dirdts_size;
int dirdts_cnt;

dirdetails* get_dirdts(char *filename, dirdetails *);

int main(int argc, char *argv[]){
  int A, a, c, C, d, F, f, h, i, k, l, n, q, R, r, S, s, t, u, w, x, one = 0;
  char *fileptr, *current_fileptr; //ptrs to get the operands(filenames)
  int filenms_memsize =5;          // number of filenames the fileptr can hold
  int filecnt = 0;                 // number of filenames present in the fileptr
  int opt;
  int iterator;
  dirdetails *dirdts, *current_dirdts;
  dirdts_size = 10;
  dirdts_cnt = 0;
  if((dirdts = calloc(dirdts_size, sizeof(dirdetails)))==NULL){
    fprintf(stderr,
	    "Error while getting the Memory allocated%s\n",
	    strerror(errno));
    exit(EXIT_FAILURE);
  }  

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

  /* get the pwd as operand when no oprand is given */
  if(filecnt==0){
    filecnt++;
    fileptr = getcwd(fileptr, 0);
  }
  current_fileptr = fileptr;
  /* call the get_dirdts for all the operands */
  for(iterator = 0;iterator<filecnt; iterator++){
    printf("%s\n", current_fileptr);
    current_fileptr = current_fileptr + FILENAMESIZE;
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
  
  
  
  




  free(dirdts);
  //  free(cfname);
  free(fileptr);


  return 0;
}

dirdetails*
get_dirdts(char *filename, dirdetails *dirdts){
  struct dirent *dirp;
  DIR* dp;
  struct stat f_stat, sb_stat;
  dirdetails *current_dirdts, sb_dirdts;
  current_dirdts = dirdts + dirdts_cnt;

  if((stat(filename, &f_stat))==-1){
    fprintf(stderr,
	    "Can't stat the file %s, %s\n",
	    filename,
	    strerror(errno));
    if(errno == ENOENT){
      return dirdts;
    }
    else{
    exit(EXIT_FAILURE);
    }
  }

  
  //if it's directory, then read dir and add allthe files to the dirdts
  if(S_ISDIR(f_stat.st_mode)){
    dp = opendir(filename);
    char *cfname;
    if((cfname = malloc(MAXPATHLEN))==NULL){
      fprintf(stderr,"Can't get memory %s\n",strerror(errno));
      exit(EXIT_FAILURE);
    }
   
    while((dirp = readdir(dp)) != NULL){
      strcat(cfname, filename);
      strcat(cfname, "/");
      strcat(cfname, dirp->d_name);
      //check if there is enough space in the dirdts
      if(dirdts_size == dirdts_cnt){
	dirdts_size *=2; 
	if((dirdts = (dirdetails *)
	    realloc((void *)dirdts,
		    dirdts_size*sizeof(dirdetails)))==NULL){
	  fprintf(stderr,"Can't get memory %s\n",strerror(errno));
	  exit(EXIT_FAILURE);
	}
	current_dirdts = dirdts + dirdts_cnt;

      }
      strcpy(sb_dirdts.f_name, dirp->d_name); 
      if((stat(cfname, &sb_stat)) ==-1){
	fprintf(stderr, "Can't stat the file %s, %s\n",
		dirp->d_name, strerror(errno));
	continue;
      }
      else{
	sb_dirdts.sb = sb_stat;
	memcpy(current_dirdts, &sb_dirdts, sizeof(dirdetails));
      }
      current_dirdts++;
      dirdts_cnt++;
      *cfname ='\0';
    }
  }
  // if not a directory, push the stat of the file to the dirdts
  else{
    strcpy(sb_dirdts.f_name, filename);
    sb_dirdts.sb = f_stat;
    //check for enough space in the dirdts
    if(dirdts_size == dirdts_cnt){
      dirdts_size *=2; 
      if(( dirdts = (dirdetails *)
	   realloc((void *)dirdts,
		   dirdts_size*sizeof(dirdetails)))==NULL){
	fprintf(stderr,"Can't get memory %s\n",strerror(errno));
	exit(EXIT_FAILURE);
      }
      current_dirdts = dirdts + dirdts_cnt;
    }
    memcpy(current_dirdts, &sb_dirdts, sizeof(dirdetails));
    current_dirdts++;
    dirdts_cnt++;

  }
  
  return dirdts;
}
