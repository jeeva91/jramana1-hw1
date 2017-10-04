#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

typedef struct{
  int id;
  char name[10];
}mystruct;


int strcomparator(const void*, const void*);

int
main(void){
  mystruct *ms,*mi;
  ms = calloc(10, sizeof(mystruct));
  int i;
  char *animals[10]={"dog", "cat", "pig", "abi", "harika", "cow", "deer", "mouse", "rat", "man"};
  mi = ms;
  for(i=0;i<=9;mi++,i++){
    mi->id =i;
    strcpy(mi->name, animals[i]);
    
  }
  mi = ms;
  
  printf("before sorting\n");
  for(i=0;i<=9;mi++, i++){
    printf("id: %d, name: %s\n", mi->id, mi->name);
     
  }
  qsort(ms, 9, sizeof(mystruct), strcomparator);
  mi=ms;
  printf("after sorting\n");
  for(i=0;i<=9;mi++, i++){
    printf("id: %d, name: %s\n", mi->id, mi->name);
     
  }

  return 0;
}

int strcomparator(const void* fir, const void* sec){
  char *first, *second;
  mystruct *fs, *ss;
  fs = (mystruct*)fir;
  ss = (mystruct*)sec;
  first = fs->name;
  second = ss->name;

  return strcmp(first, second);

}
