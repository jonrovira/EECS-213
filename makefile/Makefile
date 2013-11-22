CC = g++

CFLAGS = -g

default:	spellcheck

spellcheck:	main.cpp definitions.h parse.o dictionary.o spellcheck.o hash.o
	$(CC) $(CFLAGS) -o spellcheck main.cpp parse.o dictionary.o spellcheck.o hash.o

parse.o:	parse.cpp parse.h definitions.h
	$(CC) $(CFLAGS) -c parse.cpp 

dictionary.o:	dictionary.h dictionary.cpp hash.o definitions.h
	$(CC) $(CFLAGS) -c dictionary.cpp

spellcheck.o:	spellcheck.cpp spellcheck.h definitions.h hash.o parse.o
	$(CC) $(CFLAGS) -c spellcheck.cpp

hash.o:		hash.cpp hash.h definitions.h
	$(CC) $(CFLAGS) -c hash.cpp

clear:
	$(RM) spellcheck *.o *~