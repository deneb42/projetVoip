/* son.c					By : deneb					last modif : 08/12/11		   \
\_____________________________________________________________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>



int initSon(char mode, snd_pcm_t **handle, snd_pcm_hw_params_t **params, unsigned int *val, int *dir, snd_pcm_uframes_t *frames)
{
	int rc;
	
	if(mode =='c') /* Open PCM device */
		rc = snd_pcm_open(handle, "default", SND_PCM_STREAM_CAPTURE, 0); 
	else if(mode =='p')
		rc = snd_pcm_open(handle, "default", SND_PCM_STREAM_PLAYBACK, 0);
	else
	{
		fprintf(stderr, "%c : mode d'ouverture du canal incorrect", mode);
		return EXIT_FAILURE;
	}
	
	if (rc < 0) 
	{
		fprintf(stderr, "unable to open pcm device: %s\n", snd_strerror(rc));
		return EXIT_FAILURE;
	}
	
	snd_pcm_hw_params_alloca(params); /* Allocate a hardware parameters object. */

	snd_pcm_hw_params_any(*handle, *params); /* Fill it in with default values. */

	/* Set the desired hardware parameters. */
	snd_pcm_hw_params_set_access(*handle, *params, SND_PCM_ACCESS_RW_INTERLEAVED); /* Interleaved mode */

	snd_pcm_hw_params_set_format(*handle, *params, SND_PCM_FORMAT_S16_LE); /* Signed 16-bit little-endian format */
	
	snd_pcm_hw_params_set_channels(*handle, *params, 2); /* Two channels (stereo) */
	
	snd_pcm_hw_params_set_rate_near(*handle, *params, val, dir); /* 44100 bits/second sampling rate (CD quality) */
	
	snd_pcm_hw_params_set_period_size_near(*handle, *params, frames, dir); /* Set period size to 32 frames. */
	
	rc = snd_pcm_hw_params(*handle, *params); /* Write the parameters to the driver */
	if (rc < 0) 
	{
		fprintf(stderr, "unable to set hw parameters: %s\n", snd_strerror(rc));
		return EXIT_FAILURE;
	}
  
	snd_pcm_hw_params_get_period_size(*params, frames, dir); /* Use a buffer large enough to hold one period */

	snd_pcm_hw_params_get_period_time(*params, val, dir); /* We want to loop for 5 seconds */

	return EXIT_SUCCESS;
}
