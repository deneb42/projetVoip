//header.h

#ifndef HEADER_H
#define HEADER_H

	int set_udp_address(struct sockaddr_in * address, char* port, char* host)
	int set_address(struct sockaddr_in * address, unsigned short int type, char* port, char* host, char* protocol)
	int sock_udp()
	
#endif
