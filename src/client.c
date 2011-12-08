/* client.c					By : deneb					last modif : 22/11/11		   \
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


int traitement_client(int sock, struct sockaddr_in * serveur, s_MUV* packet, int* size)
{
	int nb_lus, nb_sent;
	char str0[200], str1[200];
	
	
	MUVtoStr(packet, str0);

	nb_sent = sendto(sock, str0, packet[0].size+sizeof(long), 0, (struct sockaddr *) serveur, sizeof (struct sockaddr_in));
	
	printf("envoye paquet num %lu de : %d octets\n", packet[0].id, nb_sent);
	
	
	if ((nb_lus = recv(sock, str1, packet[1].size+sizeof(long), MSG_DONTWAIT)) <= 0)
		return EXIT_FAILURE;
		
	strtoMUV(packet+1, str1);
	
	printf("recu paquet num %lu de : %d octets\n", packet[1].id, nb_lus);
	
	return EXIT_SUCCESS;
}
