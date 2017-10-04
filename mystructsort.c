/*program to try struct and sort
 *author: jeeva
 * date: 09/30/2017
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define ARRAYSIZE 10

typedef struct mmm{
  int id;
  char *name;
}mystruct;


int arraycomparator(const void*, const void*);
int array_manipul(void);
int structcmparrator(const void*, const void*);
int struct_manipul(void);

int main(void){
  array_manipul();

  return 0;
}

int array_manipul(void){
  
  /* mystruct *ms; */
  /* ms = calloc(10, mystruct); */

  printf("the size of hte mystruct is %d", sizeof(struct mmm));
  
  int *myarray,*inte, i, j;
  printf("allocating the myarray\n");
  myarray = calloc(ARRAYSIZE, sizeof(int));
  printf("memory allocated\n");
  inte = myarray;
  for(j=9;j>=0;inte++, j--){
    *inte = j;
  }
  printf("the address of the my array%d\n", myarray);
  printf("array before  sorting\n");
  for(i=0;i<ARRAYSIZE;i++){
    printf("my array value is %d\n", myarray[i]);
  }
  qsort(myarray, (size_t)ARRAYSIZE, sizeof(int), arraycomparator);
  printf("array after sorting\n");
  for(i=0;i<ARRAYSIZE;i++){
    printf("my array value is %d\n", myarray[i]);
  }
  printf("freeing the memory\n");
  free(myarray);
  printf("freed the memory\n");
  return 0;
}


int arraycomparator(const void* fir, const void* sec){
  int *first, *second;
  first = (int*) fir;
  second = (int*) sec;
  if(*first > *second) return 1;
  else if(*first < *second) return -1;
  else return 0;

}
