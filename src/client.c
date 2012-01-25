/* client.c						By : deneb					last modif : 09/12/11	   \
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

void* client_tcp_connexion (void* arg)
{
	s_par_thread param = *((s_par_thread*)arg);

	int sockSize;
	
	/*sock = sock_tcp();

	set_tcp_address(& adresse, port, host);*/

	if (connect (param.sock_tcp, (struct sockaddr *) & param.serveur, /*(socklen_t)*/sockSize)) < 0) {
		perror ("connect");
		exit(EXIT_FAILURE);
	}
	
	return NULL;
}
