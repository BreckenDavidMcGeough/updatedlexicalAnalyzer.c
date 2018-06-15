
//
//  main.c
//  ctest
//
//  Created by Brecken McGeough on 5/28/18.
//  Copyright © 2018 Brecken McGeough. All rights reserved.
//

#include <stdio.h>
#include <string.h>
typedef unsigned short u32;
enum binaryAlphabet{a=1,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z};
int checkifSpace(char keyword);
void locationofSpaces(char file[], int locations[]);
int classifyKeyword(char keychar[]);
void assembleTuples(char file[], char *assembledTuples[sizeof(file)/sizeof(*(file+1))], int locations[], int *px);
float to_binary(char keyword);
int main(){
    int x = 0;
    int *pX = &x;
    char file[] = "int x = 10;";
    int locations[sizeof(file)/sizeof(*file)] = {};
    locationofSpaces(file, locations);
    char *assembledTuples[sizeof(file)/sizeof(*(file+1))] = {};
    assembleTuples(file, assembledTuples, locations, pX);
    printf("%c ", assembledTuples[0][0]);
    return 0;
}
int checkifSpace(char keyword){
    int check = 2;
    char vocab[] = "abcdefghijklmnopqrstuvwxyz1234567890=;{}(),.";
    int size = sizeof(vocab)/sizeof(*vocab);
    for(int i = 0; i < size; i++){
        if(*(vocab+i) == keyword){
            check = 1;
            break;
        }else{
            check = 0;
        }
    }
    return(check);
}
void locationofSpaces(char file[], int locations[]){
    int size = sizeof(file)/sizeof(*file);
    unsigned int n = 0;
    for(int i = 0; i < size; i ++){
        if(checkifSpace(*(file+i)) == 0){
            *(locations+n) = i;
            n = n+1;
        }
    }
}
float to_binary(char keyword){
    float bin = 0.0;
    enum binaryAlphabet word = keyword;
    switch(word){
        case 1:
            bin += .01000001;
            break;
        case 2:
            bin += .01000010;
            break;
        case 3:
            bin += .01000011;
            break;
        case 4:
            bin += .01000100;
            break;
        case 5:
            bin += .01000101;
            break;
        case 6:
            bin += .01000110;
            break;
        case 7:
            bin += .01000111;
            break;
        case 8:
            bin += .01001000;
            break;
        case 9:
            bin += .01001001;
            break;
        case 10:
            bin += .01001010;
            break;
        case 11:
            bin += .01001011;
            break;
        case 12:
            bin += .01001100;
            break;
        case 13:
            bin += .01001101;
            break;
        case 14:
            bin += .01001110;
            break;
        case 15:
            bin += .01001111;
            break;
        case 16:
            bin += .01010000;
            break;
        case 17:
            bin += .01010001;
            break;
        case 18:
            bin += .01010010;
            break;
        case 19:
            bin += .01010011;
            break;
        case 20:
            bin += .01010100;
            break;
        case 21:
            bin += .0101110;
            break;
        default:
            bin += .0101010;
            break;
    }
    return bin;
}
int classifyKeyword(char keychar[]){
    int classify = 0;
    char operator[] = "+=-0000000";
    char literal[] = "1234567890";
    char seperator[] = ";{}()00000";
    for(int i = 0; i < sizeof(operator)/sizeof(*operator); i++){
        if(keychar == *(operator+i)){
            classify = 1;
        }
        if(keychar == *(literal+i)){
            classify = 2;
        }
        if(keychar == *(seperator+i)){
            classify = 3;
        }
    }
    return(classify);
}
void assembleTuples(char file[], char *assembledTuples[sizeof(file)/sizeof(*(file+1))], int locations[], int *px){
    char word[15] = "";
    int start = *(locations+*px);
    unsigned int pxOne = *px + 1;
    int stop = *(locations+pxOne);
    if(*px == 0){
        for(int i = 0; i < *(locations);i++){
            strncat(word, (file+start), 1);
        }
    }else{
        for(; start <= stop; start++){
            strncat(word, (file+start),1);
            if(start == stop){
                break;
            }
        }
    }
    *(assembledTuples+*px) = word;
    char *classifychar = "";
    int classify = classifyKeyword(word);
    switch(classify){
        case 0:
            *px += 1;
            classifychar = "identifier";
            *(assembledTuples+*px+1) = classifychar;
            break;
        case 1:
            *px += 1;
            classifychar = "operator";
            *(assembledTuples+*px+1) = classifychar;
            break;
        case 2:
            *px += 1;
            classifychar = "literal";
            *(assembledTuples+*px+1) = classifychar;
            break;
        case 3:
            *px += 1;
            classifychar = "seperator";
            *(assembledTuples+*px+1) = classifychar;
            break;
        default:
            *px += 1;
            classifychar = "error";
            *(assembledTuples+*px+1) = classifychar;
            break;
    }
    if(*(locations+*px) != 0){
        assembleTuples(file,assembledTuples,locations,px);
    }
}

