/* client.c						By : deneb					last modif : 09/12/11	   \
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


#define LG_BUFFER	1024

/* DEPRECATED
int snd_client(int sock, struct sockaddr_in * serveur, s_MUV* packetS)
{
	int nbS;
	//char strS[((const int)packetS->size+sizeof(long))];
	
	printf("sock : %d", sock);
	//MUVtoStr(packetS, strS);

	//if((nbS = sendto(sock, strS, packetS->size+sizeof(long), 0, (struct sockaddr *) serveur, sizeof(struct sockaddr_in) )) > 0)
	if((nbS = sendto(sock, packetS, sizeof(s_MUV), 0, (struct sockaddr *) serveur, sizeof(struct sockaddr_in) )) > 0)
		printf("envoye paquet num %lu de : %d octets\n", packetS->id, nbS);
	else
	{
		printf("ERF socket : %d de : %d octets\n", sock, nbS);
		perror("chier");
	}
		
	return EXIT_SUCCESS;
}*

int rcv_client(int sock, s_MUV* packetR)
{
	int nbR;
	//char strR[(packetR->size+sizeof(long))];
	
	//if ((nbR = recv(sock, strR, packetR->size+sizeof(long), MSG_DONTWAIT)) <= 0)
	if ((nbR = recv(sock, packetR,sizeof(s_MUV), MSG_DONTWAIT)) <= 0)
		return EXIT_FAILURE;
	else 
		printf("berf3\n");
		
	//strtoMUV(packetR, strR);
	
	printf("recu paquet num %lu de : %d octets\n", packetR->id, nbR);
	
	return EXIT_SUCCESS;
}
<<<<<<< HEAD

void* client_tcp_connexion (void* arg)
{
	s_par_thread param = *((s_par_thread*)arg);

	char               buffer [LG_BUFFER];
	int                nb_lus;
	
	/*sock = sock_tcp();

	set_tcp_address(& adresse, port, host);*/

	if (connect (param.sock_tcp, (struct sockaddr *) & param.serveur, (socklen_t) sizeof (struct sockaddr_in)) < 0) {
		perror ("connect");
		exit(EXIT_FAILURE);
	}
	setvbuf (stdout, NULL, _IONBF, 0);
	while (1) {
		if ((nb_lus = read (param.sock_tcp, buffer, LG_BUFFER)) == 0)
			break;
		if (nb_lus < 0) {
			perror ("read");
			break;
		}
		write (STDOUT_FILENO, buffer, nb_lus);
	}

	return NULL;
}
=======
*/
>>>>>>> eb6dbf288b25958cff4358772b2da93b2d677f90
