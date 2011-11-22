#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "utils.h"
#include "socket_utils.h"

#define LG_BUFFER 1024

void traitement_client(int sock, struct sockaddr_in * serveur);//, char* buf, int lol);
void traitement_serveur(int sock);

int main (int argc, char *argv[])
{
	struct sockaddr_in serveur;
	int sock;
	char *address, *port;
	// Fin des variables
	
	// Initialisation --------------------------------------------------
	if (lecture_arguments(argc, argv, &address, &port) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	
	sock = sock_udp();
	set_udp_address(&serveur, port, address);
	
	#ifdef SERVEUR
		if (bind(sock, (struct sockaddr *) &serveur, sizeof(struct sockaddr_in)) < 0) 
		{
			perror("bind");
			exit(EXIT_FAILURE);
		}
	#endif
	//------------------------------------------------------------------
	
	while (1) // boucle principale
	{
		#ifdef SERVEUR
			traitement_serveur(sock);
		#endif
		#ifdef CLIENT
			traitement_client(sock, &serveur);
		#endif
	}
	
	return EXIT_SUCCESS;
}

