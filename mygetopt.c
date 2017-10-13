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
#include<pwd.h>
#include<grp.h>
#include<time.h>
//#include<libbsd.h>

#define FILENAMESIZE 255

#define FILESIZE 255

typedef struct{
  char f_name[FILESIZE];
  struct stat sb;
}dirdetails;

int dirdts_size;
int dirdts_cnt;

dirdetails* get_dirdts(char *filename, dirdetails *);

void printfiles(dirdetails *dridts);

char* formatdate(char* str, time_t val);

int sort, sortr, filter_A, filter_a, filter_d,
  disp_opt_i, disp_opt_s,disp_opt_F,
  disp_spl, print_format, time_type, size_format, recursive;
//int A, a, c, C, d, F, f, h, i, k, l, n, q, R, r, S, s, t, u, w, x, one;

void printl(dirdetails *dirdts);
int rfname_comparator(const void* first, const void* second);
int rctimecomparator(const void* first, const void* second);
int ratimecomparator(const void* first, const void* second);
int rmtimecomparator(const void* first, const void* second);
int rsize_comparator(const void* first, const void* second);
int fname_comparator(const void* first, const void* second);
int ctimecomparator(const void* first, const void* second);
int atimecomparator(const void* first, const void* second);
int mtimecomparator(const void* first, const void* second);
int size_comparator(const void* first, const void* second);
  

int main(int argc, char *argv[]){
  //A, a, c, C, d, F, f, h, i, k, l, n, q, R, r, S, s, t, u, w, x, one = 0;
  sort =0;
  sortr = 0;
  filter_A = 0;
  filter_a = 0;
  filter_d = 0;
  disp_opt_i = 0;
  disp_opt_s = 0;
  disp_opt_F = 0;
  disp_spl = 'q';
  print_format = '1';
  time_type = 0;
  size_format = 'h';
  recursive = 0;


  char *fileptr, *current_fileptr; //ptrs to get the operands(filenames)
  int filenms_memsize =5;          // number of filenames the fileptr can hold
  int filecnt = 0;                 // number of filenames present in the fileptr
  int opt;
  int iterator;
  dirdetails *dirdts;
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
	filter_A = 1;
	break;
      case 'a':
	filter_a = 1;
	break;
      case 'c':
	time_type = 'c';
	break;
      case 'C':
	print_format = 'C';
	break;
      case 'd':
	filter_d = 1;
	break;
      case 'F':
	disp_opt_F = 1;
	break;
      case 'f':
	sort = 'f';
	break;
      case 'h':
	size_format = 'h';
	break;
      case 'i':
	disp_opt_i = 1;
	break;
      case 'k':
	size_format = 'k';
	break;
      case 'l':
	print_format = 'l';
	break;
      case 'n':
	print_format = 'n';
	break;
      case 'q':
	disp_spl = 'q';
	break;
      case 'R':
	recursive = 1;
	break;
      case 'r':
	sortr = 'r';
	break;
      case 'S':
	sort = 'S';
	break;
      case 's':
	disp_opt_s = 1;
	break;
      case 't':
	sort = 't';
	break;
      case 'u':
	time_type = 'u';
	break;
      case 'w':
	disp_spl = 'w';
	break;
      case 'x':
	print_format = 'x';
	break;
      case '1':
	print_format = '1';
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
    fileptr = NULL;
    fileptr = getcwd(fileptr, 0);
  }
  current_fileptr = fileptr;
  /* call the get_dirdts for all the operands */
  char temp_name[255];
  for(iterator = 0;iterator<filecnt; iterator++){
    printf("%s\n", current_fileptr);
    strcpy(temp_name, current_fileptr);
    dirdts = get_dirdts(temp_name, dirdts);
    current_fileptr = current_fileptr + FILENAMESIZE;
  }
  
  /*
   *sort as per the options
   */

  if(sortr){
    switch(sort){
    case 'f':
      break;
    case 's':
      qsort(dirdts,dirdts_cnt, sizeof(dirdetails), rsize_comparator);
      break;
    case 't':
      switch(time_type){
      case 'c':
	qsort(dirdts,dirdts_cnt, sizeof(dirdetails), rctimecomparator);
	break;
      case 'u':
	qsort(dirdts,dirdts_cnt, sizeof(dirdetails), ratimecomparator);
      default:
	qsort(dirdts,dirdts_cnt, sizeof(dirdetails), rmtimecomparator);
      }
      break;
    default:
      qsort(dirdts,dirdts_cnt, sizeof(dirdetails), rfname_comparator);
    }
  }
  else{
    switch(sort){
    case 'f':
      break;
    case 's':
      qsort(dirdts,dirdts_cnt, sizeof(dirdetails), size_comparator);
      break;
    case 't':
      switch(time_type){
      case 'c':
	qsort(dirdts,dirdts_cnt, sizeof(dirdetails), ctimecomparator);
	break;
      case 'u':
	qsort(dirdts,dirdts_cnt, sizeof(dirdetails), atimecomparator);
      default:
	qsort(dirdts,dirdts_cnt, sizeof(dirdetails), mtimecomparator);
      }
      break;
    default:
      qsort(dirdts,dirdts_cnt, sizeof(dirdetails), fname_comparator);
    }
  }


  // qsort(dirdts,dirdts_cnt, sizeof(dirdetails), size_comparator);

  printl(dirdts);


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
      if((lstat(filename, &f_stat))==-1){
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
      *cfname ='\0';
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
	if((lstat(cfname, &sb_stat)) ==-1){
	   fprintf(stderr, "Can't stat the file %s, %s\n",
		   dirp->d_name, strerror(errno));
	   continue;
	 }
      }
      else{
	sb_dirdts.sb = sb_stat;

	/*
	 *filter only the directories
	 */

	if(filter_d){
	  if(S_ISDIR(sb_stat.st_mode))
	    ;
	  else
	    continue;
	}

	/*
	 *filter the . and .. directories
	 */

	if(filter_A){
	  if(S_ISDIR(sb_stat.st_mode)){
	    if(strcmp(".", dirp->d_name)||strcmp("..",dirp->d_name))
	      ;
	    else
	      continue;
	  }
	}

	/*
	 *filter the files starting with .
	 */
	if(filter_a){
	  if(strncmp(dirp->d_name, ".", 1))
	    ;
	  else
	    continue;
	}
	
	memcpy(current_dirdts, &sb_dirdts, sizeof(dirdetails));
	current_dirdts++;
	dirdts_cnt++;
      }
      
    
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


void printfiles(dirdetails *dirdts){

  dirdetails *current_dirdts;
  int iterator;
  current_dirdts = dirdts;
  for(iterator = 0; iterator<dirdts_cnt;iterator++,current_dirdts++){
    if(disp_opt_i==1){
      printf("%lu\t%s\n",current_dirdts->sb.st_ino,current_dirdts->f_name);
    }
    else{
    printf("%s\n",current_dirdts->f_name);
    }
  }
}


void printl(dirdetails *dirdts){
  dirdetails *current_dirdts;
  int iterator;
  char mode[11];
  char date[36];
  
  current_dirdts = dirdts;
  for(iterator = 0; iterator<dirdts_cnt; iterator++, current_dirdts++){
    strmode(current_dirdts->sb.st_mode, mode);
    printf("%lu\t%s\t%s\t%s\t%lu\t%s\t%s\n",current_dirdts->sb.st_ino, mode,
	   getpwuid(current_dirdts->sb.st_uid)->pw_name,
	   getgrgid(current_dirdts->sb.st_gid)->gr_name,
	   current_dirdts->sb.st_size,
	   formatdate(date, current_dirdts->sb.st_ctime),
	   current_dirdts->f_name);
  
  }
  
}


int atimecomparator(const void* first, const void* second){
  time_t fs, ss;
  dirdetails *fir, *sec;
  fir = (dirdetails *)first;
  sec = (dirdetails *)second;
  fs = fir->sb.st_atime;
  ss = sec->sb.st_atime;

  if(fs>ss) return 1;
  else if(ss>fs) return -1;
  else return 0;
  

}


int mtimecomparator(const void* first, const void* second){
  time_t fs, ss;
  dirdetails *fir, *sec;
  fir = (dirdetails *)first;
  sec = (dirdetails *)second;
  fs = fir->sb.st_mtime;
  ss = sec->sb.st_mtime;

  if(fs>ss) return 1;
  else if(ss>fs) return -1;
  else return 0;
  

}


int ctimecomparator(const void* first, const void* second){
  time_t fs, ss;
  dirdetails *fir, *sec;
  fir = (dirdetails *)first;
  sec = (dirdetails *)second;
  fs = fir->sb.st_ctime;
  ss = sec->sb.st_ctime;

  if(fs>ss) return 1;
  else if(ss>fs) return -1;
  else return 0;
  

}

int size_comparator(const void* first, const void* second){
  size_t fs, ss;
  dirdetails *fir, *sec;
  fir = (dirdetails *)first;
  sec = (dirdetails *)second;
  fs = fir->sb.st_size;
  ss = sec->sb.st_size;

  if(fs>ss) return 1;
  else if(ss>fs) return -1;
  else return 0;
  

}

int ratimecomparator(const void* first, const void* second){
  time_t fs, ss;
  dirdetails *fir, *sec;
  fir = (dirdetails *)first;
  sec = (dirdetails *)second;
  fs = fir->sb.st_atime;
  ss = sec->sb.st_atime;

  if(fs>ss) return -1;
  else if(ss>fs) return 1;
  else return 0;
  

}


int rmtimecomparator(const void* first, const void* second){
  time_t fs, ss;
  dirdetails *fir, *sec;
  fir = (dirdetails *)first;
  sec = (dirdetails *)second;
  fs = fir->sb.st_mtime;
  ss = sec->sb.st_mtime;

  if(fs>ss) return -1;
  else if(ss>fs) return 1;
  else return 0;
  

}


int rctimecomparator(const void* first, const void* second){
  time_t fs, ss;
  dirdetails *fir, *sec;
  fir = (dirdetails *)first;
  sec = (dirdetails *)second;
  fs = fir->sb.st_ctime;
  ss = sec->sb.st_ctime;

  if(fs>ss) return -1;
  else if(ss>fs) return 1;
  else return 0;
  

}

int rsize_comparator(const void* first, const void* second){
  size_t fs, ss;
  dirdetails *fir, *sec;
  fir = (dirdetails *)first;
  sec = (dirdetails *)second;
  fs = fir->sb.st_size;
  ss = sec->sb.st_size;

  if(fs>ss) return -1;
  else if(ss>fs) return 1;
  else return 0;
  
}

int fname_comparator(const void* first, const void* second){
  char fs[255], ss[255];
  dirdetails *fir, *sec;
  fir = (dirdetails *)first;
  sec = (dirdetails *)second;
  strcpy(fs,fir->f_name);
  strcpy(ss,sec->f_name);
  return strcmp(fs,ss);
  
}

int rfname_comparator(const void* first, const void* second){
  char fs[FILENAMESIZE], ss[FILENAMESIZE];
  dirdetails *fir, *sec;
  fir = (dirdetails *)first;
  sec = (dirdetails *)second;
  strcpy(fs,fir->f_name);
  strcpy(ss,sec->f_name);
  return strcmp(ss,fs);
  
}

char* formatdate(char* str, time_t val){
  strftime(str, 36, "%b %d %H %M", localtime(&val));
  return str;

}
