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


void traitement_serveur(int sock, void** element, int size)
{
	int nb_lus;
	int sockSize = sizeof(struct sockaddr_in);
	struct sockaddr_in client;
	
	if ((nb_lus = recvfrom(sock, element[0], size, 0, (struct sockaddr *) &client, (socklen_t*)&sockSize)) == 0)
		return;
		
	if (nb_lus < 0) {
		perror("read");
		return;
	}
	
	//write(STDOUT_FILENO, buffer, nb_lus);

	sendto(sock, element[0], size, 0, (struct sockaddr *) &client, sockSize);
}
