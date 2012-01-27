/* playback.h					By : deneb					last modif : 17/01/12	   \
\_____________________________________________________________________________________*/

#ifndef PLAYBACK_H
#define PLAYBACK_H

	void* boucle_playback(void* arg); // Initialise le handle de lecture et lance la boucle principale qui lit les paquets recus.
	
	int receive_voip(int sock, s_voip* packetR); // recoit un paquet danas packetR.
	
#endif
