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
	printf("lalz\n");
	s_par_thread param = *((s_par_thread*)arg);
	printf("lulz\n");
	s_MUV packetS;
	int rc=EXIT_SUCCESS;
	
	if(initSon(CAPTURE, &(param.val), &(param.frames)) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	
	packetS.id=0;
	//packetS.size = param.frames * 4; /* 2 bytes/sample, 2 channels */
	//packetS.data = malloc(packetS.size);
	
	while(1) // boucle principale
	{	
		capture(packetS.data);
		printf("lol\n");
		#ifdef SERVEUR
			rc = snd_serveur(param.sock, &(param.client), &packetS);
		#endif
		#ifdef CLIENT
			rc = snd_client(param.sock, &(param.serveur), &packetS);
			pritnf("lulz\n");
        #endif
        
        if(rc != EXIT_FAILURE)
			packetS.id++;
		else
			fprintf(stderr, "[E] Sending error\n");
	}
	
	return NULL;
}
