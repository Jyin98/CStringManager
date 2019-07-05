#include <stdio.h>
#include <stdlib.h>

//S_Manager.c

/* s_clear: frees allocated memory of a string. does not allow string literals. */
void s_clear(char * word)
{
    //note: Does not accept quotation as parameters. e.g, "example" is a bad input.
    if(word!=NULL){
        free(word);
    }
}

/* s_input: takes an unbuffered input and returns a char array pointer */
char * s_input(void)
{
    int length=20;
    char c;
    char * word = malloc(sizeof(char)*length);
    int index=0;

    if(word!=NULL){
		//build the string and expand memory when needed. take input while 'enter' key is not pressed.
        do {
            c = getchar();
            if(c!='\n'){
                if(index<length-1){
					//append the latest character if allotted space has not been used up yet.
                    word[index]=c;
                    index++;
                } else {
					//expand the allotted space and append the character if allocated space is exceeded.
                    length=length*10;
                    word = realloc(word, sizeof(char)*length);
                    if(word!=NULL){
                        word[index]=c;
                        index++;
                    } else {
                        printf("s_input: Error. Failed to allocate memory to string.\n");
                        exit(0);
                    }
                }
            }
        } while(c!='\n');
        
		//fit memory allocation to the size of the string after determining the full input
        word = realloc(word, sizeof(char)*(index+1));
        if(word!=NULL){
            word[index]='\0';
        } else {
            printf("s_input: Error. Failed to allocate memory to string.\n");
        }
    } else {
        printf("s_input: Error. Failed to allocate memory to string.\n");
    }

    return word;
}

/* s_len: returns the length of a string */
int s_len(char * word)
{
    int len=-1;
    if(word!=NULL){
        len=0;
        while(word[len]!='\0'){
            len++;
        }
    }    
    return len;
}

/* s_print: prints a string */
void s_print(char * word)
{
    int index=0;
    if(word!=NULL){
        while(word[index]!='\0'){
            printf("%c",word[index]);
            index++;
        }
    }
}

/* s_contain: search for a character inside a string */
int s_contain(char * word, char * target)
{   
    //null for -1, not found for 0, 1 for found.
    int result = -1;
    int match = 1;
    int wlen = s_len(word);
    int tlen = s_len(target);

    if(word && target){
        result = 0;
        if(wlen>=tlen){
            for(int i=0; i<wlen; i++){
                match = 1;
                for(int j=0; j<tlen; j++){
                    if(word[i+j]!=target[j]){
                        match=0;
                        break;
                    }
                }
                
                if(match==1){
                    result=1;
                    break;
                }
            }
        }
    } else {
        printf("s_contain: Error. Null input detected.\n");
    }
    return result;
}

/* s_combine: concatenates a string */
char * s_combine(char * word1, char * word2)
{
    //concatenates two word1 and word2.
    int len1 = s_len(word1);
    int len2 = s_len(word2);
    char * combined = malloc(sizeof(char)*(len1+len2+1));
    
    if(combined!=NULL){
        //len1 without null + len2 without null + 1 extra for null
        for(int i=0; i<len1+len2+1; i++){
            if(i<len1){
                combined[i]=word1[i];
            } else {
                combined[i]=word2[i-len1];
            }
        }
    } else {
        printf("s_combine: Error. Failed to allocate memory to string.\n");
    }

    return combined;
}

/* s_compare: determines if two string is the same */
int s_compare(char * word1, char * word2)
{
    //Compares two words for exact match
    int result = -1;
    int match = 1;
    int wlen1 = s_len(word1);
    int wlen2 = s_len(word2);
    
    if(word1 && word2){
        result = 0;
        if(wlen1==wlen2){
            result = 1;
            for(int i=0; i<wlen1; i++){
                if(word1[i]!=word2[i]){
                    result = 0;
                    break;
                }
            }
        }
    }
    
    return result;
}
