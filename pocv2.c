//Author: Neel Joshi
//This is a sort of proof of concept for a word autofill using a Trie

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TOT_CHAR 128 //total number of characters

//represents a letter in the trie
struct node {
    int isEnd;
    struct node* children [TOT_CHAR];

};

/*
    Creates a new node representing a letter int he trie
    param: [int end] represents whether the letter that the node represents is the last letter of a word
*/
struct node* newNode(int end){

    struct node* t = (struct node*)malloc(sizeof(struct node));
    t-> isEnd = end;

    for (int i = 0; i < TOT_CHAR; i++){
        t->children[i] = NULL;
    }

    return t;

}

/*
    Adds a word to a trie character by character (creating new node for characters if they do not exist in the trie)
    param: [char str[]] is the string to be added
    param: [struct node* root] is the pointer to the root node of the trie
*/
void addWord (char str[], struct node* root) {

    int i = 0;
    struct node* curr = root;
    while (str[i] != '\0'){
        int index = str[i]; 
        if (curr->children[index] == NULL) {
            curr->children[index] = newNode(0);
        }
        curr = curr->children[index];
        i++;
    }
    curr->children[10] = newNode(0);
    curr = curr->children[10];
    curr->isEnd = 1;
}


//helper method for autoFill(...)
/*
    Prints the words available in the tree given a certain prefix and position of that prefix in the trie
    param: [char pref[]] will be the same prefix as passed in autoFill(...)
    param: [struct node* root] pointer to the note of the subtree starting at the end of the prefix
        NOTE** this is not a pointer to the root of the trie
        if the prefix is `met`, then [struct node* root] will point to the node representing `t`
*/
void printWords(char pref[], struct node* root) {

    if (root->isEnd) {
        printf("%s", pref);
    }

    int i = 0;
    struct node* curr = root;

    while (i < TOT_CHAR) {

        if (curr->children[i] != NULL) {
            
            char temp[100];
            strcpy(temp, pref);
            
            char c[2];
            c[0] = i;
            c[1]= '\0';
            
            strcat(temp, c);
            
            printWords(temp, curr->children[i]);
        }

        i++;
    }

}

/*
    Autofills for a certain prefix 
    param: [char pref[]] is the prefix
    param: [struct node* root] is a pointer to the root node of the trie
*/
void autoFill(char pref[], struct node* root) {
    int i = 0;
    char prefix[100] = "";
    struct node* curr = root;

    //gets to prefix position in the trie
    while (pref[i] != '\0') {
        char c = pref[i];
        strcat(prefix, &c);

        int index = c;
        if (curr->children[index] == NULL) return;
        curr = curr->children[index];

        i++;
    }
    prefix[i] = '\0';

    printWords(prefix, curr);
    printf("\n");

}

int main() {

    //root of the trie
    struct node* root = newNode(0);

    //adding words from an external file to the trie
    
    FILE *words = fopen("words.txt", "r");

    char fileStr[100];

    while (fgets(fileStr, 100, words) != NULL) {
        addWord(fileStr, root);
    }
    

    //kind of a demo of how the trie works--
    /*
    addWord("hello", root);
    printf("%d %d\n", root->children[104-97] == NULL, root->isEnd);
    printf("%d %d\n", root->children[104-97]->children[101-97] == NULL, root->children[104-97]->children[101-97]->isEnd);
    printf("%d %d\n", root->children[104-97]->children[101-97]->children[108-97] == NULL, root->children[104-97]->children[101-97]->children[108-97]->isEnd);
    printf("%d %d\n", root->children[104-97]->children[101-97]->children[108-97]->children[108-97] == NULL, root->children[104-97]->children[101-97]->children[108-97]->children[108-97]->isEnd);
    printf("%d %d\n", root->children[104-97]->children[101-97]->children[108-97]->children[108-97]->children[111-97] == NULL, root->children[104-97]->children[101-97]->children[108-97]->children[108-97]->children[111-97]->isEnd);
    */

    //getting input from the user
    printf("Type something and hit enter to end\n");

    char input[100];
    input[0] = '\0';

    char ci[2];
    ci[1] = '\0';

    //adding user's input words into the trie using spaces as delimiters
    int c;
    while ( (c = getchar()) != '\n') {
        
        if (c != ' ') {
            ci[0] = c;
            strcat(input, ci);
        } else {
            addWord(input, root);
            input[0] = '\0';
        }

    } addWord(input, root); //this final addWord() catches the last word before the new line

    char prefix[100];

    printf("Enter the prefix: ");
    scanf("%s", prefix);

    autoFill(prefix, root);

    return 0;
}