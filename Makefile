prog: AsciiArtTool.o main.o RLEList.o
	gcc AsciiArtTool.o main.o RLEList.o -o prog
AsciiArtTool.o: AsciiArtTool.c AsciiArtTool.h RLEList.h
	gcc -std=c99 -Werror -c AsciiArtTool.c
main.o: main.c AsciiArtTool.h RLEList.h
	gcc -std=c99 -Werror -c main.c
RLEList.o: RLEList.c RLEList.h
	gcc -std=c99 -Werror -c RLEList.c
clean:
	rm -f AsciiArtTool.o main.o RLEList.o prog