#include "RLEList.h"


int main() {

    // FOR DEBUGGING, ERASE LATER !!
    

	RLEList myList = RLEListCreate();
    printf("hello\n");
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

    printf("Append A\n");
    RLEListAppend(myList,'A');
    printRLEList(myList);

    printf("Remove index==1\n");
    RLEListRemove(myList,1);
    printRLEList(myList);

    printf("Append A\n");
    RLEListAppend(myList,'A');
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

    RLEListDestroy(myList);



	return 0;
}




struct RLEList_t{
    int amount;
    char letter;
    struct RLEList_t* next;
};

//implement the functions here

RLEList RLEListCreate()
{
    RLEList ptr = malloc(sizeof(*ptr));
	if(!ptr) {
		return NULL;
	}
	ptr->amount = 0;
    ptr->letter = '$'; // This way we can differentiate the HEAD
	ptr->next = NULL;
	return ptr;
}

void RLEListDestroy(RLEList list)
{
    while(list) {
		RLEList toDelete = list;
		list = list->next;
		free(toDelete);
	}
}


RLEListResult RLEListAppend(RLEList list, char value)
{
    if (!list || !value) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList ptr = list;
    while (ptr->next) {
        ptr = ptr->next;
    }

    return RLEListAppend_aux(ptr, value);

}

RLEListResult RLEListAppend_aux(RLEList finalPtr, char value)
{
    if (finalPtr->letter == value) {
        finalPtr->amount = finalPtr->amount+1;
    }

    else {
        RLEList newNode = RLEListCreate();
        if (!newNode){
            return RLE_LIST_OUT_OF_MEMORY;
        }
        finalPtr->next = newNode;
        newNode->amount = 1;
        newNode->letter = value;
    }
    return RLE_LIST_SUCCESS;
}


int RLEListSize(RLEList list)
{
    if(!list){
        return -1;
    }
    int count = 0;
    RLEList ptr = list;
     do {
        count += ptr->amount;
        ptr = ptr->next;
    } while (ptr);

     return count;
}

RLEListResult RLEListRemove(RLEList list, int index)
{
    if(!list) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(RLEListSize(list)<index) {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }

    RLEList ptr = list;
    RLEList prev = list;
    int amountLetters = 0;

    while(amountLetters + ptr->amount < index && ptr) {
        amountLetters += ptr->amount;
        prev=ptr;
        ptr = ptr->next;
    }
    ptr->amount = (ptr->amount) - 1;

    if(ptr->amount == 0) {
        RLEListCleanUp(prev);
    }


    return RLE_LIST_SUCCESS;

}

void RLEListCleanUp(RLEList prevNode)
{
    RLEList toDelete = prevNode->next;
    RLEList newNext = toDelete->next;
    prevNode->next = newNext;
    free(toDelete);
}


char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    if(!list) {
        *result =  RLE_LIST_NULL_ARGUMENT;
        return 0;
    }
    if(RLEListSize(list)<index) {
        *result =  RLE_LIST_INDEX_OUT_OF_BOUNDS;
        return 0;
    }

    RLEList ptr = list;
    int amountLetters = 0;
    while(amountLetters + ptr->amount < index && ptr) {
        amountLetters += ptr->amount;
        ptr = ptr->next;
    }
    if(ptr->letter){
        *result =  RLE_LIST_SUCCESS;
        return ptr->letter;
    }
    return 0;

}


char* RLEListExportToString(RLEList list, RLEListResult* result)
{
    if (!list){
        *result = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }
    // BUGGY!!! If I just have the HEAD ('$'), does it count as a NULL or not? Here I act as if it's not NULL.
    int nodes = countNodes(list->next);
    int* digits = malloc(sizeof(int)*(nodes));
    int digitCount = countDigits(list->next, digits);

    char* exportStr = malloc(sizeof(char)*((nodes*2)+digitCount+1)); // MAKE SURE OUTSIDE THERE'S FREE()

    RLEListExportToString_aux(exportStr, list->next, digits, nodes, digitCount);

    *result = RLE_LIST_SUCCESS;
    free(digits);
    return exportStr;
}

void RLEListExportToString_aux(char* exportStr, RLEList ptr, int digits[], int nodes, int digitCount)
{
    int currIndex = 0;
    for(int i=0; i<nodes; i++) {
        exportStr[currIndex++]=ptr->letter;
        while( digits[i]>0 ) {
            exportStr[currIndex]=(ptr->amount/( calcPow(10,(digits[i]-1)) ))%10+'0';
            digits[i]--;
            currIndex++;
        }
        exportStr[currIndex++]='\n';
        ptr=ptr->next;
    }
    exportStr[(nodes*2)+digitCount] = '\0';
}

int countNodes(RLEList list)
{
    RLEList ptr = list;
    int count = 0;
    while(ptr) {
        count++;
        ptr = ptr->next;
    }
    return count;
}
int countDigits(RLEList list, int arr[])
{
    RLEList ptr = list;
    int count = 0;
    for(int i =0; ptr; i++) {
        int ptrAmount = ptr->amount;
        int digitCount = 0;
        while (ptrAmount/10>0) {
            digitCount++;
            ptrAmount = ptrAmount/10;
        }
        arr[i] = digitCount+1;
        count+=arr[i];
        ptr = ptr->next;
    }
    return count;
}
int calcPow(int a, int b)
{
    int ans = 1;
    while(b>0) {
        ans=ans*a;
        b--;
    }
    return ans;
}


// NEED TO CHECK THIS !!!
RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if (!list || !map_function) {
        return RLE_LIST_NULL_ARGUMENT;
    }

    RLEList newList = RLEListCreate();
    int listSize = RLEListSize(list);
    RLEListResult result = RLE_LIST_SUCCESS;
    for(int i=0; i<listSize; i++) {
        char oldChar = RLEListGet(list,i,&result);
        char newChar = map_function(oldChar);
        RLEListAppend(newList, newChar);
    }

    RLEListDestroy(list->next);
    list->next = NULL;

    for(int i=0; i<listSize;i++) {
        RLEListAppend(list, RLEListGet(newList,i,&result));
    }

    return RLE_LIST_SUCCESS;
}


// ----------------------------------------- FOR DEBUGGING !!! -----------------------------------------
// ERASE LATER!!!
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
