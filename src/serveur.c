/* serveur.c					By : deneb					last modif : 09/12/11	   \
\_____________________________________________________________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "utils.h"
#include "socket_utils.h"
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/socket.h>

void* server_tcp_connexion (void* arg)
{
	int sock_connectee;
	char               buffer [256];
	s_par_thread param = *((s_par_thread*)arg);
	
	/*sock = sock_tcp();

	set_tcp_address(& adresse, port, NULL);
	if (bind(sock, (struct sockaddr *) & adresse, sizeof(struct sockaddr_in)) < 0) 
	{ 
		perror("bind");
		exit(EXIT_FAILURE);
	}*/

	listen (param.sock_tcp, 5);
	fprintf (stdout, "Mon adresse >> ");
    	printf("[I] Connection a l'adresse IP = %s, Port = %u \n", inet_ntoa(param.serveur.sin_addr), ntohs(param.serveur.sin_port));
	
	sock_connectee = accept(param.sock_tcp, (struct sockaddr *) & param.client, (socklen_t *) sizeof (struct sockaddr_in));
	if (sock_connectee < 0) 
	{
		perror ("accept");
		exit(EXIT_FAILURE);
	}

	sprintf (buffer, "IP = %s, Port = %u \n", inet_ntoa (param.client.sin_addr), ntohs (param.client.sin_port));
	fprintf (stdout, "Connexion : locale ");
	printf("[I] Connection a l'adresse IP = %s, Port = %u \n", inet_ntoa(param.client.sin_addr), ntohs(param.client.sin_port));

	fprintf (stdout, "          distante %s", buffer);
	write (sock_connectee, "Votre adresse : ", 16);
	write (sock_connectee, buffer, strlen (buffer));	
  
	return NULL;
}
