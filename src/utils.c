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

//problème : l'adresse du client n'est pas gardé entre récéption et envoi

// selection de l'adresse a amméliorer

int launch (char* paradd, char* parport, pthread_t* threads, s_par_thread* param)
{
	char *address, *port;
	
<<<<<<< HEAD
	return id;
}

/*int lecture_arguments (int argc, char * argv [], char** address, char** port) // DEPRECATED
{ // reads the arguments and put them in the appropriate strings. if not given, initialize to default values 

	char * liste_options = "a:p:d:h";
	int option;
	char* ad = "localhost";
	char* po = "2000";
=======
	// param contient les variables nécéssaires dans les threads pour le son et les socket
>>>>>>> eb6dbf288b25958cff4358772b2da93b2d677f90
	
	// pour le son
	param->val = 11025;
	param->frames = SIZE_PACKET / 4; // 2 bytes par channel, 2 channels
	
	address = paradd;
	port = parport; // need verification de la véracité des paramètres
	
	param->sock = sock_udp();
	
	#ifdef CLIENT
		set_udp_address(&(param->serveur), port, address);
	#endif
	#ifdef SERVEUR
		set_udp_address(&(param->serveur), port, NULL);
		if (bind(param->sock, (struct sockaddr *) &(param->serveur), sizeof(struct sockaddr_in)) < 0) 
		{
			perror("bind");
			exit(EXIT_FAILURE);
		}
	#endif
	
	printf("[I] Connection a l'adresse IP = %s, Port = %u \n", inet_ntoa(param->serveur.sin_addr), ntohs(param->serveur.sin_port));
	// Fin sockets
	
	#ifdef CLIENT
	pthread_create(threads + CAPTURE, 0, boucle_capture, param);
	#endif
	#ifdef SERVEUR
	pthread_create(threads + PLAYBACK, 0, boucle_playback, param);
	#endif
	return EXIT_SUCCESS;
}
