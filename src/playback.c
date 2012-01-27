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
	int rc, index;
	s_voip packetR[TAILLE_LISTE];
	s_par_thread param = *((s_par_thread*)arg);
	
	rc=EXIT_SUCCESS;
	index=0;
	
	if(initSon(PLAYBACK, &(param.val), &(param.frames)) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	
	for(int i=0;i<TAILLE_LISTE;i++)
		packetR[i].id=0;
	
	while (1) // boucle principale
	{	
		rc = receive_voip(param.sock, packetR + index);

		if(rc!=EXIT_FAILURE)
		{
			playback(packetR[index].data);
			index = (index+1)%TAILLE_LISTE;
		}
	}
	
	return NULL;
}

int receive_voip(int sock, s_voip* packetR)
{
	int nbR;

	if ((nbR = recv(sock, packetR, sizeof(s_voip), MSG_DONTWAIT)) > 0)
	{
		printf("[I] Packet %lu (%d bytes) : received\n", packetR->id, nbR);
		return EXIT_SUCCESS;
	}
		
	fprintf(stderr, "[E] Receiving error\n");
	return EXIT_FAILURE;
}
