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
	int init = 1 ;
	struct sockaddr_in adresse;
	char buffer[LG_BUFFER];
	int nb_lus;
	int sock = openSock(argc, argv, &adresse);
	//int sock2 = openSock(argc, argv, &adresse);
	
	if (bind(sock, (struct sockaddr *) &adresse, sizeof(struct sockaddr_in)) < 0) 
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}
	
	while (1) 
	{
		if ((nb_lus = recv(sock, buffer, LG_BUFFER, 0)) == 0)
			break;
				
		if (nb_lus < 0) {
			perror("read");
			break;
		}
		
		write(STDOUT_FILENO, buffer, nb_lus);
		
		//sendto(sock, buffer, nb_lus, 0,
		//	(struct sockaddr *) & adresse, sizeof (struct sockaddr_in));
		// ne marche pas surement car on est sur la meme machine
	}
	
	return EXIT_SUCCESS;
}

