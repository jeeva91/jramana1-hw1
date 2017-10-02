/* this program is to test the command
 *line argument
 *author: jeeva
 *data: 09/16/2017
 */

#include<stdio.h>

int main(int argc, char *argv[]){
  printf("%d\n", argc);
  /* for(int i=1; i&argc; i++) */
  /*   printf("%s", argv[i]); */
  for(int i=1; i<argc; i++)
    printf("%s ", argv[i]);

}
