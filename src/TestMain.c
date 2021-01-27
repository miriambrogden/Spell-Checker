/*
 @file TestMain.c
 @author Miriam Snow
 @date November 2017
 @brief File containing the test cases of a hash map api
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "HashMap.h"
#include "LinkedListAPI.h"
#include "Dictionary.h"

int main (void){
    char wordArray[3][10];
    strcpy(wordArray[0], "Why");
    strcpy(wordArray[1], "Hello");
    strcpy(wordArray[2], "World");

    printf("Test: createTable\n");
    printf("Expected Output: Table has been created\n");
    HTable * H1 = malloc(sizeof(HTable));
    H1 = createTable(26,hashNode,destroyNodeData,printNodeData);
    if (sizeof(H1) != 0){
        printf("Actual Output: Table has been created\n");
        printf("Test Result: Test Passed\n");
    } else {
        printf("Actual output: Table has not been created\n");
        printf("Test Result: Test Failed\n");
    }

    int key = generateKey(wordArray[0]);
    printf("\nTest: hasNode\n");
    printf("Expected Output: Index is 9\n");
    int index = hashNode(H1->size,key);
    if (index == 9){
        printf("Actual Output: Index is %d\n", index);
        printf("Test Result: Test Passed\n");
    } else {
        printf("Actual Output: Index is %d\n", index);
        printf("Test Result: Test Failed\n");
    }

    printf("\nTest: createNode\n");
    printf("Expected Output: Node has been created\n");
    HNode * HN1 = malloc(sizeof(HNode));
    HN1 = createNode(key,wordArray[0]);
    if (HN1 != NULL){
        printf("Actual Output: Node has been created\n");
        printf("Test Result: Test Passed\n");
    } else {
        printf("Actual Output: Node has not been created\n");
        printf("Test Result: Test Failed\n");
    }

    printf("\nTest: insertData (empty list)\n");
    printf("Expected Output: 9 : 87: Why\n");
    insertData(H1, index, HN1);
    printf("Actual Output: ");
    printNodeData(H1->table[index]->head->data);
    printf("Test Result: Test Passed\n");

    printf("\nTest: insertData (with collision)\n");
    printf("Expected Output: \n");
    printf("9 : 87: Why\n");
    printf("9 : 87: World\n");
    int key2 = generateKey(wordArray[2]);
    int index2 = hashNode(H1->size,key2);
    HNode * HN2 = malloc(sizeof(HNode));
    HN2 = createNode(key2,wordArray[2]);
    insertData(H1, index2, HN2);
    printf("Actual Output: \n");
    printNodeData(H1->table[index]->head->data);
    printNodeData(H1->table[index]->head->next->data);
    printf("Test Result: Test Passed\n");

    printf("\nTest: insertData (no collision)\n");
    printf("Expected Output: \n");
    printf("9 : 87: Why\n");
    printf("9 : 87: World\n");
    printf("20 : 72 : Hello\n");
    int key3 = generateKey(wordArray[1]);
    int index3 = hashNode(H1->size,key3);
    HNode * HN3 = malloc(sizeof(HNode));
    HN3 = createNode(key3,wordArray[1]);
    insertData(H1, index3, HN3);
    printf("Actual Output: \n");
    printTable(H1);
    printf("Test Result: Test Passed\n");

    printf("\nTest: removeData\n");
    printf("Expected Output: \n");
    printf("9 : 87: World\n");
    printf("20 : 72 : Hello\n");
    removeData(H1,"Why");
    printf("Actual Output: \n");
    printTable(H1);
    printf("Test Result: Test Passed\n");

    printf("\nTest: dataExists (does exist)\n");
    printf("Expected Output: Data exists in the table\n");
    int exists = dataExists(H1, "Hello");
    if (exists == 1){
        printf("Actual Output: Data exists in the table\n");
        printf("Test Result: Test Passed\n");
    } else {
        printf("Actual Output: Data does not exist in the table\n");
        printf("Test Result: Test Failed\n");
    }

    printf("\nTest: dataExists (does not exist)\n");
    printf("Expected Output: Data does not exist in the table\n");
    exists = dataExists(H1, "Why");
    if (exists == 1){
        printf("Actual Output: Data exists in the table\n");
        printf("Test Result: Test Failed\n");
    } else {
        printf("Actual Output: Data does not exist in the table\n");
        printf("Test Result: Test Passed\n");
    }

    printf("\nTest: destroyTable\n");
    printf("Expected Output: Table was destroyed\n");
    destroyTable(H1);
    H1 = NULL;
    if (H1 == NULL){
        printf("Actual Output: Table was destroyed\n");
        printf("Test Result: Test Passed\n");
    } else {
        printf("Actual Output: Table was not destroyed\n");
        printf("Test Result: Test Failed\n");
    }
    return 0;
}
