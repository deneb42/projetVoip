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
	struct sockaddr_in recepteur, emeteur;
	char buffer[LG_BUFFER];
	int nb_lus;
	int sock = openSock(argc, argv, &recepteur);
	int sockSize = sizeof(struct sockaddr_in);
	char *address, *port;
	
	if (lecture_arguments(argc, argv, &adress, &port) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	
	set_udp_address(recepteur, address, port);
	
	if (bind(sock, (struct sockaddr *) &recepteur, sizeof(struct sockaddr_in)) < 0) 
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}
	
	while (1) 
	{
		if ((nb_lus = recvfrom(sock, buffer, LG_BUFFER, 0, (struct sockaddr *) &emeteur, &sockSize)) == 0)
			break;
				
		if (nb_lus < 0) {
			perror("read");
			break;
		}
		
		write(STDOUT_FILENO, buffer, nb_lus);
		
		sendto(sock, buffer, nb_lus, 0, (struct sockaddr *) &emeteur, sockSize);
	}
	
	return EXIT_SUCCESS;
}

