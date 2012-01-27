/* utils.h						By : deneb					last modif : 08/12/11	   \
\_____________________________________________________________________________________*/

#ifndef UTILS_H
#define UTILS_H
	
	#include <arpa/inet.h>
	#include <alsa/asoundlib.h>
	#include <gtk/gtk.h>

	#define TAILLE_LISTE 4
	#define SIZE_PACKET 128
	
	typedef struct t_voip
	{
		unsigned long id;
		char data[SIZE_PACKET];
	} s_voip;
	
	typedef struct t_par_thread
	{
		struct sockaddr_in destination, source;
		int sock;
		unsigned int val;
		snd_pcm_uframes_t frames;
	} s_par_thread;
	
	typedef struct t_par_gtk
	{
		int statut;
		pthread_t threads[3];
		s_par_thread param_t;
		GtkWidget* widget;
	} s_par_gtk;

	int launch (char* port, pthread_t* threads, s_par_thread* param);
	
	int init_connection(char* paradd, char* parport, pthread_t* threads, s_par_thread* param);


#endif
