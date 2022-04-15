#include "RLEList.h"
#include "RLEList.c"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>


void printRLEList(RLEList list);
void printRLEListFullData(RLEList list);
void printArray(int arr[], int length);
char moveOneUp(char letter);
void test1();
void test2();
void test3();

// MAKE SURE THAT WHEN YOU DO 'gcc ...' you don't add '-DNDEBUG'

int main()
{
    test1();
    test2();
    test3();


	return 0;
}



void test1()
{
    RLEList myList = RLEListCreate();

    RLEListAppend(myList,'W');
    RLEListAppend(myList,'W');
    RLEListAppend(myList,'A');
    RLEListAppend(myList,'A');
    RLEListAppend(myList,'A');
    RLEListAppend(myList,'B');
    RLEListAppend(myList,'B');
    RLEListAppend(myList,'C');
    RLEListAppend(myList,'C');
    RLEListAppend(myList,'C');
    RLEListAppend(myList,'C');
    RLEListAppend(myList,'C');
    RLEListAppend(myList,'C');
    RLEListAppend(myList,'C');
    RLEListAppend(myList,'C');
    RLEListAppend(myList,'C');
    RLEListAppend(myList,'C');
    RLEListAppend(myList,'C');


    printRLEList(myList);
    assert(RLEListSize(myList) == 18);

    RLEListResult myResult = RLE_LIST_SUCCESS;

    assert(RLEListGet(myList,7,&myResult) == 'B');
    assert(myResult == RLE_LIST_SUCCESS);


    assert(RLEListGet(myList,10,&myResult) == 'C');
    assert(myResult == RLE_LIST_SUCCESS);

    printf("Remove index==5\n");
    assert(RLEListRemove(myList,5) == RLE_LIST_SUCCESS);
    printRLEList(myList);

    assert(RLEListGet(myList,7,&myResult) == 'C');
    assert(myResult == RLE_LIST_SUCCESS);

    printf("Remove index==5\n");
    assert(RLEListRemove(myList,5) == RLE_LIST_SUCCESS);
    printRLEList(myList);

    printf("Remove index==5\n");
    assert(RLEListRemove(myList,5) == RLE_LIST_SUCCESS);
    printRLEList(myList);

    printf("Append Z\n");
    RLEListAppend(myList,'Z');
    printRLEList(myList);

    printf("Remove index==1\n");
    assert(RLEListRemove(myList,1) == RLE_LIST_SUCCESS);
    printRLEList(myList);

    assert(RLEListRemove(myList,0) == RLE_LIST_INDEX_OUT_OF_BOUNDS);
    printRLEList(myList);

    printf("Append Y\n");
    assert(RLEListAppend(myList,'Y') == RLE_LIST_SUCCESS);
    printRLEList(myList);

    printf("Print Export\n");
    char * myExport = RLEListExportToString(myList, &myResult);
    printf("Export: \n%s",myExport);
    assert(myResult == RLE_LIST_SUCCESS);
    free(myExport);

    printf("Remove index==1\n");
    assert(RLEListRemove(myList,1) == RLE_LIST_SUCCESS);
    printRLEList(myList);


    assert(RLEListGet(myList,1,&myResult) == 'A');
    assert(myResult == RLE_LIST_SUCCESS);

    printRLEListFullData(myList);

    RLEListMap(myList, moveOneUp);
    printf("Move up each letter:\n");
    printRLEList(myList);

    printf("New Export\n");
    char * myNewExport = RLEListExportToString(myList, &myResult);
    printf("Export: \n%s",myNewExport);
    assert(myResult == RLE_LIST_SUCCESS);
    free(myNewExport);

    printRLEListFullData(myList);

    RLEListDestroy(myList);
}

void test2()
{
    RLEList myList = RLEListCreate();

    RLEListAppend(myList,'W');
    printRLEList(myList);

    assert(RLEListSize(myList) == 1);

    printf("Remove index==1\n");
    assert(RLEListRemove(myList,1) == RLE_LIST_SUCCESS);
    printRLEList(myList);

    assert(RLEListSize(myList) == 0);

    printf("Remove index==1\n");
    assert(RLEListRemove(myList,1) == RLE_LIST_INDEX_OUT_OF_BOUNDS);
    printRLEList(myList);

    printf("Append Y\n");
    assert(RLEListAppend(myList,'Y') == RLE_LIST_SUCCESS);
    printRLEList(myList);
    printf("Append X\n");
    assert(RLEListAppend(myList,'X') == RLE_LIST_SUCCESS);
    printRLEList(myList);
    printf("Append Z\n");
    assert(RLEListAppend(myList,'Z') == RLE_LIST_SUCCESS);
    printRLEList(myList);

    RLEListDestroy(myList);
}

void test3()
{
    RLEListResult myResult = RLE_LIST_SUCCESS;
    RLEList myList = NULL;
    RLEListGet(myList,7,&myResult);
    assert(myResult == RLE_LIST_NULL_ARGUMENT);
}



// ----------------------------------------- DEBUGGING UTILITIES -----------------------------------------

void printRLEList(RLEList list)
{
    RLEList ptr = list;
    while(ptr) {
        for(int i=0; i< ptr->amount ;i++) {
            printf("%c",ptr->letter);
        }
        ptr = ptr->next;
    }
    printf("\n");
}

void printRLEListFullData(RLEList list)
{
    printf("Full Info:\n");
    RLEList ptr = list;
    printf("HEAD amount: %d (==0), letter: %c (==$)\n", ptr->amount, ptr->letter);
    while(ptr) {
        printf("Amount: %d Letter: %c\n",ptr->amount, ptr->letter);
        ptr = ptr->next;
    }
    printf("\n");
}

void printArray(int arr[], int length)
{
    printf("[");
    for(int i=0; i<length;i++){
        printf("%d,",arr[i]);
    }
    printf("]\n");
}

char moveOneUp(char letter)
{
    // Fake function to test map function
    int cycle = 'z'-'a';
    if (letter>='a' && letter<='z') {
        //printf("%c", ((letter-'a')+1)%cycle + 'a' );
        return ((letter-'a')+1)%cycle + 'a';
    }
    if (letter>='A' && letter<='Z') {
        //printf("%c", ((letter-'A')+1)%cycle + 'A' );
        return ((letter-'A')+1)%cycle + 'A';
    }
    return letter;
}


