CPP=g++
C=gcc

#remove all file.
#remove: main
#	rm main *.o

.PHONY: main clean_o
clean_o: main
	rm *.o

main: main1.o house.o person.o
	$(CPP) -o $@ main1.o house.o person.o


main1.o: *.h
	g++ -c main1.cpp

house.o: house.h
	g++ -c house.cpp

person.o: person.h
	g++ -c person.cpp

