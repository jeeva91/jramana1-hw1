#include<stdio.h>
#include<string.h>
//#include<greet.h>


void
greet(void);

void
hello(const char * friend, const char * greeting);

char *
getgreeting(void);

int
setgreeting(const char * greeting);

char* greetmessage;

void
greet(void){
  printf("%s\n", greetmessage);

}


void
hello(const char * friend, const char * greeting){

  printf("%s: %s ", friend, greeting);

}


char *
getgreeting(void){

  return greetmessage;
}

int
setgreeting(const char * greeting){

  greetmessage = "Hello!";
  return 0;
}
