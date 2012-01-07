/* serveur.c					By : deneb					last modif : 09/12/11	   \
\_____________________________________________________________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "utils.h"


int traitement_serveur(int sock, s_MUV* packetS, s_MUV* packetR)
{
	int sockSize = sizeof(struct sockaddr_in);
	struct sockaddr_in client;
	
	int nbS, nbR;
	char strS[((const int)packetS->size+sizeof(long))], strR[(packetR->size+sizeof(long))];
	
	if ((nbR = recvfrom(sock, strR, packetR->size+sizeof(long), 0, (struct sockaddr *) &client, (socklen_t*)&sockSize )) <= 0)
		return EXIT_FAILURE;
	
	strtoMUV(packetR, strR);
	
	printf("recu paquet num %lu de : %d octets\n", packetR->id, nbR);
	
	
	MUVtoStr(packetS, strS);

	if((nbS = sendto(sock, strS, packetS->size+sizeof(long), 0, (struct sockaddr *) &client, sockSize)) > 0)
		printf("envoye paquet num %lu de : %d octets\n", packetS->id, nbS);

	return EXIT_SUCCESS;
}
