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

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"
#include "string.h"
#include <stdlib.h>

//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient *patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ",
               patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date *date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient *patient,
                         const struct Appointment *appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}

//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData *data)
{
    int selection;

    do
    {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do
    {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient *patient)
{
    int selection;

    do
    {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ",
               patient->patientNumber, patient->name);

        displayFormattedPhone(patient->phone.number);

        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData *data)
{
    int selection;

    do
    {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data); // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient); // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient); // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}

// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------

// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{

    int i, allInvalid = 0;

    displayPatientTableHeader();

    for (i = 0; i < max; i++)
    {

        if (patient[i].patientNumber != 0)
        {
            displayPatientData(&patient[i], fmt);
            allInvalid = 1;
        }
    }
    printf("\n");
    if (allInvalid == 0)
    {
        printf("*** No records found ***\n");
    }
}

// Search for a patient record based on patient number or phone number
// (Copy your code from MS#2)
void searchPatientData(const struct Patient patient[], int max)
{
    int selection;
    do
    {
        printf("Search Options\n"
               "==========================\n"
               "1) By patient number\n"
               "2) By phone number\n"
               "..........................\n"
               "0) Previous menu\n"
               "..........................\n");
        printf("Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            break;
        case 1:
            searchPatientByPatientNumber(patient, max);
            suspend();
            break;
        case 2:
            searchPatientByPhoneNumber(patient, max);
            suspend();
            break;
        }
    } while (selection != 0);
}

// Add a new patient record to the patient array
// (Copy your code from MS#2)
void addPatient(struct Patient patient[], int max)
{
    int index, newPatientNum;

    index = findPatientIndexByPatientNum(0, patient, max);
    if (index == -1)
    {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
    else
    {
        newPatientNum = nextPatientNumber(patient, max);
        patient[index].patientNumber = newPatientNum;
        inputPatient(&patient[index]);
        printf("*** New patient record added ***\n\n");
    }
}

// Edit a patient record from the patient array
// (Copy your code from MS#2)
void editPatient(struct Patient patient[], int max)
{
    int patientNum = 0;
    int index;

    printf("Enter the patient number: ");

    patientNum = inputIntPositive();
    index = findPatientIndexByPatientNum(patientNum, patient, max);
    if (index != -1)
    {
        printf("\n");
        menuPatientEdit(&patient[index]);
    }
    else
    {
        printf("ERROR: Patient record not found!\n");
    }
}

// Remove a patient record from the patient array
// (Copy your code from MS#2)
void removePatient(struct Patient patient[], int max)
{
    int patientNum;
    int index;
    char comfirmsRemove;

    printf("Enter the patient number: ");
    patientNum = inputIntPositive();
    printf("\n");

    index = findPatientIndexByPatientNum(patientNum, patient, max);
    if (index != -1)
    {
        displayPatientData(&patient[index], FMT_FORM);
        printf("\n");
        printf("Are you sure you want to remove this patient record? (y/n): ");
        comfirmsRemove = inputCharOption("yn");
        if (comfirmsRemove == 'y')
        {
            patient[index].patientNumber = 0;
            printf("Patient record has been removed!\n");
            printf("\n");
        }
        else
        {

            printf("Operation aborted.\n");
            printf("\n");
        }
    }
    else
    {
        printf("ERROR: Patient record not found!\n\n");
    }
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
// Todo:
//
void viewAllAppointments(struct ClinicData *data)
{

    displayScheduleTableHeader(NULL, 1);
    sortAppointments(data->appointments, data->maxAppointments);
    int i, patientIndex;
    int patientNum;
    for (i = 0; i < data->maxAppointments; i++)
    {
        if (data->appointments[i].date.year != 0)
        {
            patientNum = data->appointments[i].patientNumber;
            patientIndex = findPatientIndexByPatientNum(patientNum,
                                                        data->patients, data->maxPatient);
            displayScheduleData(&data->patients[patientIndex], &data->appointments[i], 1);
        }
    }

    printf("\n");
}

// View appointment schedule for the user input date
// Todo:

void viewAppointmentSchedule(struct ClinicData *data)
{

    int year, month, day;

    printf("Year        : ");
    year = inputIntPositive();
    printf("Month (1-12): ");
    month = inputIntRange(1, 12);

    if (month == 2)
    {
        if (year % 4 == 0)
        {
            printf("Day (1-29)  : ");
            day = inputIntRange(1, 29);
        }
        else
        {
            printf("Day (1-28)  : ");
            day = inputIntRange(1, 28);
        }
    }
    else if (month == 1 || month == 3 || month == 5 ||
             month == 7 || month == 8 || month == 10 || month == 12)
    {
        printf("Day (1-31)  : ");
        day = inputIntRange(1, 31);
    }
    else
    {
        printf("Day (1-30)  : ");
        day = inputIntRange(1, 30);
    }

    struct Date inputDate = {day, year, month};
    // Result
    int i;
    int patientNum, patientIndex;
    printf("\n");
    displayScheduleTableHeader(&inputDate, 0);
    sortAppointments(data->appointments, data->maxAppointments);
    for (i = 0; i < data->maxAppointments; i++)
    {

        patientNum = data->appointments[i].patientNumber;
        patientIndex = findPatientIndexByPatientNum(patientNum,
                                                    data->patients, data->maxPatient);

        if (year == data->appointments[i].date.year && month == data->appointments[i].date.month && day == data->appointments[i].date.day)
        {
            displayScheduleData(&data->patients[patientIndex], &data->appointments[i], 0);
        }
    }

    printf("\n");
}

// Add an appointment record to the appointment array
// Todo:
void addAppointment(struct Appointment appointments[], int maxAppointments, struct Patient patients[], int maxPatient)
{
    int patientNum, year, month, day, hour, mins;
    int patientIndex;

    printf("Patient Number: ");
    patientNum = inputIntPositive();
    patientIndex = findPatientIndexByPatientNum(patientNum, patients, maxPatient);
    if (patientIndex != 1)
    {
        int timeSlotValid;

        do
        {
            inputYearMonthDay(&year, &month, &day);
            int timeVaild = 0;
            do
            {
                printf("Hour (0-23)  : ");
                hour = inputIntRange(0, 23);
                printf("Minute (0-59): ");
                mins = inputIntRange(0, 59);
                if (hour < START || hour > END || mins % MINUTE_INTERVAL != 0 || (hour == END && mins > 0))
                {
                    printf("ERROR: Time must be between %d:00 and %d:00 in %d minute intervals.\n\n", START, END, MINUTE_INTERVAL);
                }
                else
                {
                    timeVaild = 1;
                }

            } while (timeVaild != 1);
            int i;
            int emptySpot;
            for (i = 0; i < maxAppointments; i++)
            {
                if (appointments[i].date.year == 0)
                {
                    emptySpot = i;
                }
            }

            timeSlotValid = 1;
            for (i = 0; i < maxAppointments; i++)
            {
                // match or not?

                if (appointments[i].date.year == year && appointments[i].date.month == month && appointments[i].date.day && appointments[i].time.hour == hour && appointments[i].time.min == mins)
                {
                    printf("\nERROR: Appointment timeslot is not available!\n\n");
                    timeSlotValid = 0;
                    break;
                }
            }
            if (timeSlotValid == 1)
            {
                appointments[emptySpot].patientNumber = patientNum;
                appointments[emptySpot].date.year = year;
                appointments[emptySpot].date.month = month;
                appointments[emptySpot].date.day = day;
                appointments[emptySpot].time.hour = hour;
                appointments[emptySpot].time.min = mins;
                printf("\n*** Appointment scheduled! ***\n\n");
            }

        } while (timeSlotValid == 0);
    }
    else
    {
        printf("ERROR: Patient record not found!\n");
    }

    //
}

// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment appointments[], int maxAppointments, struct Patient patients[], int maxPatient)
{

    int patientNum, year, month, day;
    int patientIndex;

    printf("Patient Number: ");
    patientNum = inputIntPositive();
    patientIndex = findPatientIndexByPatientNum(patientNum, patients, maxPatient);

    if (patientIndex != -1)
    {

        inputYearMonthDay(&year, &month, &day);
        int i;
        char comfirmsRemove;
        for (i = 0; i < maxAppointments; i++)
        {
            // match or not?
            if (appointments[i].patientNumber == patientNum && appointments[i].date.year == year && appointments[i].date.month == month && appointments[i].date.day == day)
            {
                printf("\n");
                displayPatientData(&patients[patientIndex], FMT_FORM);
                printf("Are you sure you want to remove this appointment (y,n): ");
                comfirmsRemove = inputCharOption("yn");
                if (comfirmsRemove == 'y')
                {
                    appointments[i].date.year = 0;
                    printf("\n");
                    printf("Appointment record has been removed!\n");
                    printf("\n");
                }
            }
        }
    }
    else
    {
        printf("ERROR: Patient record not found!\n\n");
    }
};

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (Copy your code from MS#2)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int vaild = -1, inputPatientNum;
    printf("Search by patient number: ");

    inputPatientNum = inputIntPositive();
    vaild = findPatientIndexByPatientNum(inputPatientNum, patient, max);
    if (vaild != -1)
    {
        printf("\n");
        displayPatientData(&patient[vaild], FMT_FORM);
    }
    else
    {
        printf("\n");
        printf("*** No records found ***\n");
    }
    printf("\n");
}

// Search and display patient records by phone number (tabular)
// (Copy your code from MS#2)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    int i;
    int found = 0;
    char patientPhoneNum[PHONE_LEN + 1];

    printf("Search by phone number: ");
    inputCString(patientPhoneNum, 10, 10);
    printf("\n");
    displayPatientTableHeader();

    for (i = 0; i < max; i++)
    {
        if (strcmp(patient[i].phone.number, patientPhoneNum) == 0)
        {

            displayPatientData(&patient[i], FMT_TABLE);
            found = 1;
        }
    }
    if (found == 0)
    {
        printf("\n");
        printf("*** No records found ***\n\n");
    }
    else
    {
        printf("\n");
    }
}

// Get the next highest patient number
// (Copy your code from MS#2)
int nextPatientNumber(const struct Patient patient[], int max)
{
    int maxnumber = 0, i;

    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber > maxnumber)
        {
            maxnumber = patient[i].patientNumber;
        }
    }
    return maxnumber + 1; // The next patient number should be one more than the current maximum
}

// Find the patient array index by patient number (returns -1 if not found)
// (Copy your code from MS#2)
int findPatientIndexByPatientNum(int patientNumber,
                                 const struct Patient patient[], int max)
{
    int i;
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber == patientNumber)
        {

            return i;
        }
    }
    return -1;
}

// Swap
void swap(struct Appointment *appointmentsJ, struct Appointment *appointmentsJ1)
{
    struct Appointment temp;
    temp = *appointmentsJ;
    *appointmentsJ = *appointmentsJ1;
    *appointmentsJ1 = temp;
}

// bubble sort appointments
void sortAppointments(struct Appointment appointments[], int size)
{
    int i, j;
    int swapped;
    for (i = 0; i < size - 1; i++)
    {
        swapped = 0;
        for (j = 0; j < size - i - 1; j++)
        {
            // pk year
            if (appointments[j].date.year > appointments[j + 1].date.year)
            {
                swap(&appointments[j], &appointments[j + 1]);
                swapped = 1;
            }
            else if (appointments[j].date.year == appointments[j + 1].date.year)
            {
                if (appointments[j].date.month > appointments[j + 1].date.month)
                {
                    swap(&appointments[j], &appointments[j + 1]);
                    swapped = 1;
                }
                else if (appointments[j].date.month == appointments[j + 1].date.month)
                {
                    if (appointments[j].date.day > appointments[j + 1].date.day)
                    {
                        swap(&appointments[j], &appointments[j + 1]);
                        swapped = 1;
                    }
                    else if (appointments[j].date.day == appointments[j + 1].date.day)
                    {
                        if (appointments[j].time.hour > appointments[j + 1].time.hour)
                        {
                            swap(&appointments[j], &appointments[j + 1]);
                            swapped = 1;
                        }
                        else if (appointments[j].time.hour == appointments[j + 1].time.hour)
                        {
                            if (appointments[j].time.min > appointments[j + 1].time.min)
                            {
                                swap(&appointments[j], &appointments[j + 1]);
                                swapped = 1;
                            }
                        }
                    }
                }
            }
        }
        if (swapped == 0)
        {
            break;
        }
    }
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (Copy your code from MS#2)
void inputPatient(struct Patient *patient)
{
    char name[NAME_LEN + 1];
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(name, 1, NAME_LEN);
    strcpy(patient->name, name);
    printf("\n");
    inputPhoneData(&(patient->phone));
}

// Get user input for phone contact information
// (Copy your code from MS#2)
void inputPhoneData(struct Phone *phone)
{
    int selection;
    printf("Phone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");
    printf("Selection: ");
    selection = inputIntRange(1, 4);
    putchar('\n');

    switch (selection)
    {
    case 1:
        printf("Contact: CELL\n");
        printf("Number : ");
        inputPhoneNumber(phone->number);
        strcpy(phone->description, "CELL");
        printf("\n");
        break;
    case 2:
        printf("Contact: HOME\n");
        printf("Number : ");
        inputPhoneNumber(phone->number);
        strcpy(phone->description, "HOME");
        printf("\n");
        break;
    case 3:
        printf("Contact: WORK\n");
        printf("Number : ");
        inputPhoneNumber(phone->number);
        strcpy(phone->description, "WORK");
        printf("\n");
        break;
    case 4:
        strcpy(phone->description, "TBD");
        break;

    default:
        break;
    }
}

void inputYearMonthDay(int *year, int *month, int *day)
{

    printf("Year        : ");
    *year = inputIntPositive();
    printf("Month (1-12): ");
    *month = inputIntRange(1, 12);

    if (*month == 2)
    {
        if (*year % 4 == 0)
        {
            printf("Day (1-29)  : ");
            *day = inputIntRange(1, 29);
        }
        else
        {
            printf("Day (1-28)  : ");
            *day = inputIntRange(1, 28);
        }
    }
    else if (*month == 1 || *month == 3 || *month == 5 ||
             *month == 7 || *month == 8 || *month == 10 || *month == 12)
    {
        printf("Day (1-31)  : ");
        *day = inputIntRange(1, 31);
    }
    else
    {
        printf("Day (1-30)  : ");
        *day = inputIntRange(1, 30);
    }
}

//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
/// ToDo:
int importPatients(const char *datafile, struct Patient patients[], int max)
{
    FILE *fp = NULL;
    int index = 0;
    fp = fopen(datafile, "r");
    if (fp != NULL)
    {
        while (fscanf(fp, "%d|%15[^|]|%4[^|]|%10[^\n]", &patients[index].patientNumber,
                      patients[index].name, patients[index].phone.description, patients[index].phone.number) != EOF &&
               index < max)
        {
            index++; // run loop
        }

        fclose(fp);
    }
    // Must return the total number of records read from the file and stored to the array,
    // which may be less than the total number of records in the file

    return index;
}

// Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:

int importAppointments(const char *datafile, struct Appointment appoints[], int max)
{
    FILE *fp = NULL;
    int index = 0;
    // 1040,2024,2,29,13,0
    fp = fopen(datafile, "r");

    if (fp != NULL)
    {
        while (fscanf(fp, "%d,%d,%d,%d,%d,%d", &appoints[index].patientNumber,
                      &appoints[index].date.year, &appoints[index].date.month, &appoints[index].date.day, &appoints[index].time.hour, &appoints[index].time.min) != EOF &&
               index < max)
        {
            index++; // run loop
        }

        fclose(fp);
    }
    // Must return the total number of records read from the file and stored to the array,
    // which may be less than the total number of records in the file

    return index;
}
