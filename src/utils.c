/* projetVoip					By : deneb					last modif : 09/12/11	   \
\_____________________________________________________________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <alsa/asoundlib.h>
#include <signal.h>
#include <pthread.h>

#include "utils.h"
#include "socket_utils.h"
#include "son.h"
#include "capture.h"
#include "playback.h"


int launch (char* paradd, char* parport, pthread_t* threads, s_par_thread* param)
{
	char *address, *port;

	// param contient les variables nécéssaires dans les threads pour le son et les socket
	
	// pour le son
	param->val = 11025;
	param->frames = SIZE_PACKET / 4; // 2 bytes par channel, 2 channels
	
	//address = paradd;
	//port = parport; // need verification de la véracité des paramètres
	
	param->sock = sock_udp();
	
	#ifdef CLIENT
		//set_udp_address(&(param->serveur), port, address);
	#endif
	#ifdef SERVEUR
		//set_udp_address(&(param->serveur), port, NULL);
		if (bind(param->sock, (struct sockaddr *) &(param->destination), sizeof(struct sockaddr_in)) < 0) 
		{
			perror("bind");
			exit(EXIT_FAILURE);
		}
	#endif
	
	//printf("[I] Connection a l'adresse IP = %s, Port = %u \n", inet_ntoa(param->destination.sin_addr), ntohs(param->destination.sin_port));
	// Fin sockets
	
	#ifdef CLIENT
	pthread_create(threads + CAPTURE, 0, boucle_capture, param);
	#endif
	#ifdef SERVEUR
	pthread_create(threads + PLAYBACK, 0, boucle_playback, param);
	#endif
	return EXIT_SUCCESS;
}

int init_connection(char* paradd, char* parport, pthread_t* threads, s_par_thread* param)
{
	char *address, *port;
	int sockTcp, sock2;
	socklen_t sockSize = 0;

	address = paradd;
	port = parport; // need verification de la véracité des paramètres
	
	sockTcp = sock_tcp();
	
	char               buffer [LG_BUFFER];
	int                nb_lus;
	char               buff [256];
	
	#ifdef CLIENT
	
		if(set_tcp_address(&(param->destination), port, address) == EXIT_FAILURE)
			return EXIT_FAILURE;
		set_tcp_address(&(param->destination), port, address);
		//printf("[I] demande de connec a l'adresse IP = %s, Port = %u \n", inet_ntoa(param->destination.sin_addr), ntohs(param->destination.sin_port));
		
		if (connect (sockTcp, (struct sockaddr *) &param->destination, sizeof(struct sockaddr_in)) < 0) {
			perror ("connect");
			return(EXIT_FAILURE);
		}
		
		//getsockname(sockTcp, (struct sockaddr*) &(param->source), &sockSize);
		//printf("[I] connec depuis l'adresse IP = %s, Port = %u \n", inet_ntoa(param->source.sin_addr), ntohs(param->source.sin_port));
		setvbuf (stdout, NULL, _IONBF, 0);
		while (1) {
			if ((nb_lus = read (sockTcp, buffer, LG_BUFFER)) == 0)
				break;
			if (nb_lus < 0) {
				perror ("read");
				break;
			}
			write (STDOUT_FILENO, buffer, nb_lus);
		}
		
	
		
		
	#endif
	#ifdef SERVEUR
		memset(&param->destination, 0, sizeof (struct sockaddr_in));
	
		if(set_tcp_address(&(param->source), port, NULL) == EXIT_FAILURE)
			return EXIT_FAILURE;

		if (bind(sockTcp, (struct sockaddr *) &(param->source), sizeof(struct sockaddr_in)) < 0) 
		{
			perror("bind");
			return(EXIT_FAILURE);
		}
		//printf("[I] Attente de connec sur l'adresse IP = %s, Port = %u \n", inet_ntoa(param->source.sin_addr), ntohs(param->source.sin_port));
		listen (sockTcp, 5);
		fprintf (stdout, "Mon adresse >> ");
		getsockname (sockTcp, &(param->source), &sockSize);
    		fprintf (stdout, "IP = %s, Port = %u \n", inet_ntoa (param->source.sin_addr),  ntohs (param->source.sin_port));

		if((sock2 = accept(sockTcp, (struct sockaddr *)&(param->destination), &sockSize)) < 0) 
		{
			perror ("accept");
			exit(EXIT_FAILURE);
		}
		getpeername(sock2, (struct sockaddr*) &(param->destination), &sockSize);
		//printf("[I] connec depuis l'adresse IP = %s, Port = %u \n", inet_ntoa(param->destination.sin_addr), ntohs(param->destination.sin_port))
		sprintf (buff, "IP = %s, Port = %u \n", inet_ntoa (param->destination . sin_addr), ntohs (param->destination . sin_port));
		fprintf (stdout, "Connexion : locale ");
		getsockname (sock2, &(param->destination), &sockSize);
    		fprintf (stdout, "IP = %s, Port = %u \n", inet_ntoa (param->destination . sin_addr),  ntohs (param->destination . sin_port));
		fprintf (stdout, "          distante %s", buff);
		write (sock2, "Votre adresse : ", 16);
		write (sock2, buff, strlen (buff));
		close (sock2);
		close (sockTcp);



			
	#endif
	
	shutdown(sockTcp, SHUT_RDWR);
	//param->destination->sin_port = htons(port);
	//printf("port : %s\n", port);

	launch(NULL, NULL, threads, param);
	
	return EXIT_SUCCESS;
}
