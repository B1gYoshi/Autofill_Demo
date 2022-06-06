//Author: Neel Joshi
//This is the first version of the proof of concept with only the lowercase letters of the alphabet

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TOT_LET 26

struct node {
    int isEnd;
    struct node* children [TOT_LET];

};

struct node* newNode(int end){

    struct node* t = (struct node*)malloc(sizeof(struct node));
    t-> isEnd = end;

    for (int i = 0; i < TOT_LET; i++){
        t->children[i] = NULL;
    }

    return t;

}

void addWord (char str[], struct node* root) {

    int i = 0;
    struct node* curr = root;
    while (str[i] != '\0'){
        int index = str[i] - 97; //97 is ascii for 'a'
        if (curr->children[index] == NULL) {
            curr->children[index] = newNode(0);
        }
        curr = curr->children[index];
        i++;
    }
    curr->isEnd = 1;
}


//helper method for autoFill(...)
void printWords(char pref[], struct node* root) {

    if (root->isEnd) {
        printf("Autofill: %s\n", pref);
    }

    int i = 0;
    struct node* curr = root;

    while (i < TOT_LET) {

        if (curr->children[i] != NULL) {

            char temp[100];
            strcpy(temp, pref);

            
            char c[2];
            c[0] = 97+i;
            c[1]= '\0';
            
            strcat(temp, c);
            printWords(temp, curr->children[i]);
        }

        i++;
    }

}

//prints autofill words for a given prefix
void autoFill(char pref[], struct node* root) {
    int i = 0;
    char prefix[100] = "";
    struct node* curr = root;

    //gets to prefix position in the trie
    while (pref[i] != '\0') {
        char c = pref[i];
        strcat(prefix, &c);

        int index = c - 97;
        if (curr->children[index] == NULL) return;
        curr = curr->children[index];

        i++;
    }
    prefix[i] = '\0';

    printWords(prefix, curr);

}

int main() {
    struct node* root = newNode(0);

    addWord("hel;lo", root);
    addWord("hel;p", root);

    /*
    printf("%d %d\n", root->children[104-97] == NULL, root->isEnd);
    printf("%d %d\n", root->children[104-97]->children[101-97] == NULL, root->children[104-97]->children[101-97]->isEnd);
    printf("%d %d\n", root->children[104-97]->children[101-97]->children[108-97] == NULL, root->children[104-97]->children[101-97]->children[108-97]->isEnd);
    printf("%d %d\n", root->children[104-97]->children[101-97]->children[108-97]->children[108-97] == NULL, root->children[104-97]->children[101-97]->children[108-97]->children[108-97]->isEnd);
    printf("%d %d\n", root->children[104-97]->children[101-97]->children[108-97]->children[108-97]->children[111-97] == NULL, root->children[104-97]->children[101-97]->children[108-97]->children[108-97]->children[111-97]->isEnd);
    */

    autoFill("he", root);

    return 0;

}