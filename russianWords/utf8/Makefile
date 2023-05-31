CC = g++ $(CFLAGS)
CFLAGS =

all: readTst writeTst words rusChars encodeRus tstget

readTst: readTst.cpp utf8.cpp utf8.h
	g++ -o readTst readTst.cpp utf8.cpp

writeTst: writeTst.cpp utf8.cpp utf8.h
	g++ -o writeTst writeTst.cpp utf8.cpp

words: words.cpp  utf8.cpp utf8.h
	g++ -o words words.cpp utf8.cpp

rusChars: rusChars.cpp utf8.cpp utf8.h
	g++ -o rusChars rusChars.cpp utf8.cpp

encodeRus: encodeRus.cpp utf8.cpp utf8.h
	g++ -o encodeRus encodeRus.cpp utf8.cpp

tstget: tstget.cpp
	g++ -o tstget tstget.cpp

clean:
	rm -f readTst writeTst words rusChars encodeRus tstget
