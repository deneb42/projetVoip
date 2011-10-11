#|  voip makefile                   |
#|                                  |
#|  by :deneb                       |
#|  last modif : 11/10/11           |
#/__________________________________/


INC_PATH =
LIB_PATH = 
LIBRARY = -asound
CFLAGS = -Wall -pedantic -std=c99 -D_GNU_SOURCE
LDFALGS = $(LIB_PATH) $(LIBRARY)
GCC=gcc

# Name of the files (more .o)
OBJS = 
# Path where the bin will be
PGM_PATH = ./
# Name of the bin
PGM = voip


# For the generic utilisation, 
# DO NOT TOUCH ANYTHING UNDER THIS LINE !!!
# ___________________________________________

# $(OBJS: =.o ) 
all : $(OBJS) 
	$(GCC) -o $(PGM_PATH)$(PGM) $(OBJS) $(LDFALGS) 

# generic method for all the .o
%.o : %.c
	$(GCC) $(CFLAGS) $(INC_PATH) -c $< 

run :
	$(PGM_PATH)$(PGM)

clean :
	-rm *.o *~ $(PGM_PATH)$(PGM)
