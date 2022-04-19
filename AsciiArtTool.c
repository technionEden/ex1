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
    RLEList ptr = list;
    while(ptr) {
        for(int i=0; i< getNodeAmount(ptr) ;i++) {
            fputc (getNodeLetter(ptr), out_stream);
        }
        ptr =  getNodeNext(ptr);
    }
    return RLE_LIST_SUCCESS;
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
    return result;
}



