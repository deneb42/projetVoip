#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include "rtp.h"



struct rtp {
	unsigned int sequence_number;
	unsigned int timestamp;
	void *data;
	struct sockaddr_in them;
};

int set_data(){
}

	
	

