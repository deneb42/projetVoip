/* son.c					By : deneb					last modif : 08/12/11		   \
\_____________________________________________________________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>

#include "son.h"

snd_pcm_hw_params_t *params[2];
snd_pcm_t *handle[2];
snd_pcm_uframes_t frames[2];

int initSon(int mode, unsigned int *val, int *dir, snd_pcm_uframes_t *f)
{
	int rc;
	
	if(mode == CAPTURE) /* Open PCM device */
		rc = snd_pcm_open(handle, "default", SND_PCM_STREAM_CAPTURE, 0); 
	else if(mode == PLAYBACK)
		rc = snd_pcm_open(handle+PLAYBACK, "default", SND_PCM_STREAM_PLAYBACK, 0);
	else
	{
		fprintf(stderr, "%d : mode d'ouverture du canal incorrect", mode);
		return EXIT_FAILURE;
	}
	
	if (rc < 0) 
	{
		fprintf(stderr, "unable to open pcm device: %s\n", snd_strerror(rc));
		return EXIT_FAILURE;
	}
	
	snd_pcm_hw_params_alloca(params+mode); /* Allocate a hardware parameters object. */

	snd_pcm_hw_params_any(*(handle+mode), *(params+mode)); /* Fill it in with default values. */

	/* Set the desired hardware parameters. */
	snd_pcm_hw_params_set_access(*(handle+mode), *(params+mode), SND_PCM_ACCESS_RW_INTERLEAVED); /* Interleaved mode */

	snd_pcm_hw_params_set_format(*(handle+mode), *(params+mode), SND_PCM_FORMAT_S16_LE); /* Signed 16-bit little-endian format */
	
	snd_pcm_hw_params_set_channels(*(handle+mode), *(params+mode), 2); /* Two channels (stereo) */
	
	snd_pcm_hw_params_set_rate_near(*(handle+mode), *(params+mode), val, dir); /* 44100 bits/second sampling rate (CD quality) */
	
	snd_pcm_hw_params_set_period_size_near(*(handle+mode), *(params+mode), f, dir); /* Set period size to 32 frames. */
	
	rc = snd_pcm_hw_params(*(handle+mode), *(params+mode)); /* Write the parameters to the driver */
	if (rc < 0) 
	{
		fprintf(stderr, "unable to set hw parameters: %s\n", snd_strerror(rc));
		return EXIT_FAILURE;
	}
  
	snd_pcm_hw_params_get_period_size(*(params+mode), (frames+mode), dir); /* Use a buffer large enough to hold one period */

	snd_pcm_hw_params_get_period_time(*(params+mode), val, dir); /* We want to loop for 5 seconds */

	return EXIT_SUCCESS;
}

void capture(char* str)
{
	int rc;
	
	rc = snd_pcm_readi(handle[CAPTURE], str, frames[CAPTURE]);
	if (rc == -EPIPE) // EPIPE means overrun
	{
		fprintf(stderr, "overrun occurred\n");
		snd_pcm_prepare(handle[CAPTURE]);
	}
	else if (rc < 0)
		fprintf(stderr, "error from read: %s\n", snd_strerror(rc));
	else if (rc != (int)frames[CAPTURE])
		fprintf(stderr, "short read, read %d frames\n", rc);
}

void playback(char* str)
{
	int rc;

	rc = snd_pcm_writei(handle[PLAYBACK], str, frames[PLAYBACK]);
			
	if (rc == -EPIPE) // EPIPE means underrun
	{
		fprintf(stderr, "underrun occurred\n");
		snd_pcm_prepare(handle[PLAYBACK]);
	} 
	else if (rc < 0) 
		fprintf(stderr, "error from writei: %s\n", snd_strerror(rc));
	else if (rc != (int)frames[PLAYBACK]) 
		fprintf(stderr, "short write, write %d frames\n", rc);
}
