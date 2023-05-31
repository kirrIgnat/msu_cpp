CC = g++

all: win2utf utf2win koi2utf utf2koi win2koi koi2win

win2utf: win2utf.cpp utf8.h utf8.cpp
	$(CC) -o win2utf win2utf.cpp utf8.cpp

utf2win: utf2win.cpp utf8.h utf8.cpp
	$(CC) -o utf2win utf2win.cpp utf8.cpp

koi2utf: koi2utf.cpp utf8.h utf8.cpp
	$(CC) -o koi2utf koi2utf.cpp utf8.cpp

utf2koi: utf2koi.cpp utf8.h utf8.cpp
	$(CC) -o utf2koi utf2koi.cpp utf8.cpp

win2koi: win2koi.cpp utf8.h utf8.cpp
	$(CC) -o win2koi win2koi.cpp utf8.cpp

koi2win: koi2win.cpp utf8.h utf8.cpp
	$(CC) -o koi2win koi2win.cpp utf8.cpp

clean:
	rm -f win2utf utf2win koi2utf utf2koi win2koi koi2win
