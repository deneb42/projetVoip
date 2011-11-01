#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#define LG_BUFFER 1024

int lecture_arguments (int argc, char * argv [],
	struct sockaddr_in * adresse, char * protocole);

int main (int argc, char *argv[])
{
	int sock;
	struct sockaddr_in adresse;
	char buffer[LG_BUFFER];
	int nb_lus;

	if (lecture_arguments(argc, argv, & adresse, "udp") < 0)
		exit(EXIT_FAILURE);
	
	adresse.sin_family = AF_INET;
	
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}
	
	while (1) 
	{
		if ((nb_lus = read(STDIN_FILENO, buffer, LG_BUFFER)) == 0)
			break;

		if (nb_lus < 0) 
		{
			perror("read");
			break;
		}
		sendto(sock, buffer, nb_lus, 0,
			(struct sockaddr *) & adresse, sizeof (struct sockaddr_in));
	}
	
	return EXIT_SUCCESS;
}

