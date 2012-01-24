/* capture.c					By : deneb					last modif : 17/01/12	   \
\_____________________________________________________________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <alsa/asoundlib.h>
#include <pthread.h>

#include "utils.h"
#include "client_serveur.h"
#include "son.h"
#include "capture.h"

void * boucle_capture(void *arg)
{
	s_par_thread param, tmp = *((s_par_thread*)arg);
	s_MUV packetS;
	
	param.serveur = tmp.serveur;
	param.client = tmp.client;
	param.sock = tmp.sock;
	
	param.val = tmp.val;
	param.frames = tmp.frames;

	
	if(initSon(CAPTURE, &(param.val), &(param.frames)) == EXIT_FAILURE)
		exit(EXIT_FAILURE);

	packetS.id=0;

	while(1) // boucle principale
	{	
		capture(packetS.data);
		
		#ifdef SERVEUR
			send(param.sock, &(param.client), &packetS);
		#endif
		#ifdef CLIENT
			send(param.sock, &(param.serveur), &packetS);
        #endif
	}
	
	return NULL;
}

int send(int sock, struct sockaddr_in * destination, s_MUV* packetS)
{
	int nbS;

	if((nbS = sendto(sock, packetS, sizeof(s_MUV), 0, (struct sockaddr *) &destination, sizeof(struct sockaddr_in) )) > 0)
	{
		printf("[I] Packet %lu (%d bytes) : sent\n", packetS->id, nbS);
		packetS.id++;
		return EXIT_SUCCESS;
	}
		
	fprintf(stderr, "[E] Sending error\n");
	return EXIT_FAILURE;
}
