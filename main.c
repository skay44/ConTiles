#include <stdio.h>
#include "genericList.h"
#include "system.h"
#include "column.h"
#include "row.h"
#include "screen.h"


void listTest() {
    GenericList list_int;
    initList(&list_int,sizeof(int));

    printf("\na:");
    printAllData(&list_int);

    int* v1 = addNode(&list_int);
    *v1 = 1;

    printf("\nb:");
    printAllData(&list_int);

    int* v2 = addNode(&list_int);
    *v2 = 2;

    printf("\nc:");
    printAllData(&list_int);

    int* v3 = addNode(&list_int);
    *v3 = 3;

    deleteAll(&list_int);

    printf("\nd:");
    printAllData(&list_int);
}



int main(void) {
    Screen mainScreen;
    initializeScreen(&mainScreen);

    addColumnToScreen(&mainScreen,1,0x1,0x10);
    addColumnToScreen(&mainScreen,5,0x2,0x20);
    Column* red_column = addColumnToScreen(&mainScreen,3,0x4,0x40);

    addRowToColumn(red_column,2,0x1,0x10);
    addRowToColumn(red_column,2,0x2,0x20);
    addRowToColumn(red_column,4,0x4,0x40);

    while (1) {
        generateView(&mainScreen);
    }
}
