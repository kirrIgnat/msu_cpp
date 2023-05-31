This package contains 6 console programs for converting
text file between different Russian encoding:
UTF-8, Windows-1251, and KOI8-R. The names of the
programs are self-explanatory:
    utf2win, win2utf, utf2koi, koi2utf,
    win2koi, koi2win.
Each program reads the source text either from
a file, when a file name is given as the first argument
of the command line, or from the standard input, when
there is no arguments. The resulting text is written 
into a file, when file name is given as the second argument,
or into the standard output. For example, the command line
for the utf2win program is
    utf2win [input-file-path [output-file-path]]
 
To compile all programs, perfform the command
    make

Пакет содержит исходный текст шести C++ программ,
предназначенных для перекодировки текстовых файлов
на русском языке между тремя кодировками:
    UTF-8, Windows CP1251, KOI8-R.
Программы называются 
    utf2win, win2utf, utf2koi, koi2utf,
    win2koi, koi2win.
Названия указывают, какую именно перекодировку выполняет
каждая программа. Например, программа utf2win перекодирует 
текст из кодировки UTF-8 (Unicode) в кодировку
Windows-1251 (Russian).

Все программы запускаются из командной строки.
Если при этом аргументы не указываются, то программа читает
исходный текст из входного потока и записывает результат в
выходной поток. Если указан один аргумент, то это имя 
файла с исходным текстом, результат записывается в выходной
поток. Если же заданы 2 аргумента, то это пути к исходному
файлу и файлу для записи результата. Например, команда
    win2utf TextWin.txt
читает исходный текст в кодировке Windows-1251 из файла
TextWin.txt, перекодирует его UTF-8 и записывает в выходной
поток. Команда
    win2koi win.txt koi.txt
читает входной текст в кодировке Windos-1251 из файла
win.txt и записывает перекодированный в KOI8-R текст в
файл koi.txt.

Для компиляции всех шести программ достаточно выполнить
команду make.

