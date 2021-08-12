main: main.o Nha.o Nguoi.o xom.o pho.o ql.o
	g++ -o main main.o Nha.o Nguoi.o xom.o pho.o ql.o


main.o: *.h
	g++ -c main.cpp

ql.o: ql.h pho.h xom.h Nha.h Nguoi.h
	g++ -c ql.cpp
pho.o: pho.h xom.h Nha.h Nguoi.h
	g++ -c pho.cpp
xom.o: xom.h Nha.h Nguoi.h
	g++ -c xom.cpp
Nha.o: Nha.h Nguoi.h
	g++ -c Nha.cpp
Nguoi.o: Nguoi.h
	g++ -c Nguoi.cpp 
