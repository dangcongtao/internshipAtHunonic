# process A chat with process B.
.PHONY: all

all: processA processB

processA:
	gcc processA.c -v -o a_process -lrt -lpthread -lcrypto -lssl

processB:
	gcc processB.c -v -o b_process -lrt -lpthread -lcrypto -lssl


clean: 
	rm -f a_process b_process pipe1 pipe2


# install third party(CJson and AES)
# then change this Makefile to Makefile.mk
# CXXFLAGS	+= -I./app

# VPATH += app

# OBJ += $(OBJ_DIR)/processB.o processA.o