/**
 * \addtogroup APP
 * Main group application
 * @{
 * \file main.c
 * \brief main application
 * \author Mustafa M.Montaser
 * \version v1.0.0
 * \date 18-May-2023
 * */

/** @} */

/* Header files includes */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Libs/StdLibs/StdTypes.h"
#include "Libs/Billing/Billing.h"


/* Global Variables */

Billing_Error_Handle_t error;
u8 operation;
Billing_Record_t record;
u8 query[INPUT_NAME_MAX_LENGTH];


int main()
{
    // Display welcome message
    printf("\n\n===================================================\n");
    printf("=============== Telecom Billing System ============\n");
    printf("===================================================\n");

    while (1)
    {
        // Display system options
        printf("\nPlease select the required operation:\n");
        printf("\n(A) => Add New Record\n");
        printf("\n(L) => View Records List\n");
        printf("\n(M) => Modify Record\n");
        printf("\n(P) => View Amount To Be Paid\n");
        printf("\n(S) => Search For Record by Name Or Number\n");
        printf("\n(D) => Delete Record by Name Or Number\n");
        printf("\nYour input is : ");
        // Getting user choice 
        scanf("%c", &operation);
        fflush(stdin);
        operation = toupper(operation);
        printf("\n--------------------------------------------------------------\n");
        switch (operation)
        {
        case ADD_NEW_RECORD: // Adding new record case
            // Gettign name
            printf("\nEnter Client Name (Must Not Exceed Than %i Character): ", INPUT_NAME_MAX_LENGTH - 1);
            fgets(record.name, INPUT_NAME_MAX_LENGTH, stdin);
            fflush(stdin);
            // Gettign phone number
            printf("\nEnter Client Number (Must Not Exceed Than %i Character): ", INPUT_PHONE_MAX_LENGTH - 1);
            scanf("%s", &(record.phoneNumber));
            fflush(stdin);
            // Gettign amount of payment
            printf("\nEnter Client Amount Of Payment (Must Not Exceed Than %i Characters) : ", INPUT_PAYMENT_MAX_LENGTH - 1);
            scanf("%s", &(record.payment));
            fflush(stdin);
            // Adding record to the file
            error = Billing_AddNewRecord(record);
            break;
        case VIEW_RECORDS_LIST: // Viewing records list case
            error = Billing_ViewRecordsList();
            break;
        case MODIFY_RECORD: // Modifing record case
            // Getting query to search about
            printf("\nEnter Name or Number To Modify Its Record : ");
            fgets(query, INPUT_NAME_MAX_LENGTH, stdin);
            fflush(stdin);
            // Getting new name
            printf("\nEnter New Client Name (Must Not Exceed Than %i Character): ", INPUT_NAME_MAX_LENGTH - 1);
            fgets(record.name, INPUT_NAME_MAX_LENGTH, stdin);
            fflush(stdin);
            // getting new phone number
            printf("\nEnter New Client Number (Must Not Exceed Than %i Character): ", INPUT_PHONE_MAX_LENGTH - 1);
            scanf("%s", &(record.phoneNumber));
            fflush(stdin);
            // getting new amount of payment
            printf("\nEnter New Client Amount Of Payment (Must Not Exceed Than %i Characters) : ", INPUT_PAYMENT_MAX_LENGTH - 1);
            scanf("%s", &(record.payment));
            fflush(stdin);
            // Modifing record and inserting it into the file
            error = Billing_ModifyRecord(query, record);
            break;
        case VIEW_AMOUNT_OF_PAYMENT: // Viewing amount of payment case
            // Getting query to search about
            printf("\nEnter Phone Number To Print Its Amount Of Payment : ");
            scanf("%s", query);
            fflush(stdin);
            // 
            error = Billing_ViewPayment(query, NULL);
            break;
        case SEARCH_RECORD: // searching about record case
            // Getting query to search about
            printf("\nEnter Name or Number To Search About : ");
            fgets(query, INPUT_NAME_MAX_LENGTH, stdin);
            fflush(stdin);
            // 
            error = Billing_SearchRecord(query);
            break;
        case DELETE_RECORD: // Deleting record case
            // Getting query to search about
            printf("\nEnter Name or Number To Delete Its Record : ");
            fgets(query, INPUT_NAME_MAX_LENGTH, stdin);
            fflush(stdin);
            // 
            error = Billing_DeleteRecord(query);
            break;
        default:
            printf("\nUnknown opration. Please select right operation\n");
            break;
        }
        // printing error message depend on each case
        Billing_PrintError(error);
        // 
        printf("\n--------------------------------------------------------------\n");
        printf("\nNeed Another Operation, Press (Y) Else, Press Any Key To Exit: ");
        scanf("%c", &operation);
        fflush(stdin);
        operation = toupper(operation);
        if (operation != 'Y') break;
        printf("\n--------------------------------------------------------------\n");
    }

    return 0;
}