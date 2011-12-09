/* serveur.c					By : deneb					last modif : 09/12/11	   \
\_____________________________________________________________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "utils.h"


int traitement_serveur(int sock, s_MUV* packet)
{
	int sockSize = sizeof(struct sockaddr_in);
	struct sockaddr_in client;
	
	int nb_lus, nb_sent;
	char str0[((const int)packet[0].size+sizeof(long))], str1[(packet[1].size+sizeof(long))];
	
	if ((nb_lus = recvfrom(sock, str1, packet[1].size+sizeof(long), 0, (struct sockaddr *) &client, (socklen_t*)&sockSize)) <= 0)
		return EXIT_FAILURE;
	
	strtoMUV(packet+1, str1);
	
	printf("recu paquet num %lu de : %d octets\n", packet[1].id, nb_lus);
	
	
	MUVtoStr(packet, str0);

	nb_sent = sendto(sock, str0, packet[0].size+sizeof(long), 0, (struct sockaddr *) &client, sockSize);
	
	printf("envoye paquet num %lu de : %d octets\n", packet[0].id, nb_sent);
	
	return EXIT_SUCCESS;
}
