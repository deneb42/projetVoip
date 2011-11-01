int lecture_arguments (int argc, char * argv [],
	struct sockaddr_in * adresse, char * protocole)
{
	char * liste_options = "a:p:h";
	int option;
	char * hote = "localhost";
	char * port = "2000";
	struct hostent * hostent;
	struct servent * servent;
	int numero;
	
	while ((option = getopt(argc, argv, liste_options)) != -1) {
		switch (option) {
			case ‘a’ :
				hote = optarg;
				break;
			case ‘p’ :
				port = optarg;
				break;
			case ‘h’ :
				fprintf(stderr, "Syntaxe : %s [-a adresse] [-p port] \n",
				argv[0]);
				return -1;
			default :
				break;
		}
	}
	
	memset(adresse, 0, sizeof (struct sockaddr_in));

	if (inet_aton(hote, & (adresse->sin_addr)) == 0) {
		if ((hostent = gethostbyname(hote)) == NULL) {
			fprintf(stderr, "hôte %s inconnu \n", hote);
			return -1;
		}
		adresse->sin_addr.s_addr = ((struct in_addr *) (hostent->h_addr))->s_addr;
	}
	
	if (sscanf(port, "%d", & numero) == 1) {
		adresse->sin_port = htons(numero);
		return 0;
	}
	
	if ((servent = getservbyname(port, protocole)) == NULL) {
		fprintf(stderr, "Service %s inconnu \n", port);
		return -1;
	}
	
	adresse->sin_port = servent->s_port;
	return 0;
}

