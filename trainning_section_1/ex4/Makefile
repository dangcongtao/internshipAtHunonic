CPP=g++
CLASS_A=man
CLASS_B=a_g
CLASS_C=archer
CLASS_D=valiant
CLASS_E=knight
CLASS_F=team


.PHONY: clean_o main

clean_o: main
	rm *.o

main: main.o $(CLASS_A).o $(CLASS_B).o $(CLASS_C).o $(CLASS_D).o $(CLASS_E).o $(CLASS_F).o
	$(CPP) -o $@ main.o $(CLASS_A).o $(CLASS_B).o $(CLASS_C).o $(CLASS_D).o $(CLASS_E).o $(CLASS_F).o

main.o: *.h
	$(CPP) -c main.cpp

$(CLASS_A).o: $(CLASS_A).h
	$(CPP) -c $(CLASS_A).cpp

$(CLASS_B).o: $(CLASS_B).h $(CLASS_A).h
	$(CPP) -c $(CLASS_B).cpp


$(CLASS_C).o: $(CLASS_C).h $(CLASS_A).h
	$(CPP) -c $(CLASS_C).cpp


$(CLASS_D).o: $(CLASS_D).h $(CLASS_A).h
	$(CPP) -c $(CLASS_D).cpp


$(CLASS_E).o: $(CLASS_E).h $(CLASS_A).h
	$(CPP) -c $(CLASS_E).cpp



$(CLASS_F).o: $(CLASS_B).h $(CLASS_A).h $(CLASS_C).h $(CLASS_D).h $(CLASS_E).h $(CLASS_F).h
	$(CPP) -c $(CLASS_F).cpp