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
	int nb_lus;
	struct sockaddr_in adresse;
	char buffer[LG_BUFFER];
	int sock = openSock(argc, argv, & adresse);
	
	if (bind(sock, (struct sockaddr *) &adresse, sizeof(struct sockaddr_in)) < 0) {
		perror("bind");
		exit(EXIT_FAILURE);
	}
	
	while (1) 
	{
		if ((nb_lus = read(STDIN_FILENO, buffer, LG_BUFFER)) == 0)
			break;

		if (nb_lus < 0) 
		{
			perror("read");
			break;
		}
		sendto(sock, buffer, nb_lus, 0,
			(struct sockaddr *) & adresse, sizeof (struct sockaddr_in));
	}
	
	return EXIT_SUCCESS;
}

