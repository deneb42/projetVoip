/* serveur.c					By : deneb					last modif : 22/11/11	   \
\_____________________________________________________________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#define LG_BUFFER 1024


void traitement_serveur(int sock)
{
	char buffer[LG_BUFFER];
	int nb_lus;
	int sockSize = sizeof(struct sockaddr_in);
	struct sockaddr_in client;
	
	if ((nb_lus = recvfrom(sock, buffer, LG_BUFFER, 0, (struct sockaddr *) &client, (socklen_t*)&sockSize)) == 0)
		return;
		
	if (nb_lus < 0) {
		perror("read");
		return;
	}
	
	write(STDOUT_FILENO, buffer, nb_lus);

	sendto(sock, buffer, nb_lus, 0, (struct sockaddr *) &client, sockSize);
}
