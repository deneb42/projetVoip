#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "header.h"

#define LG_BUFFER 1024

int main (int argc, char *argv[])
{
	struct sockaddr_in adresse;
	char buffer[LG_BUFFER];
	int nb_lus;
	int sock = openSock(argc, argv, &adresse);
	
	if (bind(sock, (struct sockaddr *) &adresse, sizeof(struct sockaddr_in)) < 0) {
		perror("bind");
		exit(EXIT_FAILURE);
	}
	
	//setvbuf(stdout, NULL, _IONBF, 0);
	
	while (1) 
	{
		if ((nb_lus = recv(sock, buffer, LG_BUFFER, 0)) == 0)
			break;
			
		if (nb_lus < 0) {
			perror("read");
			break;
		}
		
		write(STDOUT_FILENO, buffer, nb_lus);
	}
	
	return EXIT_SUCCESS;
}

