/* socket_utils.h				By : deneb					last modif : 09/12/11	   \
\_____________________________________________________________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>


int set_address(struct sockaddr_in * address, unsigned short int type, char* port, char* host, char* protocol)
{ /* Sets the parameters of the adress. protocol can be NULL. returns 1 on sucess, -1 on failure */

	int num;
	struct hostent * hostent;
	struct servent * servent;
	
	memset(address, 0, sizeof (struct sockaddr_in));
	
	address->sin_family = type;
	
	if(host==NULL)
		address->sin_addr.s_addr = htonl(INADDR_ANY);
	else if (inet_aton(host, & (address->sin_addr)) == 0) 
	{
		if ((hostent = gethostbyname(host)) == NULL) 
		{
			fprintf(stderr, "hôte %s inconnu \n", host);
			return EXIT_FAILURE;
		}
		address->sin_addr.s_addr = ((struct in_addr *) (hostent->h_addr))->s_addr;
	}
	
	if (sscanf(port, "%d", &num) == 1) { // si le numero de port est entré apres -p
		address->sin_port = htons(num);
		return EXIT_SUCCESS;
	}
	
	if ((servent = getservbyname(port, protocol)) == NULL) { // si c'est un protocole qui est rentré
		fprintf(stderr, "Service %s inconnu \n", port); // si le protocole ne rend rien : erreur
		return EXIT_FAILURE;
	}
	
	address->sin_port = servent->s_port; // si le protocole permet d'extrapoler le numero de port
	return EXIT_SUCCESS;
}

int set_udp_address(struct sockaddr_in * address, char* port, char* host)
{ /* Sur-function that initiate an address for a udp connection */

	return set_address(address, AF_INET, port, host, "udp");
}

int sock_udp()
{ /* Create a UDP socket and returns its descriptor */

	int sock;

	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
	{
		fprintf(stderr, "sock_udp : address and port must not be NULL");
		exit(EXIT_FAILURE);
	}
	
	return sock;
}
	
