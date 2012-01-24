/* playback.c					By : deneb					last modif : 17/01/12	   \
\_____________________________________________________________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <alsa/asoundlib.h>
#include <pthread.h>

#include "utils.h"
#include "client_serveur.h"
#include "son.h"
#include "playback.h"


void* boucle_playback(void* arg)
{
	s_par_thread param = *((s_par_thread*)arg);
	
	int rc=EXIT_SUCCESS, index=0;
	s_MUV packetR[TAILLE_LISTE];
	
	
	if(initSon(PLAYBACK, &(param.val), &(param.frames)) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	
	for(int i=0;i<TAILLE_LISTE;i++)
	{
		packetR[i].id=0;
		//packetR[i].size = param.frames * 4; /* 2 bytes/sample, 2 channels */
		//packetR[i].data = malloc(packetR[i].size);
	}
	
	//pthread_cleanup_push(clean_playback, packetR);
	
	while (1) // boucle principale
	{	
       
		#ifdef SERVEUR
			rc = rcv_serveur(param.sock, &(param.client), packetR + (index%TAILLE_LISTE) );
		#endif
		#ifdef CLIENT
			rc = rcv_client(param.sock, packetR + (index%TAILLE_LISTE) );
		#endif
		
		if(rc!=EXIT_FAILURE)
		{
			//#ifdef CLIENT // DEBUG
			playback(packetR[index%TAILLE_LISTE].data);
			//playback(packetR->data);
			//#endif
			//memset(packetR[index%TAILLE_LISTE].data, 0, packetR[index%TAILLE_LISTE].size);
			index++;
		}
		else
			fprintf(stderr, "[E] Receiving error\n");
	}
	
	return NULL;
}

