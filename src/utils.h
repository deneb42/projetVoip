/* utils.h						By : deneb					last modif : 08/12/11	   \
\_____________________________________________________________________________________*/

#ifndef UTILS_H
#define UTILS_H
	
	#include <arpa/inet.h>
	#include <alsa/asoundlib.h>

	#define TAILLE_LISTE 4
	#define SIZE_PACKET 128

	typedef struct t_MUV
	{
		unsigned long id;
		char data[SIZE_PACKET];
	} s_MUV;
	
	typedef struct t_par_thread
	{
		struct sockaddr_in serveur, client;
		int sock;

		unsigned int val;
		snd_pcm_uframes_t frames;
	} s_par_thread;

	int launch (char* paradd, char* port, pthread_t* threads, s_par_thread* param);

#endif
