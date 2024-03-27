/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 2
Full Name  :Hao Han Kao
Student ID#:151604220
Email      :hkao@myseneca.ca
Section    :NEE

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "core.h"
#include <ctype.h>
#include <string.h>
//
// Copy your work done from Milestone #1 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
// - Also copy the commented "sections" to help with finding functions quickly!
//

void clearInputBuffer(void)
{
// Discard all remaining char's from the standard input buffer:
while (getchar() != '\n')
{
; // do nothing!
}
}


// Wait for user to input the "enter" key to continue
void suspend(void)
{
printf("<ENTER> to continue...");
clearInputBuffer();
putchar('\n');
}



int inputInt(void) {
    int value, scanfResult;
    char end;

    do {
        scanfResult = scanf("%d%c",&value,&end);
        if (scanfResult!=2 || end != '\n'){
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }   
    } while (scanfResult!=2 || end != '\n');

    return value;
}

int inputIntPositive(void){
    int value ;
  
    
    do {
        value =inputInt();
        if ( value <=0) {
            printf("ERROR! Value must be > 0: ");
        }
            
        } while (value <=0);
    
    return value;
}

int inputIntRange(int lowerBound ,int upperBound){
    int value;
     do {
        value =inputInt();
        
        if (value < lowerBound || value > upperBound) {
            printf("ERROR! Value must be between %d and %d inclusive: ", lowerBound, upperBound);
        }
    } while (value < lowerBound || value > upperBound);
    return value;
}

char inputCharOption(const char validChars[]) {
    char value;
    int i;
    int isVaild =0;
   do {
         value= getchar();
         clearInputBuffer();
     for (i = 0; validChars[i] != '\0' && !isVaild; i++) {
            if (validChars[i]==value){
               
                isVaild=1;}
        }
        if(!isVaild ){
            printf("ERROR: Character must be one of [%s]: ",validChars);
        }
    
    } while (isVaild == 0);
   return value;
   
};

void inputCString(char* chars,int min,int max){
    char result[max+1]; 
    int i, length;
    do {
       scanf("%[^\n]", result);
       clearInputBuffer();
       length=0;
       for (i=0;result[i] !='\0'; i++){
            length+=1;
       }
       
       
        if (length < min || length > max ){
            if (min == max) {
                printf("ERROR: String length must be exactly %d chars: ",min);
            }
            else if(length> max) {
                printf("ERROR: String length must be no more than %d chars: ",max);
            }
            else {
                printf("ERROR: String length must be between %d and %d chars: ",min,max);
            }

    }
    }while(length < min || length > max);

    stpcpy(chars, result);
    
}

void displayFormattedPhone(const char* str){

    if (str!= NULL){
        int length=0, i;
        for (i=0; str[i]!='\0';i++){
            if ((int)str[i]>=48 && (int)str[i]<=57){
               
                length+=1;
            }
            else{
                 break;
            }
        
        }


        if (length== 10){
            printf("(%c%c%c)%c%c%c-%c%c%c%c",str[0],str[1],str[2],str[3],
            str[4],str[5],str[6],str[7],str[8],str[9]);
        }
        else{
         printf("(___)___-____");
        }

    } else{
         printf("(___)___-____");
    }
    
    
}



