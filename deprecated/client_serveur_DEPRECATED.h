/* client_serveur.h				By : deneb					last modif : 09/12/11	   \
\_____________________________________________________________________________________*/

#ifndef CLIENT_SERVEUR_H
#define CLIENT_SERVEUR_H

<<<<<<< HEAD

	int traitement_client(int sock, struct sockaddr_in * serveur, s_MUV* packetS, s_MUV* packetR);
	int traitement_serveur(int sock, s_MUV* packetS, s_MUV* packetR);
=======
	//int traitement_client(int sock, struct sockaddr_in * serveur, s_MUV* packetS, s_MUV* packetR);
	//int traitement_serveur(int sock, s_MUV* packetS, s_MUV* packetR);
>>>>>>> eb6dbf288b25958cff4358772b2da93b2d677f90
	
	//int snd_serveur(int sock, struct sockaddr_in * client, s_MUV* packetS);
	//int rcv_serveur(int sock, struct sockaddr_in * client, s_MUV* packetR);
	
	//int snd_client(int sock, struct sockaddr_in * serveur, s_MUV* packetS);
	//int rcv_client(int sock, s_MUV* packetR);

	void* client_tcp_connexion (void* arg);
	void* server_tcp_connexion (void* arg);
	

#endif
