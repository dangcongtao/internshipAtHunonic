# .PHONY: all pubsub_opts.o

# all: pubsub_opts.o
# 	gcc main.c -v -o test pubsub_opts.o -lrt -lm -lpthread -lcrypto -lssl -lpaho-mqtt3as -lpaho-mqtt3c -lpaho-mqtt3cs -lpaho-mqtt3a

# pubsub_opts.o: pubsub_opts.h
# 	gcc -c pubsub_opts.c
# clean:
# 	rm *.out.*


.PHONY: all
SRC_PROCESS_A=processMQTT.c
EXE_PROCESS_A=MQTT
SRC_PROCESS_B=processUART.c
EXE_PROCESS_B=UART
NAMED_PIPE_PUB=pub_pipe
NAMED_PIPE_SUB=sub_pipe
CFLAGS=-Wall


all: processA processB

processA: ${SRC_PROCESS_A}
	gcc ${CFLAGS} ${SRC_PROCESS_A} -o ${EXE_PROCESS_A}  -v -lrt -lm -lpthread -lcrypto -lssl -lpaho-mqtt3as -lpaho-mqtt3c -lpaho-mqtt3cs -lpaho-mqtt3a
processB: ${SRC_PROCESS_B}
	gcc ${CFLAGS} ${SRC_PROCESS_B} -o ${EXE_PROCESS_B} -v -lrt -lm -lpthread -lcrypto -lssl -lpaho-mqtt3as -lpaho-mqtt3c -lpaho-mqtt3cs -lpaho-mqtt3a
clean:
	rm -f ${NAMED_PIPE_SUB} ${NAMED_PIPE_PUB} ${EXE_PROCESS_A} ${EXE_PROCESS_B}