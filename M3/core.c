/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  : Hao Han Kao
Student ID#: 151604220
Email      : hkao@myseneca.ca
Section    : NEE

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "core.h"
#include <string.h>
#include <ctype.h>

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
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

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//
// Copy your work done from Milestone #2 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
//

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

int inputInt(void)
{
    int value, scanfResult;
    char end;

    do
    {
        scanfResult = scanf("%d%c", &value, &end);
        if (scanfResult != 2 || end != '\n')
        {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
    } while (scanfResult != 2 || end != '\n');

    return value;
}

int inputIntPositive(void)
{
    int value;

    do
    {
        value = inputInt();
        if (value <= 0)
        {
            printf("ERROR! Value must be > 0: ");
        }

    } while (value <= 0);

    return value;
}

int inputIntRange(int lowerBound, int upperBound)
{
    int value;
    do
    {
        value = inputInt();

        if (value < lowerBound || value > upperBound)
        {
            printf("ERROR! Value must be between %d and %d inclusive: ", lowerBound, upperBound);
        }
    } while (value < lowerBound || value > upperBound);
    return value;
}

char inputCharOption(const char validChars[])
{
    char value[3];
    int i, valid = 0;
    do
    {
        scanf("%2[^\n]", value);
        clearInputBuffer();
        if (strlen(value) != 1)
        {
            printf("ERROR: Character must be one of [%s]: ", validChars);
        }
        else
        {
            for (i = 0; validChars[i] != '\0'; i++)
            {
                if (value[0] == validChars[i])
                {
                    valid = 1;
                    break;
                }
            }
            if (valid == 0)
            {
                printf("ERROR: Character must be one of [%s]: ", validChars);
            }
        }

    } while (valid == 0);

    return value[0];
}

void inputCString(char *chars, int min, int max)
{
    char result[100];
    int i, length;
    do
    {
        scanf("%[^\n]", result);
        clearInputBuffer();
        length = 0;
        for (i = 0; result[i] != '\0'; i++)
        {
            length += 1;
        }

        if (length < min || length > max)
        {
            if (min == max)
            {
                printf("ERROR: String length must be exactly %d chars: ", min);
            }
            else if (length > max)
            {
                printf("ERROR: String length must be no more than %d chars: ", max);
            }
            else
            {
                printf("ERROR: String length must be between %d and %d chars: ", min, max);
            }
        }
    } while (length < min || length > max);

    stpcpy(chars, result);
}

void displayFormattedPhone(const char *str)
{

    if (str != NULL)
    {
        int length = 0, i;
        for (i = 0; str[i] != '\0'; i++)
        {
            if ((int)str[i] >= 48 && (int)str[i] <= 57)
            {

                length += 1;
            }
            else
            {
                break;
            }
        }

        if (length == 10)
        {
            printf("(%c%c%c)%c%c%c-%c%c%c%c", str[0], str[1], str[2], str[3],
                   str[4], str[5], str[6], str[7], str[8], str[9]);
        }
        else
        {
            printf("(___)___-____");
        }
    }
    else
    {
        printf("(___)___-____");
    }
}

void inputPhoneNumber(char *phone)
{
    char input[100];
    int length, i, valid = 1;
    do
    {
        scanf("%[^\n]", input);
        clearInputBuffer();
        length = strlen(input);

        if (length != 10)
        {
            printf("Invalid 10-digit number! Number: ");
        }
        else
        {
            for (i = 0; input[i] != '\0'; i++)
            {
                if (!isdigit(input[i]))
                {
                    valid = 0;
                    break;
                }
            }
            if (valid == 0)
            {
                printf("Invalid 10-digit number! Number: ");
            }
            else
            {
                strcpy(phone, input);
            }
        }
    } while (length != 10 || valid == 0);
};
