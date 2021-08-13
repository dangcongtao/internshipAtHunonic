CPP=g++
CLASS_A=class_a

.PHONY: main

clean_o: main
	rm *.o

main: main.o $(CLASS_A).o
	$(CPP) -o $@ main.o $(CLASS_A).o

main.o: *.h
	$(CPP) -c main.cpp

$(CLASS_A).o: $(CLASS_A).h
	$(CPP) -c  $(CLASS_A).cpp 