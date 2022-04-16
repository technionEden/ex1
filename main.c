#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AsciiArtTool.h"



int main(int argc, char **argv)
{
    // READ
    FILE *readFile;
    readFile = fopen(argv[2], "r");
    RLEList asciiList = asciiArtRead(readFile);
    if (!asciiList) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    
    // WRITE
    RLEListResult result = RLE_LIST_SUCCESS;
    if(!strcmp(argv[1],"-e")) {
        // WRITE - ENCODED
        FILE *writeFile = fopen(argv[3], "w");
        result = asciiArtPrintEncoded(asciiList, writeFile);
        fclose(writeFile);
    }
    else if(!strcmp(argv[1],"-i")){
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
