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
	int rc;
	s_voip packetS;	
	s_par_thread param = *((s_par_thread*)arg);
	
	if(initSon(CAPTURE, &(param.val), &(param.frames)) == EXIT_FAILURE)
		exit(EXIT_FAILURE);

	packetS.id=0;

	while(1) // boucle principale
	{	
		capture(packetS.data);
		
		rc = send_voip(param.sock, &(param.destination), &packetS);
		
		if(rc != EXIT_FAILURE)
		packetS.id++;
	}
	
	return NULL;
}

int send_voip(int sock, struct sockaddr_in * destination, s_voip* packetS)
{
	int nbS;

	if((nbS = sendto(sock, packetS, sizeof(s_voip), 0, (struct sockaddr *) destination, sizeof(struct sockaddr_in) )) > 0)
	{
		//printf("[I] Packet %lu (%d bytes) : sent\n", packetS->id, nbS);
		return EXIT_SUCCESS;
	}
		
	//fprintf(stderr, "[E] Packet %lu : error, %d bytes sent\n", packetS->id, nbS);
	return EXIT_FAILURE;
}
