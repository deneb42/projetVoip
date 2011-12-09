/* projetVoip					By : deneb					last modif : 09/12/11	   \
\_____________________________________________________________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <alsa/asoundlib.h>

#include "utils.h"
#include "socket_utils.h"
#include "client_serveur.h"
#include "son.h"

#define TAILLE_LISTE 2

// selection de l'adresse a amméliorer

// /!\ il y a un écho // surement une string ou une structure qui n'est pas réinitialisée

// voir a utiliser directement une string d'ou on pourrait getID, get...

int main (int argc, char *argv[])
{
	// socket
	struct sockaddr_in serveur;
	int sock;
	s_MUV packetR[TAILLE_LISTE];//, packetS;
	
	// son
	unsigned int val = 11025;
	snd_pcm_uframes_t frames = 32;
	
	// autres
	char *address, *port;
	int rc;
	
	// Fin des variables
	
	
	// Initialisation --------------------------------------------------
	if (lecture_arguments(argc, argv, &address, &port) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	
	sock = sock_udp();
	
	#ifdef CLIENT
		set_udp_address(&serveur, port, address);
	#endif
	#ifdef SERVEUR
		set_udp_address(&serveur, port, NULL);
		if (bind(sock, (struct sockaddr *) &serveur, sizeof(struct sockaddr_in)) < 0) 
		{
			perror("bind");
			exit(EXIT_FAILURE);
		}
	#endif
	
	printf("Connection a l'adresse IP = %s, Port = %u \n", inet_ntoa(serveur.sin_addr), ntohs(serveur.sin_port));
	// Fin sockets
	
	if(initSon(CAPTURE, &val, &frames) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	if(initSon(PLAYBACK, &val, &frames) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	// Fin son
	
	for(int i=0;i<TAILLE_LISTE;i++)
	{
		packetR[i].id=0;
		packetR[i].size = frames * 4; /* 2 bytes/sample, 2 channels */
		packetR[i].data = malloc(packetR[i].size);
	}
	//packetS.id=0;
	//packetS.data = malloc(size[0]);
	
	// Fin initialisation-----------------------------------------------
	
	
	while (1) // boucle principale
	{
		capture(packetR[0].data);
			
		#ifdef SERVEUR
			rc = traitement_serveur(sock, packetR);
		#endif
		#ifdef CLIENT
			rc = traitement_client(sock, &serveur, packetR);
        #endif
        
        if(rc == EXIT_SUCCESS)
		{
			(packetR[0].id)++;
			playback(packetR[1].data);
		}
		else
			fprintf(stderr, "Sending/ receiving error\n");
	}


	closeSon();
	
	return EXIT_SUCCESS;
}
