#include "RLEList.h"
#include "RLEList.c"
#include <assert.h>


void printRLEList(RLEList list);
void printRLEListFullData(RLEList list);
void printArray(int arr[], int length);
char moveOneUp(char letter);
void test1();


int main() {

    // FOR DEBUGGING, ERASE LATER !!
    test1();






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
    printf("size: %d\n",RLEListSize(myList));

    RLEListResult myResult = RLE_LIST_SUCCESS;

    printf("Letter at index 7\n");
    printf("Letter: %c\n",RLEListGet(myList,7,&myResult));

    printf("Letter at index 10\n");
    char let = RLEListGet(myList,10,&myResult);
    printf("Letter: %c Result: %i\n",let,myResult);

    printf("Remove index==5\n");
    RLEListRemove(myList,5);
    printRLEList(myList);

    printf("Letter at index 7\n");
    printf("Letter: %c\n",RLEListGet(myList,7,&myResult));

    printf("Remove index==5\n");
    RLEListRemove(myList,5);
    printRLEList(myList);

    printf("Remove index==5\n");
    RLEListRemove(myList,5);
    printRLEList(myList);

    printf("Append Z\n");
    RLEListAppend(myList,'Z');
    printRLEList(myList);

    printf("Remove index==1\n");
    RLEListRemove(myList,1);
    printRLEList(myList);

    printf("Append Y\n");
    RLEListAppend(myList,'Y');
    printRLEList(myList);

    printf("Print Export\n");
    char * myExport = RLEListExportToString(myList, &myResult);
    printf("Export: \n%s Message: %d\n",myExport, myResult);
    free(myExport);

    printf("Remove index==4\n");
    RLEListRemove(myList,4);
    printRLEList(myList);

    printf("Remove index==1\n");
    RLEListRemove(myList,1);
    printRLEList(myList);

    printf("Letter at index 1\n");
    printf("Letter: %c\n",RLEListGet(myList,1,&myResult));


    printRLEListFullData(myList);

    RLEListMap(myList, moveOneUp);
    printf("Move up each letter:\n");
    printRLEList(myList);

    RLEListDestroy(myList);
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