/*
 * This is the main part of sws
*/

#include <sys/types.h>

#include <arpa/inet.h>
#include <netinet/in.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_DIRECTORY_LENGTH 256

#define MAX_IPv4_LENGTH 15
#define MAX_IPv6_LENGTH 45

#define MIN_PORT 1024
#define MAX_PORT 65535

#define MAX_HTTP_HEADER	10000
#define MAX_URI_LENGTH	1024

#define METHOD_GET 	0;
#define METHOD_HEAD	1;

static void usage(const char* error);

/*
 * check if the input string is a number
 * if not return -1; 
*/
long int
checkDigit(char* string){
	long int p;
	
	p=0;
	char* i=string;
	while(*i!='\0'){
		if(*i<='9'&&*i>='0')
			p=p*10+(*i-'0');
		else
			return -1;
		i+=1;
	}
	return p;
}

/*
 * check if the input string is a hexadecimal number
 * if not return -1; 
*/
int
checkSegment(char* string){
	int count;
	count=0;
	while(*string!='\0'){
		if((*string>='0'&&*string<='9')||\
			(*string>='a'&&*string<='f')||\
			(*string>='A'&&*string<='F'))
			string+=1;
		else
			usage("invalid ipv6");
		count+=1;
	}
	if(count<=4)
		return 0;
	else
		return -1;
}

/*
 * This Funcion will be called by main
 * This funciont check whether input string is valid ip address
 * return 0--ipv4, 1--ipv6, or jump to usage when error
*/
int
checkIPAddress(char* string){
	int ipVersion,count;	//1:ipv4 -1:ipv6 0 invalid
	char seperator[2];
	char* i;

	ipVersion=0;
	i=string;

	while(*i!='\0'){
		if(*i=='.'){
			ipVersion=1;
			strcpy(seperator,".");
			break;
		}
		if(*i==':'){
			ipVersion=-1;
			strcpy(seperator,":");
			break;
		}
		i+=1;
	}

	count=0;
	i=(char*)malloc(sizeof(string));
	strcpy(i,string);

	switch(ipVersion){
		case 1:
			i=strtok(i,seperator);
			int octet;
			while(i){
				if((octet=checkDigit(i))==-1)
					usage("invalid ipv4");

				if(octet>=0&&octet<=255){
					i=strtok(NULL,seperator);
					if(i!=NULL)
						count+=1;
				}
				else
					usage("invalid ipv4");
			}
			if(count!=3)
				usage("invalid ipv4");
			free(i);
			return 0;
		case -1:
			i=strtok(i,seperator);
			while(i){
				if(checkSegment(i)==-1)
					usage("invalid ipv6");
				count+=1;
				i=strtok(NULL,seperator);
			}
			if(count<=8)
				return 1;
			usage("your ipv6 address has too many segments");
		default:
			usage("your ip address is nither ipv4 nor ipv6");
	}

	return 0;
}

/*
 * This Funcion will be called by main
 * This funciont check whether input string is valid port
 * return port number or jump to usage when error
*/
int
checkPort(char* string){
	long int p;

	p=0;

	if((p=checkDigit(string))==-1)
		usage("your port number invalid");
	if(p>MAX_PORT||p<MIN_PORT)
		usage("port number must between 1024 and 65536");

	return p;
}

/*
 * This Function can check the request-line
 * If it is right, return 2xx
 * If method not in GET,HED return 400
 * If protocol is not HTTP/1.0 return 505
 * if uri is too long return 400
*/
int 
checkRequestLine(char* string,int* methodType,char* uri_return){
	int i;
	char* method;
	char* uri;
	char* HTTP;

	method=strtok(string," ");
	if(!method){
		usage("wrong method");
	}
	else if(strcmp(method,"GET")==0){
		*methodType=METHOD_GET;
	}
	else if(strcmp(method,"HEAD")==0){
		*methodType=METHOD_HEAD;
	}
	else{
		return 400;
	}

	uri=strtok(NULL," ");
	if(!uri||strlen(uri)>MAX_URI_LENGTH)
		return 400;
	strncpy(uri_return,uri,strlen(uri));

	HTTP=strtok(NULL, "\r\n");
	while(*HTTP==' ')
		HTTP+=1;
	if(strncmp(HTTP,"HTTP/1.0",strlen("HTTP/1.0"))==0){
	// -1 because at the end of "", there is a '\0'
		i=8;
		while(*(HTTP+i)){
			if(*(HTTP+i)!=' ')
				return 505;
			i+=1;
		}
	}
	else
		return 505;
	
	return 200;
}

void reverse(char s[]){
     int i, j;
     char c;

     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
}  

void my_itoa(int n, char s[]){
     int i, sign;

     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
}  

/*
 * When error happen, this funcion will be called
*/
static void
usage(const char* error){
	(void)fprintf(stderr,"usage:%s \n",error);
	exit(EXIT_FAILURE);
}

/*
 * This is the main funciont of sws
 * We start our program here
*/
int
main(int argc, char** argv){
	int c,d,l;
	int port;

	int sock,msgsock,rval;
	
	int method;
	int status_code;

	const char* options, *synopsis;
	char ch;

	char header[MAX_HTTP_HEADER];
	char uri[MAX_URI_LENGTH];
	
	char* log_file, *dir;
	char* ipTemp,*portTemp;
	char* ipv4,*ipv6;

	socklen_t length;
	struct sockaddr_in server4;
	struct sockaddr_in client;

	options="c:dhi::l:p::";
	synopsis="[-dh] [-c directory] [-i ip address] [-p port] [-l file]";

	port=8080;
	ipTemp=portTemp=NULL;
	ipv4=ipv6=NULL;

	while((ch=getopt(argc,argv,options))!=-1){
		switch(ch){
			case 'c':
				c=1;
				if((dir=(char*) malloc(sizeof(char)*MAX_DIRECTORY_LENGTH))==NULL)
					usage(strerror(errno));
				strncpy(dir,optarg,MAX_DIRECTORY_LENGTH);
				printf("c:%d:%s\n",c, dir);
				break;
			case 'd':
				d=1;
				printf("capture -d:%d\n",d);
				break;
			case 'h':
				usage(synopsis);
			case 'i':
				if(optarg!=NULL){
					if((ipTemp=(char*)malloc(sizeof(char)*strlen(optarg)))==NULL)
						usage(strerror(errno));
					strcpy(ipTemp,optarg);
				}
				else if(argv[optind]&&*(argv[optind])!='-'){
					if((ipTemp=(char*)malloc(sizeof(char)*strlen(argv[optind])))==NULL)
						usage(strerror(errno));
					strcpy(ipTemp,argv[optind]);
				}
				break;
			case 'l':
				l=1;
				if((log_file=(char*)malloc(sizeof(char)*MAX_DIRECTORY_LENGTH))==NULL)
					usage(strerror(errno));
				strncpy(log_file,optarg,MAX_DIRECTORY_LENGTH);
				printf("l:%d %s\n",l, log_file);
				break;
			case 'p':
				if(optarg!=NULL){
					if((portTemp=(char*)malloc(sizeof(char)*strlen(optarg)))==NULL)
						usage(strerror(errno));
					strcpy(portTemp,optarg);
				}
				else if(argv[optind]&&*(argv[optind])!='-'){
					if((portTemp=(char*)malloc(sizeof(char)*strlen(argv[optind])))==NULL)
						usage(strerror(errno));
					strcpy(portTemp,argv[optind]);
				}
				break;
			default:
				usage(synopsis);
		}
	}

	printf("Finish reading options\n");

	if(ipTemp)
		switch(checkIPAddress(ipTemp)){
			case 0:
				if((ipv4=(char*)malloc(sizeof(char)*strlen(ipTemp)))==NULL)
					usage("memory error");
				strcpy(ipv4,ipTemp);
				break;
			case 1:
				if((ipv6=(char*)malloc(sizeof(char)*strlen(ipTemp)))==NULL)
					usage("memory error");
				strcpy(ipv6,ipTemp);
				break;
			default:
				usage("canot get IP Address");
		}

	if(ipv4){
		server4.sin_addr.s_addr=inet_addr(ipv4);
		printf("ipv4 get: %s\n", ipv4);
	}
	else{
		server4.sin_addr.s_addr=INADDR_ANY;
		printf("listen all ipv4\n");
	}
	server4.sin_family=AF_INET;

	if(portTemp)
		port=checkPort(portTemp);
	server4.sin_port=htons(port);
	printf("port is :%d\n", port);

	if((sock=socket(AF_INET,SOCK_STREAM,0))<0)
		usage("opening stream socket fail");
	if(bind(sock,(struct sockaddr*)&server4,sizeof(server4))!=0)
		usage("binding fail");
	
	listen(sock,5);
	while(1){
		length=sizeof(client);
		msgsock=accept(sock,(struct sockaddr*)&client,&length);
		if(msgsock==-1)
			usage("accept error");
		else{
			if((rval=read(msgsock,header,MAX_HTTP_HEADER))<0)
				usage("cannot read header");

			if(rval==0)
				printf("Finish reading header\n");
			else{
				status_code=checkRequestLine(header,&method,uri);
				printf("methond is %d\n",method);
				printf("uri is %s\n",uri);
				printf("%d\n", status_code);
				char snum[4];
				my_itoa(status_code,snum);
				write(msgsock,snum,sizeof(char)*5);
				break;
			}

		}
	}

	if(ipv6)
		printf("ipv6 get: %s\n", ipv6);
	else
		printf("listen all ipv6\n");

	return EXIT_SUCCESS;
}