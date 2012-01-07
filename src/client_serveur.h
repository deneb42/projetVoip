/* client_serveur.h				By : deneb					last modif : 09/12/11	   \
\_____________________________________________________________________________________*/

#ifndef CLIENT_SERVEUR_H
#define CLIENT_SERVEUR_H

	int traitement_client(int sock, struct sockaddr_in * serveur, s_MUV* packetS, s_MUV* packetR);
	int traitement_serveur(int sock, s_MUV* packetS, s_MUV* packetR);

#endif
