/*
 @file HashMap.c
 @author Miriam Snow
 @date November 2017
 @brief File containing the functions of a hash map
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "HashMap.h"
#include "LinkedListAPI.h"
#include "Dictionary.h"

HTable *createTable(size_t size, int (*hashFunction)(size_t tableSize, int key),void (*destroyData)(void *data),void (*printNode)(void *toBePrinted)){
    HTable * H1 = malloc(sizeof(HTable)*size);
    H1->table = malloc(sizeof(List)*size);
    H1->size = size;
    H1->hashFunction = hashFunction;
    H1->destroyData = destroyData;
    H1->printNode = printNode;
    return H1;
}

HNode * createNode(int key, void *data){
    HNode * HN1 = malloc(sizeof(HNode));
    HN1->key = key;
    HN1->data = data;
    return HN1;
}

void destroyTable(HTable *hashTable){
    for (int i=0; i<hashTable->size; i++){
        if (hashTable->table[i] != NULL){
            Node * curr = hashTable->table[i]->head;
            while (curr != NULL){
                removeData(hashTable, curr->data);
                curr = curr->next;
            }
            deleteList(hashTable->table[i]);
        }
    }
    free(hashTable->table);
    free(hashTable);
}

void insertData(HTable *hashTable, int index, void *data){
    HNode * theData = data;
    if (hashTable->table[index] == NULL){
        List * L1 = initializeList(printNode, deleteListNode, compare);
        Node * N1 = initializeNode(theData);
        insertBack(L1,N1);
        hashTable->table[index] = malloc(sizeof(List));
        hashTable->table[index] = L1;
    } else {
        List*L1 = hashTable->table[index];
        Node * N1 = initializeNode(theData);
        insertBack(L1,N1);
    }
}

void *lookupData(HTable *hashTable, int index){
    Node * theNode = hashTable->table[index]->head;
    if (theNode != NULL){
        while (theNode != NULL){
            printNodeData(theNode->data);
            theNode = theNode->next;
        }
        return hashTable->table[index];
    }
    else {
        return NULL;
    }
}

void printTable(HTable *Map){
    int size = Map->size;
    for(int i = 0; i<size; i++){
        if (Map->table[i] != NULL){
            lookupData(Map, i);
        }
    }
}

void removeData(HTable *hashTable, void * data) {
    int key = generateKey(data);
    int index = hashNode(hashTable->size, key);
    Node * curr = hashTable->table[index]->head;
    while (curr != NULL){
        if (strcmp(((HNode*)(curr->data))->data, data) == 0){
            deleteNodeFromList(hashTable->table[index], curr);
            curr = NULL;
        } else {
            curr = curr->next;
        }
    }
}
