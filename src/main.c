#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "utils.h"
#include "socket_utils.h"

//------------- new----------
#define ALSA_PCM_NEW_HW_PARAMS_API

#include <alsa/asoundlib.h>

//---------------------------

void traitement_client(int sock, struct sockaddr_in * serveur, void* element, int size);
void traitement_serveur(int sock, void* element, int size); // suffisant ou besoin de pointeur sur pointeur ?

int main (int argc, char *argv[])
{
	struct sockaddr_in serveur;
	int sock;
	char *address, *port;
	//-------------------new ------------
	snd_pcm_hw_params_t *params;
	snd_pcm_t *handle;
	char *buffer;
	
	unsigned int val = 11025;
	snd_pcm_uframes_t frames = 32;
	int size = frames * 4; /* 2 bytes/sample, 2 channels */
		
	int dir;
	int rc;
	//-------------------------------------
	
	// Fin des variables
	
	// Initialisation --------------------------------------------------
	if (lecture_arguments(argc, argv, &address, &port) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	
	sock = sock_udp();
	set_udp_address(&serveur, port, address);
	
	#ifdef SERVEUR
		if (bind(sock, (struct sockaddr *) &serveur, sizeof(struct sockaddr_in)) < 0) 
		{
			perror("bind");
			exit(EXIT_FAILURE);
		}
	#endif
	//------------------------------------------------------------------
	// SON==============================================================
	#ifdef CLIENT
		rc = snd_pcm_open(&handle, "default", SND_PCM_STREAM_CAPTURE, 0); /* Open PCM device for playback. */
	#endif
	#ifdef SERVEUR
		rc = snd_pcm_open(&handle, "default", SND_PCM_STREAM_PLAYBACK, 0); /* Open PCM device for recording (capture). */
	#endif
	
	if (rc < 0) 
	{
		fprintf(stderr, "unable to open pcm device: %s\n", snd_strerror(rc));
		exit(1);
	}
	
	snd_pcm_hw_params_alloca(&params); /* Allocate a hardware parameters object. */

	snd_pcm_hw_params_any(handle, params); /* Fill it in with default values. */

	/* Set the desired hardware parameters. */
	snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED); /* Interleaved mode */

	snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE); /* Signed 16-bit little-endian format */
	
	snd_pcm_hw_params_set_channels(handle, params, 2); /* Two channels (stereo) */
	
	snd_pcm_hw_params_set_rate_near(handle, params, &val, &dir); /* 44100 bits/second sampling rate (CD quality) */
	
	snd_pcm_hw_params_set_period_size_near(handle, params, &frames, &dir); /* Set period size to 32 frames. */
	
	rc = snd_pcm_hw_params(handle, params); /* Write the parameters to the driver */
	if (rc < 0) 
	{
		fprintf(stderr, "unable to set hw parameters: %s\n", snd_strerror(rc));
		exit(1);
	}
  
	snd_pcm_hw_params_get_period_size(params, &frames, &dir); /* Use a buffer large enough to hold one period */

	buffer = (char *) malloc(size);

	snd_pcm_hw_params_get_period_time(params, &val, &dir); /* We want to loop for 5 seconds */
	
	//==================================================================
	
	while (1) // boucle principale
	{
		#ifdef SERVEUR
			//rc = read(0, buffer, size);
			traitement_serveur(sock, buffer, size);
			/*if (rc == 0) 
			{
				fprintf(stderr, "end of file on input\n");
				break;
			} 
			else if (rc != size) 
				fprintf(stderr, "short read: read %d bytes\n", rc);
			*/
			rc = snd_pcm_writei(handle, buffer, frames);
			if (rc == -EPIPE) /* EPIPE means underrun */
			{
				fprintf(stderr, "underrun occurred\n");
				snd_pcm_prepare(handle);
			} 
			else if (rc < 0) 
				fprintf(stderr, "error from writei: %s\n", snd_strerror(rc));
			else if (rc != (int)frames) 
				fprintf(stderr, "short write, write %d frames\n", rc);
		#endif
		#ifdef CLIENT
			rc = snd_pcm_readi(handle, buffer, frames);
			if (rc == -EPIPE) /* EPIPE means overrun */
			{
				fprintf(stderr, "overrun occurred\n");
				snd_pcm_prepare(handle);
			}
			else if (rc < 0)
				fprintf(stderr, "error from read: %s\n", snd_strerror(rc));
			else if (rc != (int)frames)
				fprintf(stderr, "short read, read %d frames\n", rc);

			/*rc = write(1, buffer, size);
			if (rc != size)
				fprintf(stderr, "short write: wrote %d bytes\n", rc);
			*/
			traitement_client(sock, &serveur, buffer, size);
        #endif
/*
		#ifdef SERVEUR
			traitement_serveur(sock);
		#endif
		#ifdef CLIENT
			traitement_client(sock, &serveur);
		#endif
*/
	}
	
	snd_pcm_drain(handle);
	snd_pcm_close(handle);
	free(buffer);
	
	return EXIT_SUCCESS;
}
