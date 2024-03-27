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
#include <string.h>
// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


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
// Displays a single patient record in  | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
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


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
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
            printf("<<< Feature not yet available >>>\n\n");
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
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
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
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


// ---------------------------------------------------------------------------
// !!! Put all the remaining function definitions below !!!
// Note: Maintain the same order/sequence as it is listed in the header file
// ---------------------------------------------------------------------------

// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void displayAllPatients(const struct Patient patient[], int max, int fmt){
    
    int i, allInvalid=0;
    
    displayPatientTableHeader();

    for (i=0;i<max; i++ ){
        
        if (patient[i].patientNumber !=0){
            displayPatientData( &patient[i], fmt);
            allInvalid = 1;
        } 
    }
    printf("\n");
    if (allInvalid==0){
        printf("*** No records found ***\n");
    }
    
    

}



// Search for a patient record based on patient number or phone number
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientData(const struct Patient patient[], int max) {
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
    } while (selection!=0);
}


// Add a new patient record to the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void addPatient(struct Patient patient[], int max){
    int index ,newPatientNum;
    

    index=findPatientIndexByPatientNum(0,patient,max);
    if (index==-1){
        printf("ERROR: Patient listing is FULL!\n\n");
    } else{
        newPatientNum=nextPatientNumber(patient,max);
        patient[index].patientNumber =newPatientNum;
        inputPatient(&patient[index]);
        printf("*** New patient record added ***\n\n");
    }

}


// Edit a patient record from the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void editPatient(struct Patient patient[], int max){
    int patientNum=0;
    int index;

    printf("Enter the patient number: ");
    
    patientNum=inputIntPositive();
    index =findPatientIndexByPatientNum(patientNum,patient,max);
    if (index !=-1){
        printf("\n");
        menuPatientEdit(&patient[index]);
        

    }else{
        printf("ERROR: Patient record not found!\n");
        }
    

}

// Remove a patient record from the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void removePatient(struct Patient patient[], int max){
    int patientNum;
    int index;
    char yesOrNo[]= {'y','n'};
    char comfirmsRemove;


    printf("Enter the patient number: ");
    patientNum=inputIntPositive();
    printf("\n");
    
    index =findPatientIndexByPatientNum(patientNum,patient,max);
    if (index !=-1){
        displayPatientData(&patient[index],FMT_FORM);
        printf("\n");
        printf("Are you sure you want to remove this patient record? (y/n): ");
       comfirmsRemove = inputCharOption(yesOrNo);
        if (comfirmsRemove =='y'){
            patient[index].patientNumber =0;
            printf("Patient record has been removed!\n");
            printf("\n");
        }else{
            
            printf("Operation aborted.\n");
            printf("\n");
        }
    }else{
        printf("ERROR: Patient record not found!\n\n");
    }
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientByPatientNumber(const struct Patient patient[], int max){
    int vaild=-1,inputPatientNum; 
    printf("Search by patient number: ");

    inputPatientNum = inputIntPositive();
    vaild  =findPatientIndexByPatientNum(inputPatientNum,patient,max);
    if (vaild!=-1){
        printf("\n");
        displayPatientData(&patient[vaild],FMT_FORM);
    }
    else{
        printf("\n");
        printf("*** No records found ***\n");
    }
    printf("\n");
}

// Search and display patient records by phone number (tabular)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientByPhoneNumber(const struct Patient patient[], int max){
    int i;
    int found=0; 
    char patientPhoneNum[PHONE_LEN+1];

    printf("Search by phone number: ");
    inputCString(patientPhoneNum,10,10);
    printf("\n");
    displayPatientTableHeader();
    
    for (i=0;i<max ;i++){
        if (strcmp(patient[i].phone.number, patientPhoneNum) == 0){
           
            displayPatientData(&patient[i],FMT_TABLE);
            found=1;
        }
    }
    if (found ==0){
        printf("\n");
        printf("*** No records found ***\n\n");
    } else {
        printf("\n");
    }

}

// Get the next highest patient number
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
int nextPatientNumber(const struct Patient patient[], int max){
    int maxnumber=0,i;

    for (i=0;i<max;i++){
        if(patient[i].patientNumber>maxnumber){
            maxnumber = patient[i].patientNumber;
            
        }
    } 
    return maxnumber + 1;// The next patient number should be one more than the current maximum
}


// Find the patient array index by patient number (returns -1 if not found)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
int findPatientIndexByPatientNum(int patientNumber,
                                 const struct Patient patient[], int max){
    int i; 
    for(i=0;i<max;i++){
         if (patient[i].patientNumber==patientNumber){
           
            return i;
         }
         

    }
    return -1;
   
   
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void inputPatient(struct Patient* patient){
    char name[NAME_LEN+1];   
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: %05d\n",patient->patientNumber);
    printf("Name  : ");
    inputCString(name,1,NAME_LEN);
    strcpy(patient->name,name);
    printf("\n");
    inputPhoneData(&(patient->phone));
    


}

// Get user input for phone contact information
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void inputPhoneData(struct Phone* phone){
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
    case 1 :
        printf("Contact: CELL\n");
        printf("Number : ");
        inputCString(phone->number,10,10);
        strcpy(phone->description,"CELL");
        printf("\n");
        break;
    case 2 :
        printf("Contact: HOME\n");
        printf("Number : ");
        inputCString(phone->number,10,10);
        strcpy(phone->description,"HOME");
        printf("\n");
        break;
    case 3:
        printf("Contact: WORK\n");
        printf("Number : ");
        inputCString(phone->number,10,10);
        strcpy(phone->description,"WORK");
        printf("\n");
        break;
    case 4:
        strcpy(phone->description,"TBD");
        break;

    default:
        break;
    }


}