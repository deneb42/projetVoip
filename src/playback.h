/* playback.h					By : deneb					last modif : 17/01/12	   \
\_____________________________________________________________________________________*/

#ifndef PLAYBACK_H
#define PLAYBACK_H

	int init_playback();
	void* boucle_playback(void* arg);
	int receive(int sock, struct sockaddr_in * source, s_MUV* packetR);
	
#endif
