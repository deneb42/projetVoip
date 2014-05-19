/* socket_utils.h				By : deneb					last modif : 09/12/11	   \
\_____________________________________________________________________________________*/

#ifndef SOCKET_UTILS_H
#define SOCKET_UTILS_H
		
	int set_address(struct sockaddr_in * address, unsigned short int type, char* port, char* host, char* protocol); 
		/* Sets the parameters of the adress. protocol can be NULL. returns 1 on sucess, -1 on failure */
		
	int set_udp_address(struct sockaddr_in * address, char* port, char* host); 
		/* Sur-fonction qui initialise une adresse, se basant a défaut sur le port udp */

	int set_tcp_address(struct sockaddr_in * address, char* port, char* host); 
		/* Sur-fonction qui initialise une adresse, se basant a défaut sur le port tcp */
		
	int sock_udp(); /* Crée un socket udp et retourne son descripteur */

	int sock_tcp(); /* Crée un socket tcp et retourne son descripteur */
	
	int set_port(struct sockaddr_in * address, char* port); /* définit le port de l'adresse a port */

	
#endif
