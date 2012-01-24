/* serveur.c					By : deneb					last modif : 09/12/11	   \
\_____________________________________________________________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "utils.h"


int snd_serveur(int sock, struct sockaddr_in * client, s_MUV* packetS)
{
	int nbS;
	//char strS[((const int)packetS->size+sizeof(long))];
	
	
	//MUVtoStr(packetS, strS);

	//if((nbS = sendto(sock, strS, packetS->size+sizeof(long), 0, (struct sockaddr *) &client, sizeof(struct sockaddr_in) )) > 0)
	if((nbS = sendto(sock, packetS, sizeof(s_MUV), 0, (struct sockaddr *) &client, sizeof(struct sockaddr_in) )) > 0)
		printf("envoye paquet num %lu de : %d octets\n", packetS->id, nbS);
	else 
		printf("berf1\n");

	return EXIT_SUCCESS;
}

int rcv_serveur(int sock, struct sockaddr_in * client, s_MUV* packetR)
{
	int sockSize = sizeof(struct sockaddr_in);
	
	int nbR;
	//char strR[(packetR->size+sizeof(long))];
	
	//if ((nbR = recvfrom(sock, strR, packetR->size+sizeof(long), 0, (struct sockaddr *) client, (socklen_t*)&sockSize )) <= 0)
	if ((nbR = recvfrom(sock, packetR, sizeof(s_MUV), MSG_DONTWAIT, (struct sockaddr *) client, (socklen_t*)&sockSize )) <= 0)
		return EXIT_FAILURE;
	else 
		printf("berf2\n");
	//strtoMUV(packetR, strR);
	
	printf("recu paquet num %lu de : %d octets\n", packetR->id, nbR);
	
	return EXIT_SUCCESS;
}
