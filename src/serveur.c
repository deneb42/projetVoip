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

/* DEPRECATED 
int snd_serveur(int sock, struct sockaddr_in * client, s_MUV* packetS)
{
	int nbS;
	//char strS[((const int)packetS->size+sizeof(long))];
	
	
	//MUVtoStr(packetS, strS);

	//if((nbS = sendto(sock, strS, packetS->size+sizeof(long), 0, (struct sockaddr *) &client, sizeof(struct sockaddr_in) )) > 0)
	if((nbS = sendto(sock, packetS, sizeof(s_MUV), 0, (struct sockaddr *) &client, sizeof(struct sockaddr_in) )) > 0)
		printf("envoye paquet num %lu de : %d octets\n", packetS->id, nbS);
	else 
		printf("berf1\n");

	return EXIT_SUCCESS;
} */

int rcv_serveur(int sock, struct sockaddr_in * client, s_MUV* packetR)
{
	int sockSize = sizeof(struct sockaddr_in);
	
	int nbR;
	//char strR[(packetR->size+sizeof(long))];
	
	//if ((nbR = recvfrom(sock, strR, packetR->size+sizeof(long), 0, (struct sockaddr *) client, (socklen_t*)&sockSize )) <= 0)
	if ((nbR = recvfrom(sock, packetR, sizeof(s_MUV), MSG_DONTWAIT, (struct sockaddr *) client, (socklen_t*)&sockSize )) <= 0)
		return EXIT_FAILURE;
	else 
		printf("berf2\n");
	//strtoMUV(packetR, strR);
	
	printf("recu paquet num %lu de : %d octets\n", packetR->id, nbR);
	
	return EXIT_SUCCESS;
}


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
