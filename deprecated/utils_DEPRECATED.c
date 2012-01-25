/* utils.c						By : deneb					last modif : 09/12/11	   \
\_____________________________________________________________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "utils.h"

/* DEPRECATED 
 * 
void * MUVtoStr(s_MUV * packet, char* str)
{
	memcpy(str, &(packet->id), sizeof(long));
	memcpy(str+sizeof(long), packet->data, packet->size);
	
	return str;
}

void * strtoMUV(s_MUV * packet, char* str)
{
	memcpy(&(packet->id), str, sizeof(long));
	memcpy(packet->data, str+sizeof(long), packet->size);
	
	return packet;
}*

int getIndex(char* str)
{
	int id;
	memcpy(str, &id, sizeof(long));
	
	return id;
}

/*int lecture_arguments (int argc, char * argv [], char** address, char** port) // DEPRECATED
{ /* reads the arguments and put them in the appropriate strings. if not given, initialize to default values *

	char * liste_options = "a:p:d:h";
	int option;
	char* ad = "localhost";
	char* po = "2000";
	
	if(address == NULL || port==NULL)
	{
		fprintf(stderr, "lecture_arguments : address, dest and port must not be NULL");
		return EXIT_FAILURE;
	}
	
	*address = ad;
	*port = po;

	while ((option = getopt(argc, argv, liste_options)) != -1) 
	{
		switch (option) 
		{
			case 'a' :
				*address = optarg;
				break;
			case 'p' :
				*port = optarg;
				break;
			case 'h' :
				fprintf(stderr, "Syntaxe : %s [-a adresse] [-p port] \n", argv[0]);
				return EXIT_FAILURE;
			default :
				break;
		}
	}

	return EXIT_SUCCESS;
} */
