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

// NE PAS UTILISER LOCALHOST COMME ADRESSE DU SERVEUR ! IL FAUT UTILISER L'ADRESSE DE SOUS RÉSEAU


//------------- new----------
#define ALSA_PCM_NEW_HW_PARAMS_API

#include <alsa/asoundlib.h>

//---------------------------

void traitement_client(int sock, struct sockaddr_in * serveur, void* element, int *size);
void traitement_serveur(int sock, void* element, int *size);

int main (int argc, char *argv[])
{
	struct sockaddr_in serveur;
	int sock;
	char *address, *port;
	//-------------------new ------------
	snd_pcm_hw_params_t *params[2];
	snd_pcm_t *handle[2];
	char *buffer[2];
	
	unsigned int val[2] = {11025, 11025};
	snd_pcm_uframes_t frames[2] = {32, 32};
	int size[2] = {128, 128}; /* 2 bytes/sample, 2 channels */
		
	int dir[2];
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
	//#ifdef CLIENT
		rc = snd_pcm_open(&handle[0], "default", SND_PCM_STREAM_CAPTURE, 0); /* Open PCM device for playback. */
		
		if (rc < 0) 
		{
			fprintf(stderr, "unable to open pcm device: %s\n", snd_strerror(rc));
			exit(1);
		}
	
	//*#ifdef SERVEUR
		
		rc = snd_pcm_open(&handle[1], "default", SND_PCM_STREAM_PLAYBACK, 0);
		
		if (rc < 0) 
		{
			fprintf(stderr, "unable to open pcm device: %s\n", snd_strerror(rc));
			exit(1);
		}
	//#endif */
	
	
	
	for(int i=0;i<2;i++)
	{
		snd_pcm_hw_params_alloca(&params[i]); /* Allocate a hardware parameters object. */

		snd_pcm_hw_params_any(handle[i], params[i]); /* Fill it in with default values. */

		/* Set the desired hardware parameters. */
		snd_pcm_hw_params_set_access(handle[i], params[i], SND_PCM_ACCESS_RW_INTERLEAVED); /* Interleaved mode */

		snd_pcm_hw_params_set_format(handle[i], params[i], SND_PCM_FORMAT_S16_LE); /* Signed 16-bit little-endian format */
		
		snd_pcm_hw_params_set_channels(handle[i], params[i], 2); /* Two channels (stereo) */
		
		snd_pcm_hw_params_set_rate_near(handle[i], params[i], i+val, dir+i); /* 44100 bits/second sampling rate (CD quality) */
		
		snd_pcm_hw_params_set_period_size_near(handle[i], params[i], i+frames, i+dir); /* Set period size to 32 frames. */
		
		rc = snd_pcm_hw_params(handle[i], params[i]); /* Write the parameters to the driver */
		if (rc < 0) 
		{
			fprintf(stderr, "unable to set hw parameters: %s\n", snd_strerror(rc));
			exit(1);
		}
	  
		snd_pcm_hw_params_get_period_size(params[i], i+frames, i+dir); /* Use a buffer large enough to hold one period */

		buffer[i] = (char *) malloc(size[i]);

		snd_pcm_hw_params_get_period_time(params[i], i+val, i+dir); /* We want to loop for 5 seconds */
	}
	//==================================================================
	
	while (1) // boucle principale
	{
		rc = snd_pcm_readi(handle[0], buffer[0], frames[0]);
		if (rc == -EPIPE) /* EPIPE means overrun */
		{
			fprintf(stderr, "overrun occurred\n");
			snd_pcm_prepare(handle[0]);
		}
		else if (rc < 0)
			fprintf(stderr, "error from read: %s\n", snd_strerror(rc));
		else if (rc != (int)frames[1])
			fprintf(stderr, "short read, read %d frames\n", rc);
		
		#ifdef SERVEUR
			traitement_serveur(sock, buffer, size);
		#endif
		#ifdef CLIENT
			traitement_client(sock, &serveur, buffer, size);
        #endif
        
		rc = snd_pcm_writei(handle[1], buffer[1], frames[1]);
		if (rc == -EPIPE) /* EPIPE means underrun */
		{
			fprintf(stderr, "underrun occurred\n");
			snd_pcm_prepare(handle[1]);
		} 
		else if (rc < 0) 
			fprintf(stderr, "error from writei: %s\n", snd_strerror(rc));
		else if (rc != (int)frames[1]) 
			fprintf(stderr, "short write, write %d frames\n", rc);
	}
	
	for(int i=0;i<2;i++)
	{
		snd_pcm_drain(handle[i]);
		snd_pcm_close(handle[i]);
		free(buffer[i]);
	}
	
	return EXIT_SUCCESS;
}
