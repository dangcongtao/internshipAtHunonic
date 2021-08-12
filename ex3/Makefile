rm -f main main1.o house.o person.o

main: main1.o house.o person.o
	g++ -o main main1.o house.o person.o


main1.o: *.h
	g++ -c main1.cpp

house.o: house.h
	g++ -c house.cpp

person.o: person.h
	g++ -c person.cpp

