#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <alsa/asoundlib.h>

#include "utils.h"
#include "socket_utils.h"
#include "son.h"

#define TAILLE_LISTE 2

// NE PAS UTILISER LOCALHOST COMME ADRESSE DU SERVEUR ! IL FAUT UTILISER L'ADRESSE DE SOUS RÉSEAU

// /!\ il y a un écho
// voir a utiliser directement une string d'ou on pourrait getID, get...

int traitement_client(int sock, struct sockaddr_in * serveur, void* element, int *size);
int traitement_serveur(int sock, void* element, int *size);

int main (int argc, char *argv[])
{
	// socket
	struct sockaddr_in serveur;
	int sock;
	s_MUV packetR[TAILLE_LISTE], packetS;
	
	// son
	snd_pcm_hw_params_t *params[2];
	snd_pcm_t *handle[2];
	unsigned int val[2] = {11025, 11025};
	snd_pcm_uframes_t frames[2] = {32, 32};
	int size[2] = {128, 128}; /* 2 bytes/sample, 2 channels */
	int dir[2];
	
	// autres
	char *address, *port;
	int rc;
	
	// Fin des variables
	
	
	// Initialisation --------------------------------------------------
	if (lecture_arguments(argc, argv, &address, &port) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	
	sock = sock_udp();
	set_udp_address(&serveur, port, address);
	
	#ifdef SERVEUR
		if (bind(sock, (struct sockaddr *) &serveur, sizeof(struct sockaddr_in)) < 0) 
		{
			perror("bind");
			exit(EXIT_FAILURE);
		}
	#endif
	
	if(initSon('c', handle, params, val, dir, frames) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	if(initSon('p', handle+1, params+1, val+1, dir+1, frames+1) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
		
	for(int i=0;i<TAILLE_LISTE;i++)
	{
		packetR[i].id=0;
		packetR[i].data = malloc(size[1]);
		packetR[i].size = frames[i] * 4; /* 2 bytes/sample, 2 channels */
	}
	//packetS.id=0;
	//packetS.data = malloc(size[0]);
	
	// Fin initialisation-----------------------------------------------
	
	
	while (1) // boucle principale
	{
		//capture(handle[0], 
		rc = snd_pcm_readi(handle[0], packetR[0].data, frames[0]);
		if (rc == -EPIPE) // EPIPE means overrun
		{
			fprintf(stderr, "overrun occurred\n");
			snd_pcm_prepare(handle[0]);
		}
		else if (rc < 0)
			fprintf(stderr, "error from read: %s\n", snd_strerror(rc));
		else if (rc != (int)frames[1])
			fprintf(stderr, "short read, read %d frames\n", rc);
		
		#ifdef SERVEUR
			rc = traitement_serveur(sock, packetR, size);
		#endif
		#ifdef CLIENT
			rc = traitement_client(sock, &serveur, packetR, size);
        #endif
        
        if(rc == EXIT_SUCCESS)
		{
			rc = snd_pcm_writei(handle[1], packetR[1].data, frames[1]);
			
			if (rc == -EPIPE) // EPIPE means underrun
			{
				fprintf(stderr, "underrun occurred\n");
				snd_pcm_prepare(handle[1]);
			} 
			else if (rc < 0) 
				fprintf(stderr, "error from writei: %s\n", snd_strerror(rc));
			else if (rc != (int)frames[1]) 
				fprintf(stderr, "short write, write %d frames\n", rc);

			(packetR[0].id)++;
		}
		else
			fprintf(stderr, "Sending/ receiving error\n");
	}
	
	for(int i=0;i<2;i++) // a revoir
	{
		snd_pcm_drain(handle[i]);
		snd_pcm_close(handle[i]);
		//free(buffer[i]);
	}
	
	return EXIT_SUCCESS;
}
