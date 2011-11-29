/* client.c					By : deneb					last modif : 22/11/11		   \
\_____________________________________________________________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>


void traitement_client(int sock, struct sockaddr_in * serveur, void** element, int* size)
{
	int nb_lus;

	sendto(sock, element[0], size[0], 0, (struct sockaddr *) serveur, sizeof (struct sockaddr_in));
		
	if ((nb_lus = recv(sock, element[1], size[1], MSG_DONTWAIT)) == 0)
		return;
	
	write(STDOUT_FILENO, "recu\n", 6);
}
