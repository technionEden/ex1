#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "RLEList.h"
#include "AsciiArtTool.h"
#include "AsciiArtTool.c"

int checkMainInput(int argc, char **argv);


int main(int argc, char **argv)
{
    
    if (!checkMainInput(argc,argv)) {
        // What type of return am i supposed to put here?
        return 0;
    }

    // READ
    FILE *readFile;
    readFile = fopen(argv[2], "r");
    RLEList asciiList = asciiArtRead(readFile);

    // WRITE
    RLEListResult result = RLE_LIST_SUCCESS;
    if(!strcmp(argv[1],"-e")) {
        // WRITE - ENCODED
        FILE *writeFile = fopen(argv[3], "w");
        result = asciiArtPrintEncoded(asciiList, writeFile);
        fclose(writeFile);
    } else {
        // WRITE - INVERTED
        FILE *appendFile = fopen(argv[3], "a");
        result = RLEListMap(asciiList, asciiInvertCharacter);
        if (result == RLE_LIST_SUCCESS) {
            result = asciiArtPrint(asciiList, appendFile);
        }
        fclose(appendFile);
    }


    // CLOSE/FREE

    fclose(readFile);
    RLEListDestroy(asciiList);
    
    return result;
    
}

int checkMainInput(int argc, char **argv)
{
    if (argc != 4) {
        printf("Didn't enter 3 arguments, entered %d\n", argc);
        for(int i=1; i<argc; i++){
            printf("%s",argv[i]);
        }
        printf("\n");
        return 0;
    }

    if(strcmp(argv[1],"-e")!=0 && strcmp(argv[1],"-i")!=0) {
        printf("Not appropriate flag\n");
        return 0;
    }
    // TODO: check other arguments too
    return 1;
}