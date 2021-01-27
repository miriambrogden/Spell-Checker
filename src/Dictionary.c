/*
 @file Dictionary.c
 @author Miriam Snow
 @date November 2017
 @brief File containing the functions of a dictionary and user defined functions of a hashmap and linked list
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Dictionary.h"
#include "LinkedListAPI.h"
#include "HashMap.h"

int dataExists(HTable *hashTable, void * data){
    char theWord[100];
    char theData[100];
    strcpy(theData,data);
    int key = generateKey(theData);
    int index = hashNode(hashTable->size,key);
    if (hashTable->table[index] != NULL){
        Node * curr = hashTable->table[index]->head;
        while (curr != NULL){
            strcpy(theWord, ((HNode*)(curr->data))->data);
            makeWordLower(theWord);
            makeWordLower(theData);
            if (strcmp(theWord, theData) == 0){
                return 1;
            } else {
                curr = curr->next;
            }
        }
    }
    return 0;
}

int compareFile(char * fileName, HTable * H1){
    FILE * fptr = fopen(fileName, "r");
    if (fptr == NULL){
        return 0;
    } else {
        int size = 0;
        fseek(fptr, 0, SEEK_END);
        size = ftell(fptr);
        if (size == 0){
            return 0;
        } else {
            fseek(fptr, 0, SEEK_SET);
            char buffer[100];
            int lines = 0;
            int i = 0;
            List * found = initializeList(printNode, deleteListNode, compare);
            List * notfound = initializeList(printNode, deleteListNode, compare);
            while (fgets(buffer,100,fptr) != NULL){
                lines++;
            }
            fseek(fptr, 0, SEEK_SET);
            char fileArray[lines][100];
            while (fgets(buffer,100,fptr) != NULL){
                removeNewline(buffer);
                strcpy(fileArray[i],buffer);
                i++;
            }
            for (int i = 0; i<lines; i++){
                Node * aNode = initializeNode(fileArray[i]);
                int exists = dataExists(H1, fileArray[i]);
                if (exists == 1){
                    insertBack(found, aNode);
                } else {
                    insertBack(notfound, aNode);
                }
            }
            printf("File processed by Spell Check: %s\n", fileName);
            Node * curr = notfound->head;
            while (curr != NULL){
                printNode(curr->data);
                printf(" was not found in the dictionary\n");
                curr = curr->next;
            }
            int correct = count(found);
            int incorrect = count(notfound);
            printf("Summary: \n");
            printf("Correctly Spelt Words: %d\n", correct);
            printf("Incorrectly Spelt Words: %d\n", incorrect);
            printf("Enter any key to go back to the main menu: ");
            char * input2 = malloc(sizeof(char));
            do {
                fgets(input2, 100, stdin);
            } while (strcmp(input2, "") == 0);
            return 1;
        }
    }
}

int generateKey(void * data){
    char * word = malloc(sizeof(char));
    strcpy(word, data);
    char letter = toupper(word[0]);
    int ascii = (int)letter;
    return ascii;
}

void removeNewline(char line[]){
    if(line[strlen(line)-1] == '\n'){
        line[strlen(line)-1] = '\0';
    }
}

int hashNode(size_t size, int key){
    int index = key % size;
    return index;
}

void destroyNodeData(void *data){

}

void printNodeData(void *toBePrinted){
    char word[100];
    strcpy(word, (char*)(((HNode*)(toBePrinted))->data));
    int key = generateKey(word);
    int index = hashNode(26,key);
    printf("%d : ", index);
    printf("%d : ",(int)(((HNode*)(toBePrinted))->key));
    printf("%s\n",(char*)(((HNode*)(toBePrinted))->data));
}

void printMenu (){
    printf("1. Add a word to a dictionary\n");
    printf("2. Remove a word from a dictionary\n");
    printf("3. Spell check a file\n");
    printf("4. Show dictionary words\n");
    printf("5. Quit\n");
}

void makeWordLower(char * word){
    for(int i = 0; i<strlen(word); i++){
        word[i] = tolower(word[i]);
    }
}

int getInt(char* prompt, char max){
    char userInt[100] = "";
    int flag = 1;
    int ascii = 0;
    int maxAscii = (int)(max);
    int zero = (int)('0');
    while(flag != 0){
        flag = 0;
        printf("%s", prompt);
        fgets(userInt, 100, stdin);
        removeNewline(userInt);
        if (strcmp(userInt, "") == 0){
            flag ++;
        }
        if (max != '0'){
            ascii = (int)(userInt[0]);
            if (ascii > maxAscii || ascii == zero){
                flag++;
            }
        }
        for (int j = 0; j<strlen(userInt); j++){
            if (!isdigit(userInt[j])){
                flag++;
            }
        }
        if (flag > 0){
            printf("Error! ");
        }
    }
    int numInts = atoi(userInt);
    return numInts;
}

void printNode(void *toBePrinted){
    printf("%s",(char*)(toBePrinted));
}

void deleteListNode(void *toBeDeleted){

}

int compare(const void *first,const void *second){
    return 0;
}

int count(List * L1){
    int count = 0;
    Node * curr = L1->head;
    while (curr != NULL){
        count++;
        curr = curr->next;
    }
    return count;
}

int checkString(char * string){
    for (int i = 0; i < strlen(string); i++){
        if (string[i] == ' ') {
            return 1;
        }
    }
    for (int i = 0; i < strlen(string); i++){
        if (!isalpha(string[i])){
            return 1;
        }
    }
    return 0;
}
