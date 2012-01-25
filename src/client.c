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


#define LG_BUFFER	1024


void* client_tcp_connexion (void* arg)
{
	s_par_thread param = *((s_par_thread*)arg);

	char               buffer [LG_BUFFER];
	int                nb_lus;
	
	/*sock = sock_tcp();

	set_tcp_address(& adresse, port, host);*/

	if (connect (param.sock_tcp, (struct sockaddr *) & param.serveur, (socklen_t) sizeof (struct sockaddr_in)) < 0) {
		perror ("connect");
		exit(EXIT_FAILURE);
	}
	setvbuf (stdout, NULL, _IONBF, 0);
	while (1) {
		if ((nb_lus = read (param.sock_tcp, buffer, LG_BUFFER)) == 0)
			break;
		if (nb_lus < 0) {
			perror ("read");
			break;
		}
		write (STDOUT_FILENO, buffer, nb_lus);
	}

	return NULL;
}
