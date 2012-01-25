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
	s_par_thread param = *((s_par_thread*)arg);
	s_MUV packetS;
	int rc;
	
	if(initSon(CAPTURE, &(param.val), &(param.frames)) == EXIT_FAILURE)
		exit(EXIT_FAILURE);

	packetS.id=0;

	while(1) // boucle principale
	{	
		capture(packetS.data);
		
		//#ifdef SERVEUR
			rc = sendMUV(param.sock, /*&(param.client)*/ &(param.destination), &packetS);
		/*#endif
		#ifdef CLIENT
			rc = sendMUV(param.sock, &(param.serveur), &packetS);
		#endif*/
		if(rc != EXIT_FAILURE)
		packetS.id++;
	}
	
	return NULL;
}

int sendMUV(int sock, struct sockaddr_in * destination, s_MUV* packetS)
{
	int nbS;

	if((nbS = sendto(sock, packetS, sizeof(s_MUV), 0, (struct sockaddr *) destination, sizeof(struct sockaddr_in) )) > 0)
	{
		printf("[I] Packet %lu (%d bytes) : sent\n", packetS->id, nbS);
		return EXIT_SUCCESS;
	}
		
	fprintf(stderr, "[E] Packet %lu : error, %d bytes sent\n", packetS->id, nbS);
	return EXIT_FAILURE;
}
