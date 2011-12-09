/* son.h						By : deneb					last modif : 09/12/11	   \
\_____________________________________________________________________________________*/

#ifndef SON_H
#define SON_H

	#include <alsa/asoundlib.h>
	
	#define ALSA_PCM_NEW_HW_PARAMS_API
	
	#define CAPTURE 0
	#define PLAYBACK 1

	int initSon(int mode, unsigned int *val, snd_pcm_uframes_t *frames);
	
	void closeSon();

	void capture(char* str);

	void playback(char* str);

#endif
