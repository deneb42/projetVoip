#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "header.h"

int sock_udp()
{
	int sock;

	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
	{
		fprintf(stderr, "sock_udp : address and port must not be NULL");
		exit(EXIT_FAILURE);
	}
	
	return sock;
}
