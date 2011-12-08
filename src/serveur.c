/* serveur.c					By : deneb					last modif : 22/11/11	   \
\_____________________________________________________________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "utils.h"

int traitement_serveur(int sock, s_MUV* packet, int* size)
{
	int nb_lus, nb_sent;
	int sockSize = sizeof(struct sockaddr_in);
	struct sockaddr_in client;
	char str0[200], str1[200];
	
	if ((nb_lus = recvfrom(sock, str1, packet[1].size+sizeof(long), 0, (struct sockaddr *) &client, (socklen_t*)&sockSize)) <= 0)
		return EXIT_FAILURE;
	
	strtoMUV(packet+1, str1);
	
	printf("recu paquet num %lu de : %d octets\n", packet[1].id, nb_lus);
	
	
	MUVtoStr(packet, str0);

	nb_sent = sendto(sock, str0, packet[0].size+sizeof(long), 0, (struct sockaddr *) &client, sockSize);
	
	printf("envoye paquet num %lu de : %d octets\n", packet[0].id, nb_sent);
	
	return EXIT_SUCCESS;
}
