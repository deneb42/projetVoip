/* son.c						By : deneb					last modif : 24/12/11	   \
\_____________________________________________________________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>

#include "son.h"

snd_pcm_t *handle[2]; // On ne peut avoir au maximum que un handle pour la lecture et un pour la capture...
snd_pcm_uframes_t frames; // ...et un nombre de frame par periode commun aux deux afin de rester coherent.
// nous avons donc décidé de les placer ici afin d'éviter de se les asser en paramètres a chaque appel.
// De plus, cela permet d'améliorer la modularité du code : on n'utilise presque pas ALSA en dehors de ce fichier.


int initSon(int mode, unsigned int *val, snd_pcm_uframes_t *f)
{
	snd_pcm_hw_params_t *params;
	int dir;
	int rc;
	
	
	if(mode == CAPTURE) // Alloue le handle en fonction du mode voulu.
		rc = snd_pcm_open(handle, "default", SND_PCM_STREAM_CAPTURE, 0); 
	else if(mode == PLAYBACK)
		rc = snd_pcm_open(handle+PLAYBACK, "default", SND_PCM_STREAM_PLAYBACK, 0);
	else
	{
		fprintf(stderr, "[E] %d : mode d'ouverture du canal incorrect", mode);
		return EXIT_FAILURE; // Si le mode n'est pas bien définit, erreur de programmation : il faut couper tout de suite.
	}
	
	if (rc < 0) 
	{
		fprintf(stderr, "[E] unable to open pcm device: %s\n", snd_strerror(rc));
		return EXIT_FAILURE; // Si il y a erreur a l'ouverture du handle, il ne sert a rien de continuer ou coupe tout ici.
	}
	
	snd_pcm_hw_params_alloca(&params); // Allocation d'une structure qui va contenir les paramètres du handle...
	snd_pcm_hw_params_any(*(handle+mode), params); // ...que l'on remplit avec les valeurs par défaut.
	
	// On définit les paramètres de notre handle.
	snd_pcm_hw_params_set_access(*(handle+mode), params, SND_PCM_ACCESS_RW_INTERLEAVED); // Entrelacé.
	snd_pcm_hw_params_set_format(*(handle+mode), params, SND_PCM_FORMAT_S16_LE); // Enregistrement au format 16-bit little-endian.
	snd_pcm_hw_params_set_channels(*(handle+mode), params, 2); // Enregistrement sur deux canaux (stereo).
	snd_pcm_hw_params_set_rate_near(*(handle+mode), params, val, &dir); // Taux d'échantillonage de "val" bits/seconde.
	snd_pcm_hw_params_set_period_size_near(*(handle+mode), params, f, &dir); // Période de f frames.
	
	rc = snd_pcm_hw_params(*(handle+mode), params); // On affecte ces paramètres au handle.
	if (rc < 0) 
	{
		fprintf(stderr, "[E] unable to set hw parameters: %s\n", snd_strerror(rc));
		return EXIT_FAILURE;
	}
  
	snd_pcm_hw_params_get_period_size(params, &frames, &dir); /* Use a buffer large enough to hold one period */

	//snd_pcm_hw_params_get_period_time(params, val, &dir);

	return EXIT_SUCCESS;
}

void closeSon(int mode)
{
	printf("[I] Desallocation du handle de ");
	if(mode==CAPTURE)
		printf("capture\n");
	else
		printf("lecture\n");
		
	snd_pcm_drain(handle[mode]);
	snd_pcm_close(handle[mode]);
	printf("[I] OK\n");
}

void capture(char* str)
{
	int rc;

	rc = snd_pcm_readi(handle[CAPTURE], str, frames);

	if (rc == -EPIPE) // EPIPE means overrun
	{
		fprintf(stderr, "[D] overrun occurred\n");
		snd_pcm_prepare(handle[CAPTURE]);
	}
	else if (rc < 0)
		fprintf(stderr, "[E] error from read: %s\n", snd_strerror(rc));
	else if (rc != (int)frames)
		fprintf(stderr, "[D] short read, read %d frames\n", rc);
}

void playback(char* str)
{
	int rc;

	rc = snd_pcm_writei(handle[PLAYBACK], str, frames);
			
	if (rc == -EPIPE) // EPIPE means underrun
	{
		fprintf(stderr, "[D] underrun occurred\n");
		snd_pcm_prepare(handle[PLAYBACK]);
	} 
	else if (rc < 0) 
		fprintf(stderr, "[E] error from writei: %s\n", snd_strerror(rc));
	else if (rc != (int)frames) 
		fprintf(stderr, "[D] short write, write %d frames\n", rc);
}
