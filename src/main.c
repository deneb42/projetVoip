/* projetVoip					By : deneb					last modif : 09/12/11	   \
\_____________________________________________________________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <alsa/asoundlib.h>
#include <signal.h>
#include <pthread.h>

#include "utils.h"
#include "socket_utils.h"
#include "client_serveur.h"
#include "son.h"

#include "capture.h"
#include "playback.h"

int init_connection(char* paradd, char* parport, pthread_t* threads, s_par_thread* param)
{
	char *address, *port;
	int sock_tcp, sockSize;

	address = paradd;
	port = parport; // need verification de la véracité des paramètres
	
	sock_tcp = sock_tcp();
	
	#ifdef CLIENT
		if(set_tcp_address(&(param->destination), port, address) == EXIT_FAILURE)
			return EXIT_FAILURE;
	#endif
	#ifdef SERVEUR
		if(set_tcp_address(&(param->destination), port, NULL) == EXIT_FAILURE)
			return EXIT_FAILURE;

		if (bind(sock_tcp, (struct sockaddr *) &(param->destination), sizeof(struct sockaddr_in)) < 0) 
		{
			perror("bind");
			return(EXIT_FAILURE);
		}

	#endif
	printf("[I] demande de connec a l'adresse IP = %s, Port = %u \n", inet_ntoa(param->serveur.sin_addr), ntohs(param->serveur.sin_port));

	#ifdef CLIENT
		if (connect (sock_tcp, (struct sockaddr *) & param.serveur, /*(socklen_t)*/sockSize)) < 0) {
			perror ("connect");
			return(EXIT_FAILURE);
		}
	#endif
	#ifdef SERVEUR
		if(accept(sock_tcp, (struct sockaddr *) & param.destination, (socklen_t *) sockSize) < 0) 
		{
			perror ("accept");
			exit(EXIT_FAILURE);
		}

		printf("[I] Connection a l'adresse IP = %s, Port = %u \n", inet_ntoa(param.client.sin_addr), ntohs(param.client.sin_port));
	#endif
	
	shutdown(sock_tcp);
	
	launch(NULL, NULL, threads, param);
	
	return EXIT_SUCCESS;
}

