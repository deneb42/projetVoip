/* utils.h						By : deneb					last modif : 08/12/11	   \
\_____________________________________________________________________________________*/

#ifndef UTILS_H
#define UTILS_H

	#define TAILLE_LISTE 4

	typedef struct t_MUV
	{
		unsigned long id;
		//char *ip_dest;
		char *data;
		int size;
	} s_MUV;
	
	typedef struct t_par_thread
	{
		struct sockaddr_in serveur, client;
		int sock;

		unsigned int val;
		snd_pcm_uframes_t frames;
	} s_par_thread;

	
	void* MUVtoStr(s_MUV * packet, char* str);

	void* strtoMUV(s_MUV * packet, char* str);
	
	int getIndex(char* str);

	int lecture_arguments (int argc, char * argv [], char** address, char** port);
		/* reads the arguments and put them in the appropriate strings. if not given, initialize to default values */
	
#endif
