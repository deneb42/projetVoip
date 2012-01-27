/* projetVoip					By : deneb					last modif : 09/12/11	   \
\_____________________________________________________________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "utils.h"
#include "socket_utils.h"
#include "capture.h"
#include "playback.h"
#include "son.h"

int launch (char* parport, pthread_t* threads, s_par_thread* param)
{ // param contient les variables nécéssaires dans les threads pour le son et les socket.

	param->val = 11025;
	param->frames = SIZE_PACKET / 4; // 2 bytes par channel, 2 channels
	
	param->sock = sock_udp();
	
	set_port(&param->source, parport);
	set_port(&param->destination, parport);

	#ifdef SERVEUR
		if (bind(param->sock, (struct sockaddr *) &(param->destination), sizeof(struct sockaddr_in)) < 0) 
		{
			perror("bind");
			exit(EXIT_FAILURE);
		}
	#endif
	
	printf("[I] Connecte en udp a l'adresse IP = %s, Port = %u \n", inet_ntoa(param->destination.sin_addr), ntohs(param->destination.sin_port));

	pthread_create(threads + CAPTURE, 0, boucle_capture, param);
	pthread_create(threads + PLAYBACK, 0, boucle_playback, param); // debug pour pas avoir d'echo
	
	return EXIT_SUCCESS;
}


int init_connection(char* paradd, char* parport, pthread_t* threads, s_par_thread* param)
{
	char *address, *port;
	int sockTcp;
	
	#ifdef SERVEUR
		int sock2;
		socklen_t sockSize = 0;
	#endif

	address = paradd;
	port = parport;
	
	sockTcp = sock_tcp();
	
	#ifdef CLIENT
	
		if(set_tcp_address(&(param->destination), port, address) == EXIT_FAILURE)
			return EXIT_FAILURE;
			
		if (connect (sockTcp, (struct sockaddr *) &param->destination, sizeof(struct sockaddr_in)) < 0) {
			perror ("connect");
			return(EXIT_FAILURE);
		}

	#endif
	#ifdef SERVEUR
		if(set_tcp_address(&(param->source), port, NULL) == EXIT_FAILURE)
			return EXIT_FAILURE;		

		if (bind(sockTcp, (struct sockaddr *) &(param->source), sizeof(struct sockaddr_in)) < 0) 
		{
			perror("bind");
			return(EXIT_FAILURE);
		}
		listen (sockTcp, 5);
		
		if((sock2 = accept(sockTcp, (struct sockaddr *)&(param->destination), &sockSize)) < 0) 
		{
			perror ("accept");
			exit(EXIT_FAILURE);
		}
		getpeername(sock2, (struct sockaddr*) &(param->destination), &sockSize);
		
		shutdown(sock2, SHUT_RDWR);
	#endif
	
	shutdown(sockTcp, SHUT_RDWR);

	launch(parport, threads, param);
	
	return EXIT_SUCCESS;
}
