/* capture.h					By : deneb					last modif : 17/01/12	   \
\_____________________________________________________________________________________*/

#ifndef CAPTURE_H
#define CAPTURE_H

	#include <arpa/inet.h>

	void* boucle_capture(void* arg); // Initialise le handle de capture et lance la boucle principale qui enregistre un paquet et l'envoit.

	int send_voip(int sock, struct sockaddr_in * destination, s_voip* packetS); // Envoit le paquet passé en paramètre.
	
#endif
