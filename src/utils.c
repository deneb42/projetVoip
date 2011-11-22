#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int lecture_arguments (int argc, char * argv [], char** address, char** port)
{ /* reads the arguments and put them in the appropriate strings. if not given, initialize to default values */

	char * liste_options = "a:p:h";
	int option;
	char* ad = "localhost";
	char* po = "2000";
	
	if(address == NULL || port==NULL)
	{
		fprintf(stderr, "lecture_arguments : address and port must not be NULL");
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
}

