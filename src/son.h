/* son.h						By : deneb					last modif : 09/12/11	   \
\_____________________________________________________________________________________*/

#ifndef SON_H
#define SON_H

	#include <alsa/asoundlib.h>
	
	#define ALSA_PCM_NEW_HW_PARAMS_API
	
	#define CAPTURE 0
	#define PLAYBACK 1
	// Servent a identifier le handle en question. doivent etre utilisés pour définir le mode des fonctions suivantes.

	int initSon(int mode, unsigned int *val, snd_pcm_uframes_t *frames);
		// Alloue et initialise le handle séléctionné par mode, avec les valeurs passées en paramètres.
	
	void closeSon(int mode); // Vide et désalloue le handle son séléctionné.

	void capture(char* str); // Capture une frame et l'enregistre dans le buffer passé en paramètre.

	void playback(char* str); // Lit la frame passée en paramètre.

#endif
