CPP=g++
CLASS_A=class_a
CLASS_B=class_b


.PHONY: main clean_o

clean_o: main
	rm *.o

main: main.o $(CLASS_A).o $(CLASS_B).o
	$(CPP) -o $@ main.o $(CLASS_A).o $(CLASS_B).o

main.o: *.h
	$(CPP) -c main.cpp

$(CLASS_A).o: $(CLASS_A).h
	$(CPP) -c $(CLASS_A).cpp

$(CLASS_B).o: $(CLASS_B).h $(CLASS_B).h
	$(CPP) -c $(CLASS_B).cpp