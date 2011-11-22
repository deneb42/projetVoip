/* socket_utils.h					By : deneb					last modif : 22/11/11  \
\_____________________________________________________________________________________*/

#ifndef SOCKET_UTILS_H
#define SOCKET_UTILS_H

	int set_udp_address(struct sockaddr_in * address, char* port, char* host); 
		/* Sur-function that initiate an address for a udp connection */
		
	int set_address(struct sockaddr_in * address, unsigned short int type, char* port, char* host, char* protocol); 
		/* Sets the parameters of the adress. protocol can be NULL. returns 1 on sucess, -1 on failure */
		
	int sock_udp(); /* Create a UDP socket and returns its descriptor */
	
#endif