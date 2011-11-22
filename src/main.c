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

int main (int argc, char *argv[])
{
	struct sockaddr_in recepteur, emeteur;
	char buffer[LG_BUFFER], buffer2[LG_BUFFER];
	int nb_lus;
	int sockSize = sizeof(struct sockaddr_in);
	int sock = sock_udp();
	char *address, *port;

	
	if (lecture_arguments(argc, argv, &address, &port) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	
	set_udp_address(&recepteur, port, address);
	
	#ifdef SERVEUR
	if (bind(sock, (struct sockaddr *) &recepteur, sizeof(struct sockaddr_in)) < 0) 
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}
	#endif
	
	while (1)
	{
		#ifdef SERVEUR
			if ((nb_lus = recvfrom(sock, buffer, LG_BUFFER, 0, (struct sockaddr *) &emeteur, (socklen_t*)&sockSize)) == 0)
				break;
					
			if (nb_lus < 0) {
				perror("read");
				break;
			}
			
			write(STDOUT_FILENO, buffer, nb_lus);
			
			sendto(sock, buffer, nb_lus, 0, (struct sockaddr *) &emeteur, sockSize);
		#endif
		#ifdef CLIENT
			if ((nb_lus = read(STDIN_FILENO, buffer, LG_BUFFER)) == 0)
				break;

			if (nb_lus < 0) 
			{
				perror("read");
				break;
			}
			sendto(sock, buffer, nb_lus, 0,
				(struct sockaddr *) & recepteur, sizeof (struct sockaddr_in));
				
			if ((nb_lus = recv(sock, buffer2, LG_BUFFER, 0)) == 0)
				break;
			
			write(STDOUT_FILENO, buffer2, nb_lus);
		#endif
	}
	
	return EXIT_SUCCESS;
}

