#|  projetVoip makefile             |
#|                                  |
#|  by :deneb                       |
#|  last modif : 24/01/12           |
#/__________________________________/


INC_PATH = 
LIB_PATH = 
LIBRARY = -lasound -pthread `pkg-config --libs gtk+-2.0`
CFLAGS = -Wall -ansi -pedantic -std=c99 -D_GNU_SOURCE `pkg-config --cflags gtk+-2.0`
LDFALGS = $(LIB_PATH) $(LIBRARY)
GCC=gcc

# Name of the files (more .o)
OBJS = son.o socket_utils.o
#utils.o socket_utils.o son.o interface.o capture.o playback.o
# Path where the bin will be
PGM_PATH = ./
#names of the execs
CLIENT = utils.o interface.o capture.o playback.o
SERVEUR = utils.o interface.o capture.o playback.o

# For the generic utilisation, 
# DO NOT TOUCH ANYTHING UNDER THIS LINE !!!
# ___________________________________________

# $(OBJS:.o=_client.o ) 
all : client serveur

client : $(CLIENT:.o=_client.o ) $(OBJS)
	$(GCC) -o $(PGM_PATH)client $(CLIENT:.o=_client.o ) $(OBJS) $(LDFALGS) 
	
serveur : $(SERVEUR:.o=_serveur.o ) $(OBJS)
	$(GCC) -o $(PGM_PATH)serveur $(SERVEUR:.o=_serveur.o ) $(OBJS) $(LDFALGS)

# generic method for all the .o

%_client.o : %.c
	$(GCC) -D CLIENT -o $@ $(CFLAGS) $(INC_PATH) -c $< 

%_serveur.o : %.c
	$(GCC) -D SERVEUR -o $@ $(CFLAGS) $(INC_PATH) -c $<

%.o : %.c
	$(GCC) $(CFLAGS) $(INC_PATH) -c $< 

#run :
#	$(PGM_PATH)$(PGM)

clean :
	-rm *.o *~
	
cleanmax : clean
	-rm $(PGM_PATH)client $(PGM_PATH)serveur
