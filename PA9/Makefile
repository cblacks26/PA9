CC = g++
CFLAGS = -Wall -c
LFLAGS = -Wall
INCLUDE  = -I.

all: main.o Count.o Stem.o Exception.o Compare.o
	$(CC) main.o Count.o Stem.o Exception.o Compare.o -Wall $(INCLUDE) -o PA9
	
main.o: main.cpp Count.h Compare.h
	$(CC) main.cpp $(CFLAGS) $(INCLUDE)
	
Count.o: Count.cpp Count.h Stem.h Exception.h
	$(CC) Count.cpp $(CFLAGS) $(INCLUDE)
	
Compare.o: Compare.cpp Compare.h Count.h
	$(CC) Compare.cpp $(CFLAGS) $(INCLUDE)
	
Stem.o: Stem.cpp Stem.h
	$(CC) Stem.cpp $(CFLAGS) $(INCLUDE)
  
Exception.o: Exception.cpp Exception.h
	$(CC) Exception.cpp $(CFLAGS) $(INCLUDE)

clean :
	-rm *.o PA9
