#|  voip makefile                   |
#|                                  |
#|  by :deneb                       |
#|  last modif : 22/11/11           |
#/__________________________________/


INC_PATH =
LIB_PATH = 
LIBRARY = -lasound
CFLAGS = -Wall -pedantic -std=c99 -D_GNU_SOURCE
LDFALGS = $(LIB_PATH) $(LIBRARY)
GCC=gcc

# Name of the files (more .o)
OBJS = main.o utils.o socket_utils.o client.o serveur.o son.o
# Path where the bin will be
PGM_PATH = ./
#names of the execs
CLIENT = client
SERVEUR = serveur

# For the generic utilisation, 
# DO NOT TOUCH ANYTHING UNDER THIS LINE !!!
# ___________________________________________

# $(OBJS:.o=_client.o ) 
all : client serveur

client : $(OBJS:.o=_client.o ) 
	$(GCC) -o $(PGM_PATH)$(CLIENT) $(OBJS:.o=_client.o )  $(LDFALGS) 
	
serveur : $(OBJS:.o=_serveur.o )
	$(GCC) -o $(PGM_PATH)$(SERVEUR) $(OBJS:.o=_serveur.o ) $(LDFALGS)

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
	-rm $(PGM_PATH)$(CLIENT) $(PGM_PATH)$(SERVEUR)
