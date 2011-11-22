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

#define LG_BUFFER 1024


void traitement_client(int sock, struct sockaddr_in * serveur)
{
	char buffer[LG_BUFFER], buffer2[LG_BUFFER];
	int nb_lus;

	if ((nb_lus = read(STDIN_FILENO, buffer, LG_BUFFER)) == 0)
		return;

	if (nb_lus < 0) 
	{
		perror("read");
		return;
	}
	
	sendto(sock, buffer, nb_lus, 0, (struct sockaddr *) serveur, sizeof (struct sockaddr_in));
		
	if ((nb_lus = recv(sock, buffer2, LG_BUFFER, 0)) == 0)
		return;
	
	write(STDOUT_FILENO, buffer2, nb_lus);
}
