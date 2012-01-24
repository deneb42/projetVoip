/* playback.c					By : deneb					last modif : 17/01/12	   \
\_____________________________________________________________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <alsa/asoundlib.h>
#include <pthread.h>

#include "utils.h"
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
		packetR[i].id=0;
	
	while (1) // boucle principale
	{	
		#ifdef SERVEUR
			rc = receiveMUV(param.sock, &(param.client), packetR + index);
		#endif
		#ifdef CLIENT
			rc = receiveMUV(param.sock, NULL, packetR + index);
		#endif
		
		if(rc!=EXIT_FAILURE)
		{
			playback(packetR[index].data);
			index = (index+1)%TAILLE_LISTE;
		}
	}
	
	return NULL;
}

int receiveMUV(int sock, struct sockaddr_in * source, s_MUV* packetR)
{
	int sockSize = sizeof(struct sockaddr_in);
	int nbR;

	if ((nbR = recvfrom(sock, packetR, sizeof(s_MUV), MSG_DONTWAIT, (struct sockaddr *) source, (socklen_t*)&sockSize )) > 0)
	{
		printf("[I] Packet %lu (%d bytes) : received\n", packetR->id, nbR);
		return EXIT_SUCCESS;
	}
		
	fprintf(stderr, "[E] Sending error\n");
	return EXIT_FAILURE;
}
