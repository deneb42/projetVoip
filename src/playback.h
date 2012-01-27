/* playback.h					By : deneb					last modif : 17/01/12	   \
\_____________________________________________________________________________________*/

#ifndef PLAYBACK_H
#define PLAYBACK_H

	void* boucle_playback(void* arg);
	
	int receive_voip(int sock, s_voip* packetR);
	
#endif
