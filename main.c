#include <stdio.h>
#include <stdlib.h>
typedef const size_t cu4;
void locationofSpaces(int *locationSpaces, char *file);
int classifyChar(char *word);
void lexTuple(int *locationSpaces, char *file, char **ptr,int *px, char **ptrToken);
int main(){
    char *file = "int x = 10";
    cu4 sizeFile = sizeof(file)/sizeof(*file);
    int *locations = malloc(sizeFile * sizeof(int));
    locationofSpaces(locations, file);
    char *tokens = calloc(sizeof(locations)/sizeof(*locations),sizeof(char));
    char **ptr = &tokens;
    int x = 0;
    int *px = &x;
    char *pToken = calloc(sizeof(locations)/sizeof(*locations),sizeof(char));
    char **ptrToken = &pToken;
    lexTuple(locations, file, ptr,px,ptrToken);
    printf("%s ", &tokens[0]);
    printf("%s ", &pToken[0]);
    return 0;
}
void locationofSpaces(int *locationSpaces, char *file){
    char alpha[47] = "abcdefghijklmnopqrstuvwxyz0123456789+-/*={}[];.";
    int y = 0;
    for(int i = 0; i < sizeof(file)/sizeof(*file); i++){
        int x = 0;
        for(int l = 0; l < 47;l++){
            if(*(file+i) == *(alpha+l)){
                x ++;
            }else{
                if(l == 46 && x == 0){
                    *(locationSpaces+y) = i;
                    y++;
                    break;
                }else{
                    if(l == 46 && x > 0){
                        break;
                    }
                }
            }
        }
    }
}
int classifyChar(char *word){
    int classify = 0;
    char operator[] = "+=-0000000";
    char literal[] = "1234567890";
    char seperator[] = ";{}()00000";
    for(int i = 0; i < sizeof(operator)/sizeof(*operator); i++){
        if(word == *(operator+i)){
            classify = 1;
        }
        if(word == *(literal+i)){
            classify = 2;
        }
        if(word == *(seperator+i)){
            classify = 3;
        }
    }
    return(classify);
}
void lexTuple(int *locationSpaces, char *file, char **ptr,int *px, char **ptrToken){
    size_t start = *(locationSpaces+*px);
    size_t stop = *(locationSpaces+(*px+1));
    char *word = malloc(sizeof(char)*(stop-start));
    int y = 0;
    if(*px == 0){
        for(int i = 0; i <= start; i++){
            *(word+y) = *(file+i);
            y++;
            if(i == start-1){
                break;
            }
        }
    }else{
        for(; start < stop; start++){
            *(word+y) = *(file+start);
            y++;
            if(start == stop){
                break;
            }
        }
    }
    *(ptr+*px) = word;
    char *classifychar = calloc(20,sizeof(char));
    int classify = classifyChar(word);
    switch(classify){
        case 0:
            classifychar = "identifier";
            break;
        case 1:
            classifychar = "operator";
            break;
        case 2:
            classifychar = "literal";
            break;
        case 3:
            classifychar = "seperator";
            break;
        default:
            classifychar = "error";
            break;
    }
    *(ptrToken+*px) = classifychar;
    *px += 1;
    if(*px < sizeof(locationSpaces)/sizeof(*locationSpaces)){
        lexTuple(locationSpaces, file, ptr, px, ptrToken);
    }
}
