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

//problème : l'adresse du client n'est pas gardé entre récéption et envoi


// selection de l'adresse a amméliorer

// voir a utiliser directement une string d'ou on pourrait getID, get...


int launch (char* paradd, pthread_t** threads)
{
	char *address, port[] = "2000";
	s_par_thread param;
	// param contient les variables nécéssaires dans les threads pour le son et les socket
	
	// pour le son
	param.val = 11025;
	param.frames = 32;
	
	//if (lecture_arguments(argc, argv, &address, &port) == EXIT_FAILURE)
	//	exit(EXIT_FAILURE);
	address = paradd;
	
	param.sock = sock_udp();
	
	#ifdef CLIENT
		set_udp_address(&(param.serveur), port, address);
	#endif
	#ifdef SERVEUR
		set_udp_address(&(param.serveur), port, NULL);
		if (bind(param.sock, (struct sockaddr *) &(param.serveur), sizeof(struct sockaddr_in)) < 0) 
		{
			perror("bind");
			exit(EXIT_FAILURE);
		}
	#endif
	
	printf("[I] Connection a l'adresse IP = %s, Port = %u \n", inet_ntoa(param.serveur.sin_addr), ntohs(param.serveur.sin_port));
	// Fin sockets
	
	pthread_create(threads[CAPTURE], 0, &boucle_capture, &param);
	pthread_create(threads[PLAYBACK], 0, &boucle_playback, &param);

	return EXIT_SUCCESS;
}

