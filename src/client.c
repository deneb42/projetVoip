/* client.c						By : deneb					last modif : 09/12/11	   \
\_____________________________________________________________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "utils.h"


int traitement_client(int sock, struct sockaddr_in * serveur, s_MUV* packetS, s_MUV* packetR)
{
	int nbS, nbR;
	char strS[((const int)packetS->size+sizeof(long))], strR[(packetR->size+sizeof(long))];
	
	
	MUVtoStr(packetS, strS);

	if((nbS = sendto(sock, strS, packetS->size+sizeof(long), 0, (struct sockaddr *) serveur, sizeof(struct sockaddr_in) )) > 0)
		printf("envoye paquet num %lu de : %d octets\n", packetS->id, nbS);
	
	if ((nbR = recv(sock, strR, packetR->size+sizeof(long), MSG_DONTWAIT)) <= 0)
		return EXIT_FAILURE;
	
	strtoMUV(packetR+(getIndex(strR)%TAILLE_LISTE), strR);
	
	printf("recu paquet num %lu de : %d octets\n", packetR->id, nbR);
	
	return EXIT_SUCCESS;
}
