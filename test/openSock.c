#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "header.h"

int openSock(int argc, char *argv[], struct sockaddr_in * adresse)
{
	int sock;

	if (lecture_arguments(argc, argv, adresse, "udp") < 0)
		exit(EXIT_FAILURE);
	
	adresse->sin_family = AF_INET;
	
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}
	
	return sock;
}
