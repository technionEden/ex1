COMPILER = gcc
EXE = AsciiArtTool
ASCII_ART_TOOL = tool/AsciiArtTool
MAIN = tool/main
RLE_LIST = /home/mtm/public/2122b/ex1/RLEList
OBJ_FILES = $(ASCII_ART_TOOL).o $(MAIN).o RLEList.o
FLAGS = -std=c99 -Wall -Werror -I/home/mtm/public/2122b/ex1
G_FLAG = -g

$(EXE): $(OBJ_FILES)
	$(COMPILER) $(G_FLAG) $(FLAGS) $(OBJ_FILES) -o $(EXE)


$(ASCII_ART_TOOL).o: $(ASCII_ART_TOOL).c $(ASCII_ART_TOOL).h $(RLE_LIST).h
	$(COMPILER) $(FLAGS) $(G_FLAG) -c $(ASCII_ART_TOOL).c -o $(ASCII_ART_TOOL).o

$(MAIN).o: $(MAIN).c $(ASCII_ART_TOOL).h $(RLE_LIST).h
	$(COMPILER) $(FLAGS) $(G_FLAG) -c $(MAIN).c -o $(MAIN).o

RLEList.o: RLEList.c $(RLE_LIST).h
	$(COMPILER) $(FLAGS) $(G_FLAG) -c RLEList.c


clean:
	rm -f $(OBJ_FILES) $(EXE)