/* projetVoip					By : deneb					last modif : 09/12/11	   \
\_____________________________________________________________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <alsa/asoundlib.h>
#include <signal.h>

#include "utils.h"
#include "socket_utils.h"
#include "client_serveur.h"
#include "son.h"

char continuer;

// selection de l'adresse a amméliorer

// voir a utiliser directement une string d'ou on pourrait getID, get...

void fnexit(int i)
{
	continuer = 0;
}


int main (int argc, char *argv[])
{
	// socket
	struct sockaddr_in serveur;
	int sock;
	s_MUV packetR[TAILLE_LISTE], packetS;
	int index = 0;
	
	// son
	unsigned int val = 11025;
	snd_pcm_uframes_t frames = 32;
	
	// autres
	char *address, *port;
	int rc;
	
	// Fin des variables

	
	// Initialisation --------------------------------------------------
	continuer = 1;
	signal(SIGINT, fnexit); // pour une sortie propre du programme
	
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
	packetS.id=0;
	packetS.size = frames * 4; /* 2 bytes/sample, 2 channels */
	packetS.data = malloc(packetS.size);
	// Fin initialisation-----------------------------------------------
	
	
	while (continuer) // boucle principale
	{	
		capture(packetS.data);
			
		#ifdef SERVEUR
			rc = traitement_serveur(sock, &packetS, packetR);
		#endif
		#ifdef CLIENT
			rc = traitement_client(sock, &serveur, &packetS, packetR);
        #endif
        
        if(rc == EXIT_SUCCESS)
		{
			packetS.id++;
			#ifdef CLIENT // DEBUG
			playback(packetR[index%TAILLE_LISTE].data);
			//playback(packetR->data);
			#endif
			memset(packetR[index%TAILLE_LISTE].data, 0, packetR[index%TAILLE_LISTE].size);
			index++;
		}
		else
			fprintf(stderr, "Sending/ receiving error\n");
	}


	printf("Desallocation des handles\n");
	closeSon();
	
	printf("Desallocation des buffers\n");
	for(int i=0;i<TAILLE_LISTE;i++)
		free(packetR[i].data);
	free(packetS.data);
	
	printf("Fin\n");
	return EXIT_SUCCESS;
}
