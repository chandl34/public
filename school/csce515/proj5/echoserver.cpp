#include <netinet/in.h>		
#include <arpa/inet.h>	
#include <fcntl.h>
#include <sys/errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <iostream>

using namespace std;


const int MAXLINE = 4096, LISTENQ = 1024;
static struct flock lock, unlock;
static int lockfd = -1;
int listenfd, connfd;
int children;
pid_t* pid;


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

void Close(int sockfd){
	if(close(sockfd) < 0)
		error("close() error\n");
}


// Server socket functions
void Bind(int sockfd, struct sockaddr_in* addr){	
	if(bind(sockfd, (struct sockaddr*) addr, sizeof(*addr)) < 0)
		error("bind() error\n");
}

void Listen(int sockfd){
	if(listen(sockfd, LISTENQ) < 0)
		error("listen() error\n");
}

int Accept(int sockfd){	
	int n = accept(sockfd, 0, 0);
	if(n < 0)
		error("accept() error\n");
	return n;
}


// I/0
int Read(int sockfd, char* buffer, int s){
	int n = read(sockfd, buffer, s);
	if(n < 0)
		error("read() error\n");
	return n;
}

int Write(int sockfd, char* buffer, int s){
	int n = write(sockfd, buffer, s);
	if(n < 0)
		error("write() error\n");
	return n;
}


// Closing handler
void sigParent(int signo){	
	printf("Server shutting down...\n");
	Close(listenfd);
	
	// Kill children
	for(int i = 0; i < children; i++){		
		if(kill(pid[i], SIGCHLD) < 0)
			printf("pid %i did not receive kill signal\n", pid[i]);
	}
	
	// Make sure children are dead
	for(int i = 0; i < children; i++)
		waitpid(pid[i], NULL, 0);
	
	printf("Shutting down parent...\n");		
	
	delete [] pid;
	
	exit(0);
}

void sigChild(int signo){	
	printf("Child %i shutting down...\n", getpid());
	Close(listenfd);
	close(connfd);	
	exit(0);
}

void sigIgnore(int signo){}


// Locking
void initLockFile(char* filepath){
	char file[1024];
	
	strncpy(file, filepath, sizeof(file));
	lockfd = mkstemp(file);
	if(lockfd < 0)
		error("mkstemp() error");
	
	if(unlink(file) < 0)
		error("unlink() error");
	
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;
	
	unlock.l_type = F_UNLCK;
	unlock.l_whence = SEEK_SET;
	unlock.l_start = 0;
	unlock.l_len = 0;
}

void lockWait(){
	while(fcntl(lockfd, F_SETLKW, &lock) < 0){
		if(errno != EINTR)
			error("lockWait() error");		
	}	
}

void lockRelease(){
	if(fcntl(lockfd, F_SETLKW, &unlock) < 0)
		error("lockRelease() error");	
}



int main (int argc, char * const argv[]) {	
	if(argc < 3)
		error("usage %s port children");
	
	char buffer[MAXLINE];
	struct sockaddr_in localAddr;
	int n, i;
	children = atoi(argv[2]);
	pid = new pid_t[children];
		
	bzero(&localAddr, sizeof(localAddr));
	localAddr.sin_family = AF_INET;
	localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	localAddr.sin_port = htons(atoi(argv[1]));
	
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);
	Bind(listenfd, &localAddr);
	Listen(listenfd);
		
	initLockFile("/tmp/lock.XXXXXX");
	
	for(i = 0; i < children; i++){		
		pid[i] = fork();
		if(pid[i] == 0){				
			// Children code	t
			signal(SIGINT, sigIgnore);	// Catch CTRL + C	
			signal(SIGCHLD, sigChild);	// Catch KILL from parent
			delete [] pid;				// Delete unused array
			
			while(true){
				lockWait();
				connfd = Accept(listenfd);
				lockRelease();
				printf("%i>  Client connected...\n", i);
			
				while(true){
					if((n = Read(connfd, buffer, MAXLINE)) == 0){
						printf("%i>  Client disconnected...\n", i);
						Close(connfd);
						break;
					}
					else
						Write(connfd, buffer, n);
				}
			}	
			// Code does not reach here
		}			
	}
		
	
	// Parent code	
	signal(SIGINT, sigParent);	// Catch CTRL + C	
	
	while(true){}		// Parent loops until SIGINT is sent
		
    return 0;
}
