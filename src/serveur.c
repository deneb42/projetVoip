/* serveur.c					By : deneb					last modif : 09/12/11	   \
\_____________________________________________________________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "utils.h"
#include "socket_utils.h"
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/socket.h>

void* server_tcp_connexion (void* arg)
{
	int sockSize;
	s_par_thread param = *((s_par_thread*)arg);
	

	listen (param.sock_tcp, 5);

	if(accept(param.sock_tcp, (struct sockaddr *) & param.destination, (socklen_t *) sockSize) < 0) 
	{
		perror ("accept");
		exit(EXIT_FAILURE);
	}

	printf("[I] Connection a l'adresse IP = %s, Port = %u \n", inet_ntoa(param.client.sin_addr), ntohs(param.client.sin_port));
	
  
	return NULL;
}
