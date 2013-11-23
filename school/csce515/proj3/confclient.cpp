#include <netdb.h> 
#include <arpa/inet.h>	
#include <iostream>
#include <stdio.h>
#include <list>
#include <pthread.h>
#include <sys/signal.h>
#include <string.h>
#include <stdlib.h>


using namespace std;



const int MAXLINE = 4096;
int sockfd;
struct sockaddr_in servaddr, recvaddr;
struct hostent* server;
int n;
char buffer[MAXLINE];
char* token;
list<sockaddr_in> client;
list<sockaddr_in>::iterator iter;


void error(const char* msg){
    perror(msg);
    exit(0);
}


// General socket functions
int Socket(int family, int type, int protocol){
	int n = socket(family, type, protocol);
	if(n < 0)
		error("socket() error\n");
	return n;
}

// I/O
int Recvfrom(int sockfd, char* buffer, int size, 
			 struct sockaddr_in* addr){
	socklen_t len = sizeof(*addr);	
	int n = recvfrom(sockfd, buffer, size, 0, 
					 (struct sockaddr*) addr, &len);
	if(n < 0)
		error("recvfrom() error\n");
	return n;
}

int Sendto(int sockfd, char* buffer, int size, 
			 struct sockaddr_in* addr){
	socklen_t len = sizeof(*addr);	
	int n = sendto(sockfd, buffer, size, 0, 
				   (struct sockaddr*) addr, len);
	if(n < 0)
		error("sendto() error\n");
	return n;
}


// Closing client handler
void sigLeave(int signo){	
	printf("\nSending LEAVE to server...\n");
	Sendto(sockfd, "LEAVE", 5, &servaddr);
	exit(0);
}


// Child process
void* userInput(void* data){
	while(true){
		if(fgets(buffer, MAXLINE-1, stdin) == NULL)	 // Catch CTRL + D
			sigLeave(SIGINT);		
		
		// Send to all other clients
		for(iter = client.begin(); iter != client.end(); iter++)
			Sendto(sockfd, buffer, strlen(buffer), &(*iter));
	}
	pthread_exit(NULL);
}


int main (int argc, char * const argv[]) {	
	if (argc < 3)
		error("usage %s hostname port");

	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);	
	
	// Setup server address
	bzero((char*) &servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;	
	server = gethostbyname(argv[1]);
    bcopy((char*) server->h_addr,
		  (char*) &servaddr.sin_addr.s_addr,
		  server->h_length);
    servaddr.sin_port = htons(atoi(argv[2]));
	
	// Join server
	printf("Sending JOIN to server (%s:%i)...\n", 
		   argv[1], ntohs(servaddr.sin_port));
	
	Sendto(sockfd, "JOIN", 4, &servaddr);	
	
	// Setup signals for quitting clients
	signal(SIGHUP, sigLeave);		// Catch closing window
	signal(SIGINT, sigLeave);		// Catch CTRL + C
	signal(SIGQUIT, sigLeave);		// Catch CTRL + \\
	
	// Collect user input
	pthread_t child;
	if(pthread_create(&child, NULL, userInput, NULL))
		error("pthread_create() error");
			
	// Listen for client and server messages
	while(true){
		n = Recvfrom(sockfd, buffer, MAXLINE, &recvaddr);
		
		// Check for server message
		if(recvaddr.sin_addr.s_addr == servaddr.sin_addr.s_addr &&
		   recvaddr.sin_port == servaddr.sin_port){				
			
			if(strncmp(buffer, "JOIN", 4) == 0){													
				token = strtok(buffer, " ");
				token = strtok(NULL, " ");		
				recvaddr.sin_addr.s_addr = atoi(token);
				token = strtok(NULL, " ");
				recvaddr.sin_port = atoi(token);
						
				client.push_back(recvaddr);
			}
			else if(strncmp(buffer, "LEAVE", 5) == 0){											
				token = strtok(buffer, " ");
				token = strtok(NULL, " ");		
				recvaddr.sin_addr.s_addr = atoi(token);
				token = strtok(NULL, " ");
				recvaddr.sin_port = atoi(token);
				
				for(iter = client.begin(); iter != client.end(); iter++){
					if((*iter).sin_addr.s_addr == recvaddr.sin_addr.s_addr &&
					   (*iter).sin_port == recvaddr.sin_port){
						client.erase(iter);
						break;
					}
				}
			}	
			
			//printf("clients: %i\n", client.size() + 1);							
		}
		else{  // Client messages
			printf("%i:%i>  ", 
				   recvaddr.sin_addr.s_addr, ntohs(recvaddr.sin_port));
			fwrite(buffer, sizeof(char), n, stdout);
		}		
	}
	
    return 0;
}
