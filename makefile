CC = g++ -g
EXE = music_finder

$(EXE): catalog.o run_catalog.o
	$(CC) catalog.o run_catalog.o -o $(EXE)

catalog.o: catalog.cpp
	$(CC) -c catalog.cpp

run_catalog.o: run_catalog.cpp
	$(CC) -c run_catalog.cpp 

clean: 
	rm -f *.o $(EXE)

leak_check: catalog.o run_catalog.o
	$(CC) catalog.o run_catalog.o -o $(EXE)
	valgrind --leak-check=full ./$(EXE)