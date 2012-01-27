#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <alsa/asoundlib.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#include <netdb.h>
#include <netinet/in.h>

#include <sys/types.h>
#include <sys/socket.h>

#include "utils.h"
#include "socket_utils.h"
#include "client_serveur.h"
#include "son.h"

#include "capture.h"
#include "playback.h"

#define LG_BUFFER 1024

int init_connection(char* paradd, char* parport, pthread_t* threads, s_par_thread* param)
{
	char *address, *port;
	int sockTcp, sock2;
	socklen_t sockSize = 0;

	address = paradd;
	port = parport; // need verification de la véracité des paramètres

	sockTcp = sock_tcp();

	char buffer [LG_BUFFER];
	int nb_lus;
	char buff [256];
	
	#ifdef CLIENT

		if(set_tcp_address(&(param->destination), port, address) == EXIT_FAILURE)
			return EXIT_FAILURE;
		set_tcp_address(&(param->destination), port, address);
	
		/* La fonction connect() permet d etablir une connexion avec un serveur */
		if (connect (sockTcp, (struct sockaddr *) &param->destination, sizeof(struct sockaddr_in)) < 0) {
			perror ("connect");
			return(EXIT_FAILURE);
		}
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
		
		/* La fonction listen() permet de mettre un socket en attente de connexion */
		listen (sockTcp, 5);
		fprintf (stdout, "Mon adresse >> ");
		getsockname (sockTcp, &(param->source), &sockSize);
		fprintf (stdout, "IP = %s, Port = %u \n", inet_ntoa (param->source.sin_addr), ntohs (param->source.sin_port));
		
		/* La fonction accept() permet la connexion en acceptant un appel */
		if((sock2 = accept(sockTcp, (struct sockaddr *)&(param->destination), &sockSize)) < 0)
		{
			perror ("accept");
			exit(EXIT_FAILURE);
		}
		getpeername(sock2, (struct sockaddr*) &(param->destination), &sockSize);
		
		sprintf (buff, "IP = %s, Port = %u \n", inet_ntoa (param->destination . sin_addr), ntohs (param->destination . sin_port));
		fprintf (stdout, "Connexion : locale ");
		getsockname (sock2, &(param->destination), &sockSize);
		fprintf (stdout, "IP = %s, Port = %u \n", inet_ntoa (param->destination . sin_addr), ntohs (param->destination . sin_port));
		fprintf (stdout, " distante %s", buff);
		write (sock2, "Votre adresse : ", 16);
		write (sock2, buff, strlen (buff));
		close (sock2);
		close (sockTcp);



	#endif




	return EXIT_SUCCESS;
}


