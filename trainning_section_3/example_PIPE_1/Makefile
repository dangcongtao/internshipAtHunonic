SRC_PROCESS_A=processA.c
EXE_PROCESS_A=a
SRC_PROCESS_B=processB.c
EXE_PROCESS_B=b
NAMED_PIPE=MyPipe
NAMED_PIPE2=MyPipe2
CFLAGS=-Wall


all: processA processB

processA: ${SRC_PROCESS_A}
	gcc ${CFLAGS} ${SRC_PROCESS_A} -o ${EXE_PROCESS_A}
processB: ${SRC_PROCESS_B}
	gcc ${CFLAGS} ${SRC_PROCESS_B} -o ${EXE_PROCESS_B}
clean:
	rm -f ${NAMED_PIPE} ${NAMED_PIPE2} ${EXE_PROCESS_A} ${EXE_PROCESS_B}