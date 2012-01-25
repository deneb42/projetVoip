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
#include "son.h"
#include "capture.h"
#include "playback.h"


int launch (char* paradd, char* parport, pthread_t* threads, s_par_thread* param)
{
	char *address, *port;

	// param contient les variables nécéssaires dans les threads pour le son et les socket
	
	// pour le son
	param->val = 11025;
	param->frames = SIZE_PACKET / 4; // 2 bytes par channel, 2 channels
	
	//address = paradd;
	//port = parport; // need verification de la véracité des paramètres
	
	param->sock = sock_udp();
	
	#ifdef CLIENT
		//set_udp_address(&(param->serveur), port, address);
	#endif
	#ifdef SERVEUR
		//set_udp_address(&(param->serveur), port, NULL);
		if (bind(param->sock, (struct sockaddr *) &(param->destination), sizeof(struct sockaddr_in)) < 0) 
		{
			perror("bind");
			exit(EXIT_FAILURE);
		}
	#endif
	
	printf("[I] Connection a l'adresse IP = %s, Port = %u \n", inet_ntoa(param->destination.sin_addr), ntohs(param->destination.sin_port));
	// Fin sockets
	
	#ifdef CLIENT
	pthread_create(threads + CAPTURE, 0, boucle_capture, param);
	#endif
	#ifdef SERVEUR
	pthread_create(threads + PLAYBACK, 0, boucle_playback, param);
	#endif
	return EXIT_SUCCESS;
}
