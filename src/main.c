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
	int sockTcp, sock2;
	socklen_t sockSize = 0;

	address = paradd;
	port = parport; // need verification de la véracité des paramètres
	
	sockTcp = sock_tcp();
	
	#ifdef CLIENT
	
		if(set_tcp_address(&(param->destination), port, address) == EXIT_FAILURE)
			return EXIT_FAILURE;
		
		printf("[I] demande de connec a l'adresse IP = %s, Port = %u \n", inet_ntoa(param->destination.sin_addr), ntohs(param->destination.sin_port));
		
		if (connect (sockTcp, (struct sockaddr *) &param->destination, sizeof(struct sockaddr_in)) < 0) {
			perror ("connect");
			return(EXIT_FAILURE);
		}
		getsockname(sockTcp, (struct sockaddr*) &(param->source), &sockSize);
		printf("[I] connec depuis l'adresse IP = %s, Port = %u \n", inet_ntoa(param->source.sin_addr), ntohs(param->source.sin_port));
	#endif
	#ifdef SERVEUR
		memset(&param->destination, 0, sizeof (struct sockaddr_in));
	
		if(set_tcp_address(&(param->source), port, NULL) == EXIT_FAILURE)
			return EXIT_FAILURE;

		if (bind(sockTcp, (struct sockaddr *) &(param->source), sizeof(struct sockaddr_in)) < 0) 
		{
			perror("bind");
			return(EXIT_FAILURE);
		}
		printf("[I] Attente de connec sur l'adresse IP = %s, Port = %u \n", inet_ntoa(param->source.sin_addr), ntohs(param->source.sin_port));
		listen (sockTcp, 5);

		if((sock2 = accept(sockTcp, (struct sockaddr *)&(param->destination), &sockSize)) < 0) 
		{
			perror ("accept");
			exit(EXIT_FAILURE);
		}
		getpeername(sock2, (struct sockaddr*) &(param->destination), &sockSize);
	printf("[I] connec depuis l'adresse IP = %s, Port = %u \n", inet_ntoa(param->destination.sin_addr), ntohs(param->destination.sin_port));
	#endif
	
	shutdown(sockTcp, SHUT_RDWR);
	
	//param->destination->sin_port = htons(port);
	printf("port : %s\n", port);
	launch(NULL, NULL, threads, param);
	
	return EXIT_SUCCESS;
}

