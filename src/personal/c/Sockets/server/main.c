#include <stdio.h>   
#include <stdlib.h>
#include <strings.h>

#include <sys/select.h>
//#include <sys/time.h>

#include <sys/socket.h>
#include <netinet/in.h>


// Constants
const int MAX_LINE = 4096;
const int PUB_PORT = 10000;
const int PRV_PORT = 20000;


// Typedefs
typedef struct sockaddr SA;


// Utility functions
int max(int a, int b)
{
	if(a > b)
		return a;
	return b;
}

void error(const char* msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}


// Main function
int main(char** argv, int argc)
{
	// Verify arguments
	if(argc != 2)
	{

	}

	// Setup public socket
	int pub_sock = socket(AF_INET, SOCK_DGRAM, 0);
	
	if(pub_sock < 0)
	{

		error("ERROR: socket()");
	}

	struct sockaddr_in pub_addr;
	bzero(&pub_addr, sizeof(pub_addr));
	pub_addr.sin_family = AF_INET;					// IPv4
	pub_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	pub_addr.sin_port = htons(PUB_PORT);
	
	if(bind(pub_sock, (SA*) &pub_addr, sizeof(pub_addr)) < 0)
	{
		error("Error: bind()");
	}
	
	// Setup private socket
	int prv_sock = socket(AF_INET, SOCK_DGRAM, 0);
	
	if(prv_sock < 0)
	{
		error("ERROR: socket()");
	}

	struct sockaddr_in prv_addr;
	bzero(&prv_addr, sizeof(prv_addr));
	prv_addr.sin_family = AF_INET;					// IPv4
	prv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	prv_addr.sin_port = htons(PRV_PORT);
	
	if(bind(prv_sock, (SA*) &prv_addr, sizeof(prv_addr)) < 0)
	{
		error("Error: bind()");
	}
	
	// Server loop
	int ret;
	int max_fd = max(pub_sock, prv_sock) + 1;

	fd_set read_set;
	FD_ZERO(&read_set);

	char msg[MAX_LINE];

	for(;;)
	{
		FD_SET(pub_sock, &read_set);
		FD_SET(prv_sock, &read_set);

		if(select(max_fd, &read_set, NULL, NULL, NULL) < 0)
		{
			error("ERROR: select()");
		}

		if(FD_ISSET(pub_sock, &read_set))
		{
			printf("pub\n");
			read(pub_sock, msg, MAX_LINE);

			// place packet in a buffer
		}

		if(FD_ISSET(prv_sock, &read_set))
		{
			printf("prv\n");
			read(prv_sock, msg, MAX_LINE);
		
			// data is fragmented, send frament to remote network address			
			//sendto(pub_sock, "", 0, 0, (SA*) &rem_addr, sizeof(rem_addr));

			// if contiguous and checksums match, send the packet to the local network address	
			//sendto(pub_sock, "", 0, 0, (SA*) &loc_addr, sizeof(loc_addr));
		}
	}			
}

