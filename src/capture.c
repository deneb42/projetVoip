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


void clean_capture(void *arg)
{
	closeSon(CAPTURE);
	
	printf("[I] Desallocation du buffers d'envoi\n");
	free(((s_MUV*)arg)->data);
}

void * boucle_capture(void *arg)
{
	s_par_thread param = *((s_par_thread*)arg);
	
	s_MUV packetS;
	int rc=EXIT_SUCCESS;
	
	if(initSon(CAPTURE, &(param.val), &(param.frames)) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	
	packetS.id=0;
	packetS.size = param.frames * 4; /* 2 bytes/sample, 2 channels */
	packetS.data = malloc(packetS.size);
	
	pthread_cleanup_push(clean_capture,&packetS);
	
	while(1) // boucle principale
	{	
		capture(packetS.data);
			
		#ifdef SERVEUR
			rc = snd_serveur(param.sock, &(param.client), &packetS);
		#endif
		#ifdef CLIENT
			rc = snd_client(param.sock, &(param.serveur), &packetS);
        #endif
        
        if(rc != EXIT_FAILURE)
			packetS.id++;
		else
			fprintf(stderr, "[E] Sending error\n");
	}
	return EXIT_SUCCESS;
}
