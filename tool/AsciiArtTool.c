#include "AsciiArtTool.h"


RLEList asciiArtRead(FILE* in_stream)
{
    RLEList asciiList = RLEListCreate();

    if (!in_stream || !asciiList){
        return NULL; //could not open file
    }

    char tmpChar;
    RLEListResult result = RLE_LIST_SUCCESS;
    while ((tmpChar = fgetc(in_stream)) != EOF && result == RLE_LIST_SUCCESS) {
        result = RLEListAppend(asciiList, tmpChar);
     }

    if (result!=RLE_LIST_SUCCESS){
        return NULL;
    }

    return asciiList;

}


RLEListResult asciiArtPrint(RLEList list, FILE *out_stream)
{
    if(!list) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    int listSize = RLEListSize(list);
    RLEListResult result = RLE_LIST_SUCCESS;
    for(int i=0; i<listSize && result==RLE_LIST_SUCCESS; i++) {
        char letter = RLEListGet(list, i, &result);
        if(result == RLE_LIST_SUCCESS){
            fputc (letter, out_stream);
        }
    }
    return result;
}


RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream)
{
    if (!list || !out_stream) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult result;
    char * encoded = RLEListExportToString(list,&result);
    if (result != RLE_LIST_SUCCESS || !encoded) {
        free(encoded);
        return result;
    }
    int writeResult = fputs(encoded, out_stream);
    free(encoded);
    if(writeResult!=EOF) {
        return result;
    }
    return RLE_LIST_ERROR;

}



