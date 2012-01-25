/* capture.c					By : deneb					last modif : 17/01/12	   \
\_____________________________________________________________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <alsa/asoundlib.h>
#include <pthread.h>

#include "utils.h"
#include "son.h"
#include "capture.h"

void * boucle_capture(void *arg)
{
	s_par_thread param, tmp = *((s_par_thread*)arg);
	s_MUV packetS;
	int rc;
	
	param.serveur = tmp.serveur;
	param.client = tmp.client;
	param.sock_udp = tmp.sock_udp;
	
	param.val = tmp.val;
	param.frames = tmp.frames; // nécéssaire ? je ne pense pas 

	
	if(initSon(CAPTURE, &(param.val), &(param.frames)) == EXIT_FAILURE)
		exit(EXIT_FAILURE);

	packetS.id=0;

	while(1) // boucle principale
	{	
		capture(packetS.data);
		
		#ifdef SERVEUR
<<<<<<< HEAD
			sendn(param.sock_udp, &(param.client), &packetS);
		#endif
		#ifdef CLIENT
			sendn(param.sock_udp, &(param.serveur), &packetS);
=======
			rc = sendMUV(param.sock, &(param.client), &packetS);
		#endif
		#ifdef CLIENT
			rc = sendMUV(param.sock, &(param.serveur), &packetS);
>>>>>>> eb6dbf288b25958cff4358772b2da93b2d677f90
        #endif
        if(rc != EXIT_FAILURE)
			packetS.id++;
	}
	
	return NULL;
}

<<<<<<< HEAD
int sendn(int sock, struct sockaddr_in * destination, s_MUV* packetS)
=======
int sendMUV(int sock, struct sockaddr_in * destination, s_MUV* packetS)
>>>>>>> eb6dbf288b25958cff4358772b2da93b2d677f90
{
	int nbS;

	if((nbS = sendto(sock, packetS, sizeof(s_MUV), 0, (struct sockaddr *) destination, sizeof(struct sockaddr_in) )) > 0)
	{
		printf("[I] Packet %lu (%d bytes) : sent\n", packetS->id, nbS);
<<<<<<< HEAD
		packetS->id++;
=======
>>>>>>> eb6dbf288b25958cff4358772b2da93b2d677f90
		return EXIT_SUCCESS;
	}
		
	fprintf(stderr, "[E] Packet %lu : error, %d bytes sent\n", packetS->id, nbS);
	perror("fuck");
	return EXIT_FAILURE;
}
