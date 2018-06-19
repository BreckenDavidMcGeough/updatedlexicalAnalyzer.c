#include <stdio.h>
#include <stdlib.h>
typedef const size_t cu4;
void locationofSpaces(int *locationSpaces, char *file);
int classifyChar(char *word);
void lexTuple(int *locationSpaces, char *file, char **ptr,int *px);
int main(){
    char *file = "int x = 10";
    int x = 0;
    int *px = &x;
    int *locations = malloc(sizeof(int) * strlen(file));
    //char tuples is a pointer to an array of char pointers which will point to another array of characters
    char **tuples = malloc(sizeof(char *) * strlen(file));
    locationofSpaces(locations, file);
    lexTuple(locations, file, tuples, px);
    for(int i = 0; i < 15;i++){
        printf("%c ", *(tuples)[i]);
    }
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
void lexTuple(int *locationSpaces, char *file, char **ptr,int *px){
    size_t start = *(locationSpaces+*px);
    size_t stop = *(locationSpaces+(*px+1));
    int *p = malloc(sizeof(int));
    *p = 0;
    char *word = malloc(sizeof(char)*(stop-start));
    *(ptr+*px) = malloc(sizeof(char) * (strlen(word)+*p));
    int y = 0;
    if(*px == 0){
        for(int i = 0; i < start; i++){
            *(word+i) = *(file+i);
            (ptr+*px)[i] = &file[i];
            if(i == start-1){
                break;
            }
        }
    }else{
        for(; start < stop; start++){
            *(word+y) = *(file+start);
            (ptr+*px)[y] = &file[start];
            y++;
            if(start == stop){
                break;
            }
        }
    }
    char *classifychar;
    int classify = classifyChar(word);
    switch(classify){
        case 0:
            classifychar = ":identifier/";
            break;
        case 1:
            classifychar = ":operator/";
            break;
        case 2:
            classifychar = ":literal/";
            break;
        case 3:
            classifychar = ":seperator/";
            break;
        default:
            classifychar = ":error/";
            break;
    }
    *p = strlen(classifychar);
    int z = 0;
    for(int l = (stop-start)+1; l <= (*p+(stop-start));l++){
        (ptr+*px)[l] = &classifychar[z];
        z++;
    }
    *px += 1;
    if(*px < sizeof(locationSpaces)/sizeof(*locationSpaces)){
        //lexTuple(locationSpaces, file, ptr, px);
    }
}

