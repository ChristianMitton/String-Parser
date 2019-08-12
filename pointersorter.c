//Set up: ------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef int bool;
#define true 1
#define false 0

//Structs: ------------------------
typedef struct Node{
	int wordLength;
	int symbolIndex;
	char *word;
	char letter;
	struct Node *next;	
} Node;

//Method Signatures: ------------------------
void printLLInAlphabeticOrder(Node *head);
void printArray(char **array, int size);
char **selectionSort(char **array, int size);
Node *createWordNode(int wordLength, char *word);
Node *createLetterNode(char letter);
Node *createSymbolIndexNode(int symbolIndex);
void addToEndWordNode(Node **head, Node *target);
void addToEndLetterNode(Node **head, Node *target);
void addToEndIndexOfSymbolNode(Node **head, Node *target);
char *convertLetterLLToArrayOfLetters(Node *head);
bool isALetter(char character);
int sizeOfSmallestWord(char *w1, char *w2);

//Global Variables: ------------------------
Node *allWordsLL = NULL;
Node *symbolLL = NULL;

//Main code: ------------------------
int main(int argc, char **argv){
	if((argc > 2) || (argc == 1)){
		printf("Please give one string argument.\n");
		return 0;
	}

	/*------------------------------
 	Put all words from string into a linked list
  	--------------------------------*/
	int wordIndex = 1;	
	Node *letterLL = NULL;
	int wordLen = strlen(argv[wordIndex]);
	int letterCount = 0;
	
	while(letterCount < wordLen){
		char character = argv[wordIndex][letterCount];
		if(isALetter(character) == true) {
			Node *letterNode = createLetterNode(character);
			addToEndLetterNode(&letterLL, letterNode);
		} else {
			Node *symbolNode = createSymbolIndexNode(letterCount);
			addToEndIndexOfSymbolNode(&symbolLL, symbolNode);		
			if (letterLL != NULL){
				char *innerWordString = convertLetterLLToArrayOfLetters(letterLL);
				int lenOfInnerWord = strlen(innerWordString);
				Node *innerWord = createWordNode(lenOfInnerWord, innerWordString);
				addToEndWordNode(&allWordsLL, innerWord);
				letterLL = NULL;
			}
		}
		letterCount++;
	}
	char *convertedWord = convertLetterLLToArrayOfLetters(letterLL);
	int convertedWordLen = strlen(convertedWord);
	Node *word = createWordNode(convertedWordLen, convertedWord);
	addToEndWordNode(&allWordsLL,word);
	letterLL = NULL;

	/*-----------------------------
	Print words in descending order
 	-------------------------------*/	
	printLLInAlphabeticOrder(allWordsLL);

	return 0;
}

//Methods: ------------------------
void printLLInAlphabeticOrder(Node *head){
	/*---------------------------------------------------------
 	Convert linked list of words (wordLL) to an array
	---------------------------------------------------------*/
	Node *result = NULL;
	Node *ptr = head;
	int sizeOfList = 0;
	while(ptr != NULL){
		if(ptr->word != ""){
			sizeOfList++;
		}
		ptr = ptr->next;
	}
	ptr = head;
	char *wordArray[sizeOfList];
	int i = 0;
	while(ptr != NULL){
		if(ptr->word != ""){
			wordArray[i] = ptr->word;
			i++;
		}
		ptr = ptr->next;
	}

	/*---------------------------------------------------------
	Split wordArray into 2 arrays: one that contains words where
	the first letters are capital, the other where the the first
	letters are lowercase
  	-----------------------------------------------------------*/
	int numCapitals = 0;
	int numLowers = 0;
	for(i = 0; i < sizeOfList; i++){
		if(isupper(wordArray[i][0])){
			numCapitals++;
		} else if(islower(wordArray[i][0])) {
			numLowers++;
		}
	}

	char *capitals[numCapitals];	
	char *lowers[numLowers];	

	int x = 0;
	int k = 0;
	for(i = 0; i < sizeOfList; i++){
		if(isupper(wordArray[i][0])){
			capitals[k] = wordArray[i];
			k++;
		}
		if(islower(wordArray[i][0])){
			lowers[x] = wordArray[i];
			x++;
		}
	}

	/*---------------------------------------------------------
 	Sort uppercase array and lowercase arrays in ascending order
  	-----------------------------------------------------------*/
	char **sortedUpper = selectionSort(capitals,numCapitals);
	char **sortedLower = selectionSort(lowers,numLowers);
	
	/*---------------------------------------------------------
	put both sortedUpper and sortedLower into finalArray backwards 
	in order to have descending order
  	-----------------------------------------------------------*/
	char *finalArray[numCapitals+numLowers];
	int y = 0;
	
	for(i = numCapitals-1; i > -1; i--){
		finalArray[y] = sortedUpper[i];
		y++;
	}

	for(i = numLowers-1; i > -1; i--){
		finalArray[y] = sortedLower[i];
		y++;
	}

	/*------------------------
  	Print words in final array
	--------------------------*/
	printArray(finalArray,numLowers+numCapitals);
}


char **selectionSort(char **array, int size){
    
    int i, j, k, min_idx;
    for (i = 0; i < size; i++){
        min_idx = i;
        
        for(j = i+1; j < size; j++){
		char *currentWord = array[j];
		char *minValue = array[min_idx];
         	char currentWordFirstLetter = currentWord[0];
		char minValueFirstLetter = minValue[0];
		
		if(currentWordFirstLetter < minValueFirstLetter){
			min_idx = j;
		}
            	if(currentWordFirstLetter == minValueFirstLetter){
                	int sizeOfCurrentWord = strlen(currentWord);
                	int sizeOfMinValue = strlen(minValue);
                	int smallestWordSize = sizeOfSmallestWord(currentWord, minValue);
               
                	for(k = 1; k < smallestWordSize; k++){
				char currentWordLetter = currentWord[k];
				char minValueLetter = minValue[k];
			
				/*-----------------------------------------
 				If a letter is uppercase, add 33 to give it 
				priority over lowercase words
 				-------------------------------------------*/
				if(isupper(currentWordLetter)){
					currentWordLetter += 33;
				}
				if(isupper(minValueLetter)){
					minValueLetter += 33;
				}

                	        if(currentWordLetter == minValueLetter){
                            		continue;
                        	}
                        	if(currentWordLetter > minValueLetter){
                           		break;
                        	}
                        	if(currentWordLetter < minValueLetter){
                            		min_idx = j;
                            		break;
                        	}
			}
		}
        }
        char *temp = array[min_idx];
        array[min_idx] = array[i];
        array[i] = temp;
    }
	return array;
}


void printArray(char **array, int size){
	int i;
	for(i = 0; i<size; i++){
		printf("%s\n",array[i]);
	}
}

bool isALetter(char character){
	if(isalpha(character)) {
		return true;
	} else {
		return false;
	}
}

int sizeOfSmallestWord(char *w1, char *w2){
	int sizeOfSmallestWord = 0;
	int w1Size = strlen(w1);
	int w2Size = strlen(w2);
	if(w1Size > w2Size){
		sizeOfSmallestWord = w2Size;
	} else if(w1Size < w2Size){
		sizeOfSmallestWord = w1Size;
	} else {
		sizeOfSmallestWord = w1Size;
	}
	return sizeOfSmallestWord;
}

Node *createWordNode(int wordLength, char *word){
    	Node *ptr = malloc(sizeof(Node));
    	ptr->wordLength = wordLength;
    	ptr->word = strdup(word);
    	return ptr;
}

Node *createLetterNode(char letter){
	Node *ptr = malloc(sizeof(Node));	
	ptr->letter = letter;
	return ptr;
}

Node *createSymbolIndexNode(int symbolIndex){
	Node *ptr = malloc(sizeof(Node));
	ptr->symbolIndex = symbolIndex;
	return ptr;
}

void addToEndWordNode(Node **head, Node *target){
	if(*head == NULL) {
		(*head) = target;
		return;
	}
	Node *temp = createWordNode(target->wordLength, target->word);
	Node *ptr = (*head);
	while(ptr->next != NULL){
		ptr = ptr->next;
	}
	ptr->next = temp;
}

void addToEndLetterNode(Node **head, Node *target){
	if (*head == NULL) {
		(*head) = target;
		return;
	}
	Node *temp = createLetterNode(target->letter);
	Node *ptr = (*head);
	while(ptr->next != NULL){
		ptr = ptr->next;
	}
	ptr->next = temp;
}

void addToEndIndexOfSymbolNode(Node **head, Node *target){
	if (*head == NULL) {
		(*head) = target;
		return;
	}
	Node *temp = createLetterNode(target->symbolIndex);
	Node *ptr = (*head);
	while(ptr->next != NULL){
		ptr = ptr->next;
	}
	ptr->next = temp;
}

char *convertLetterLLToArrayOfLetters(Node *head){
	Node *ptr = head;
	int numLetters = 0;
   	while(ptr != NULL){
        	numLetters++;
        	ptr = ptr->next;
    	}
    	
	char *letters = (char *) malloc(sizeof(char)*(numLetters+1));
	letters[numLetters+1] = '\0';    
	
    	ptr = head;
    
    	int i = 0;
    	while (ptr != NULL) {
        	letters[i] = ptr->letter;
        	i++;
        	ptr = ptr->next;
    	}
	return letters;
}











