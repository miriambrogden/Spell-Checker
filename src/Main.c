/*
 @file Main.c
 @author Miriam Snow
 @date November 2017
 @brief File containing the main function
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "HashMap.h"
#include "LinkedListAPI.h"
#include "Dictionary.h"

int main (int argc, char ** argv){
    FILE * fptr = fopen(argv[1], "r");
    if (fptr == NULL){
        printf("Error opening file!\n");
    } else {
        int size = 0;
        fseek(fptr, 0, SEEK_END);
        size = ftell(fptr);
        if (size == 0){
            printf("File has no contents!\n");
        } else {
            fseek(fptr, 0, SEEK_SET);
            char buffer[1000];
            int index = 0;
            int key = 0;
            int i = 0;
            int m = 0;
            int input = 0;
            int lines = 0;
            char word[100][100];
            HTable * Map = malloc(sizeof(HTable));
            Map = createTable(26,hashNode,destroyNodeData,printNodeData);
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
            for (int j = 0; j<lines;j++){
                key = generateKey(fileArray[j]);
                index = hashNode(Map->size, key);
                HNode * HN1 = createNode(key,fileArray[j]);
                insertData(Map,index,HN1);
            }
            while (input != 5){
                printMenu();
                input = getInt("Please enter a menu option: ", '5');
                if (input == 1){
                    do {
                        printf("Please enter a word: ");
                        fgets(word[m], 100, stdin);
                        removeNewline(word[m]);
                    } while (checkString(word[m]) == 1);
                    int exists = dataExists(Map, word[m]);
                    if (exists == 0){
                        key = generateKey(word[m]);
                        index = hashNode(Map->size, key);
                        makeWordLower(word[m]);
                        HNode * HN2 = createNode(key,word[m]);
                        insertData(Map,index,HN2);
                        printf("The word was successfully added to the dictionary.\n");
                    } else {
                        printf("This word already exists in the dictionary.\n");
                    }
                    m++;
                }
                if (input == 2){
                    printf("Please enter a word: ");
                    fgets(word[m], 100, stdin);
                    removeNewline(word[m]);
                    int exists = dataExists(Map, word[m]);
                    if (exists == 1){
                        makeWordLower(word[m]);
                        removeData(Map, word[m]);
                        printf("The word was successfully removed from the dictionary.\n");
                    } else {
                        printf("Sorry, that word does not exists in the dictionary.\n");
                    }
                    m++;
                }
                if (input == 3){
                    printf("Please enter a filename: ");
                    char fileName2[100];
                    fgets(fileName2,100,stdin);
                    removeNewline(fileName2);
                    int comp = compareFile(fileName2, Map);
                    if (comp == 0){
                        printf("Error opening file\n");
                    }
                }
                if (input == 4){
                    printTable(Map);
                }
            }
            destroyTable(Map);
            Map = NULL;
        }
    }
    return 0;
}
