/* capture.h					By : deneb					last modif : 17/01/12	   \
\_____________________________________________________________________________________*/

#ifndef CAPTURE_H
#define CAPTURE_H

	#include <arpa/inet.h>

	int init_capture();
	
	void* boucle_capture(void* arg);
<<<<<<< HEAD
	int sendn(int sock, struct sockaddr_in * destination, s_MUV* packetS);
=======
	
	int sendMUV(int sock, struct sockaddr_in * destination, s_MUV* packetS);
>>>>>>> eb6dbf288b25958cff4358772b2da93b2d677f90
	
#endif
