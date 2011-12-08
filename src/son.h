/* son.h					By : deneb					last modif : 08/12/11		   \
\_____________________________________________________________________________________*/

#ifndef SON_H
#define SON_H

	#include <alsa/asoundlib.h>
	
	#define ALSA_PCM_NEW_HW_PARAMS_API

	int initSon(char mode, snd_pcm_t **handle, snd_pcm_hw_params_t **params, unsigned int *val, int *dir, snd_pcm_uframes_t *frames);

#endif
