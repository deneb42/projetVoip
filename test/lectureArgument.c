#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int lecture_arguments (int argc, char * argv [], char* address, char* port)
{
	char * liste_options = "a:p:h";
	int option;
	
	if(address == NULL || port==NULL)
	{
		fprintf(stderr, "lecture_arguments : address and port must not be NULL");
		return EXIT_FAILURE;
	}
	
	strcpy(address, "localhost");;
	strcpy(port, "2000");

	while ((option = getopt(argc, argv, liste_options)) != -1) 
	{
		switch (option) 
		{
			case 'a' :
				strcpy(address, optarg);
				break;
			case 'p' :
				strcpy(port, optarg);
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

