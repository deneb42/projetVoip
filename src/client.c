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


void traitement_client(int sock, struct sockaddr_in * serveur, void** element, int size)
{
	//char buffer[LG_BUFFER];
	int nb_lus;

	/*if ((nb_lus = read(STDIN_FILENO, buffer, LG_BUFFER)) == 0)
		return;

	if (nb_lus < 0) 
	{
		perror("read");
		return;
	}*/
	
	sendto(sock, element[0], size, 0, (struct sockaddr *) serveur, sizeof (struct sockaddr_in));
		
	if ((nb_lus = recv(sock, element[0], size, MSG_DONTWAIT)) == 0)
		return;
	
	//write(STDOUT_FILENO, buffer, nb_lus);
}
