/**
 * \addtogroup Libs
 * This group contain necessary libraries
 * @{
 * \addtogroup Billing
 * This group includes billing libraries
 * @{
 * \file Billing.c
 * \brief this file contains functions implementation for Billing module
 * \author Mustafa M.Montaser
 * \version v1.0.0
 * \date 18-May-2023
 * */

/** @} */
/** @} */


/* Header files includes */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../StdLibs/StdTypes.h"
#include "Billing.h"

/* functions definition */

Billing_Error_Handle_t Billing_AddNewRecord(Billing_Record_t record)
{
    // Initialise error state for each step {open file, close file, read file, write in file, user input}
    Billing_Error_Handle_t error = {NOK, NOK, OK, NOK, NOK};
    
    // check phone number and payment if they are numbers or not
    if (atoi(record.phoneNumber) && atof(record.payment))
    {
        // user input is ok
        error.userInputErr = OK;
        
        // open data file with append mode
        FILE *file = fopen(BILLING_DATA_FILE_PATH, "a");
        if (file != NULL)
        {
            // openning file is ok
            error.fileOpenErr = OK;
            
            // removing 'new line' from the data input and complete the length with spaces for file organization
            u8 noOfChar = strcspn(record.name, "\n");
            for (noOfChar; noOfChar < INPUT_NAME_MAX_LENGTH - 1; noOfChar++) record.name[noOfChar] = ' ';     
            
            noOfChar = strcspn(record.phoneNumber, "\0");
            for (noOfChar; noOfChar < INPUT_PHONE_MAX_LENGTH - 1; noOfChar++) record.phoneNumber[noOfChar] = ' ';
            record.phoneNumber[INPUT_PHONE_MAX_LENGTH - 1] = '\0';           
            
            noOfChar = strcspn(record.payment, "\0");
            for (noOfChar; noOfChar < INPUT_PAYMENT_MAX_LENGTH - 1; noOfChar++) record.payment[noOfChar] = ' ';
            record.payment[INPUT_PAYMENT_MAX_LENGTH - 1] = '\0';
            
            // append the record into the file
            noOfChar = fprintf (file, "%s %s | %s %s | %s %s\n",
                                    FILE_PRE_NAME, record.name,
                                    FILE_PRE_PHONE, record.phoneNumber,
                                    FILE_PRE_PAYMENT, record.payment
                                );
            
            // check if data is written successfully
            if (noOfChar > 0) error.fileWriteErr = OK;
            
            // check if file is closed successfully
            if (fclose(file) == 0) error.fileCloseErr = OK;
        }
    }

    return error;
}


Billing_Error_Handle_t Billing_ViewRecordsList()
{
    // Initialise error state for each step {open file, close file, read file, write in file, user input}
    Billing_Error_Handle_t error = {NOK, NOK, NOK, OK, OK};

    // open data file with read mode
    FILE *file = fopen(BILLING_DATA_FILE_PATH, "r");

    if (file != NULL)
    {
        // open file is ok
        error.fileOpenErr = OK;

        printf("\n");

        // buffer for reading data from th file
        u8 buffer[FILE_MAX_LINE_LENGTH];

        // display data as long as getting data is ok and end of the file not reached yet
        while (fgets(buffer, FILE_MAX_LINE_LENGTH, file) && !feof(file)) printf("%s", buffer);

        // check if reachs to the end of the file 
        if (fgetc(file) == EOF) error.fileReadErr = OK;

        printf("\n");

        // check closing the file
        if (fclose(file) == 0) error.fileCloseErr = OK;
    }

    return error;
}


Billing_Error_Handle_t Billing_ModifyRecord(u8 query[], Billing_Record_t record)
{
    // Initialise error state for each step {open file, close file, read file, write in file, user input}
    Billing_Error_Handle_t error = {NOK, NOK, NOK, NOK, NOK};

    // open the file with read and write mode
    FILE *file = fopen(BILLING_DATA_FILE_PATH, "r+");

    if (file != NULL)
    {
        // file open is ok
        error.fileOpenErr = OK;

        // removing 'new line' from query keyword
        if (strcspn(query, "\n")) query[strcspn(query, "\n")] = ' ';
        
        // buffer for reading data form the file
        u8 buffer[FILE_MAX_LINE_LENGTH];

        // as long as getting data from the file is ok and EOF not reched yet
        while (fgets(buffer, FILE_MAX_LINE_LENGTH, file) && !feof(file))
        {
            // reading data is ok
            if(!error.fileReadErr) error.fileReadErr = OK;
            
            // check if query is exists in the buffer
            if (strstr(buffer, query))
            {
                // moving curser positon to the start of the line
                fseek(file, (-1 * FILE_MAX_LINE_LENGTH), SEEK_CUR);                
                
                // check if user data input is ok
                if (atoi(record.phoneNumber) && atof(record.payment))
                {
                    error.userInputErr = OK;

                    // removing 'new line' from the data input and complete the length with spaces for file organization 
                    u8 noOfChar = strcspn(record.name, "\n");
                    for (noOfChar; noOfChar < INPUT_NAME_MAX_LENGTH - 1; noOfChar++) record.name[noOfChar] = ' ';          
                    
                    noOfChar = strcspn(record.phoneNumber, "\0");
                    for (noOfChar; noOfChar < INPUT_PHONE_MAX_LENGTH - 1; noOfChar++) record.phoneNumber[noOfChar] = ' ';
                    record.phoneNumber[INPUT_PHONE_MAX_LENGTH - 1] = '\0';         
                    
                    noOfChar = strcspn(record.payment, "\0");
                    for (noOfChar; noOfChar < INPUT_PAYMENT_MAX_LENGTH - 1; noOfChar++) record.payment[noOfChar] = ' ';
                    record.payment[INPUT_PAYMENT_MAX_LENGTH - 1] = '\0';
                    
                    printf("\nModifing Record : \n\n%s\nTo Be >>>\n\n[Name] %s [Phone Number] %s [Amount Of Payment] %s\n",
                            buffer, record.name, record.phoneNumber, record.payment
                        );
                    
                    // writing new record into the file instead of old one
                    noOfChar = fprintf (file, "%s %s | %s %s | %s %s",
                                    FILE_PRE_NAME, record.name,
                                    FILE_PRE_PHONE, record.phoneNumber,
                                    FILE_PRE_PAYMENT, record.payment
                                );

                    // ckeck if data is written successfully
                    if (noOfChar > 0) error.fileWriteErr = OK;
                }

                break;
            }
        }

        // check if file close is done
        if (fclose(file) == 0) error.fileCloseErr = OK;
    }

    return error;
}


Billing_Error_Handle_t Billing_ViewPayment(u8 query[], f32 *ptrResult)
{
    // Initialise error state for each step {open file, close file, read file, write in file, user input}
    Billing_Error_Handle_t error = {NOK, NOK, NOK, OK, NOK};

    // check if user input is a number
    if(atoi(query))
    {
        error.userInputErr = OK;

        // opne the file in read mode
        FILE *file = fopen(BILLING_DATA_FILE_PATH, "r");

        if (file != NULL)
        {
            // file open is ok
            error.fileOpenErr = OK;

            // buffer for getting data from the file
            u8 buffer[INPUT_NAME_MAX_LENGTH];

            // as long as EOF not reched yet
            while (!feof(file))
            {
                // check if reading from file is ok
                error.fileReadErr = fscanf(file, "%s", buffer) ? OK : NOK;

                // check if query string matchs with read data in buffer
                if (strcmp(query, buffer) == 0 && !feof(file))
                {
                    // seeking for payment keyword 
                    while ((strcmp(FILE_PRE_PAYMENT, buffer) != 0) && !feof(file)) fscanf(file, "%s", buffer);

                    if (fgetc(file) != EOF)
                    {
                        // getting payment value which after payment keyword
                        fscanf(file, "%s", buffer);

                        printf("\nAmount Of Payment = %s\n", buffer);

                        // assign it to the passed pointer if not NULL
                        if (ptrResult != NULL) *ptrResult = (f32)atof(buffer);

                        break;
                    }
                }
                
                // reachs to here means that query not found
                if (fgetc(file) == EOF) printf("\nYour Entry Is Not Found\n");
            }

            // checking closing file
            if(fclose(file) == 0) error.fileCloseErr = OK;
        }
    }

    return error;
}


Billing_Error_Handle_t Billing_SearchRecord(u8 query[])
{
    // Initialise error state for each step {open file, close file, read file, write in file, user input}
    Billing_Error_Handle_t error = {NOK, NOK, NOK, OK, OK};

    // open file with read mode
    FILE *file = fopen(BILLING_DATA_FILE_PATH, "r");

    if (file != NULL)
    {
        // file open is ok
        error.fileOpenErr = OK;

        // removing 'new line' from the query
        if (strcspn(query, "\n")) query[strcspn(query, "\n")] = ' ';

        // buffer for storing getting data from the file
        u8 buffer[FILE_MAX_LINE_LENGTH];

        // indication for query result
        u8 findQuery = 0;

        printf("\n");

        // as long as getting data is OK and EOF not reached yet
        while (fgets(buffer, FILE_MAX_LINE_LENGTH, file) && !feof(file))
        {
            // read data file is ok
            if (!error.fileReadErr) error.fileReadErr = OK;

            // check if query is exists in data read in the buffer
            if (strstr(buffer, query)) 
            {
                printf("%s", buffer);
                findQuery++;
            }
        }

        // in case reaching to EOF and there is no result for query
        if((fgetc(file) == EOF) && !findQuery) printf("Your Entry Is Not Found\n");
        
        // closing file
        if (fclose(file) == 0) error.fileCloseErr = OK;
    }

    return error;
}


Billing_Error_Handle_t Billing_DeleteRecord(u8 query[])
{
    // Initialise error state for each step {open file, close file, read file, write in file, user input}
    Billing_Error_Handle_t error = {NOK, NOK, NOK, NOK, OK};

    // open file with read and write mode
    FILE *file = fopen(BILLING_DATA_FILE_PATH, "r+");

    if (file != NULL)
    {
        // open file is ok
        error.fileOpenErr = OK;

        // removing 'new line'
        if (strcspn(query, "\n")) query[strcspn(query, "\n")] = ' ';

        // buffer for storing data which get from the file
        u8 buffer[FILE_MAX_LINE_LENGTH];

        // as long as getting data is Ok and EOF not reached yet
        while (fgets(buffer, FILE_MAX_LINE_LENGTH, file) && !feof(file))
        {
            // read file is ok
            if(!error.fileReadErr) error.fileReadErr = OK;

            // check if query is exists in the data buffer
            if (strstr(buffer, query))
            {
                printf("\nDeleting Record : ...\n\n%s", buffer);

                // moving curser to the line start
                fseek(file, (-1 * FILE_MAX_LINE_LENGTH), SEEK_CUR);

                u8 writeState = 0;
                
                // fill the line with spaces which act as delete
                for(u8 i = 0; i < FILE_MAX_LINE_LENGTH - 1; i++) writeState = fputc(' ', file);

                // check if write in file is ok
                if (writeState) error.fileWriteErr = OK;

                break;
            }
        }

        // closing file
        if (fclose(file) == 0) error.fileCloseErr = OK;
    }

    return error;
}


void Billing_PrintError(Billing_Error_Handle_t error)
{
    // check if all steps are OK
    if (error.fileOpenErr && error.fileCloseErr && error.fileReadErr && error.fileWriteErr && error.userInputErr)
        printf("\nOperation Is Done Successfully\n");
    else
    {
        if (!error.userInputErr)    printf("\nInput Error");
        if (!error.fileOpenErr)     printf("\nFile Open Error");
        if (!error.fileReadErr)     printf("\nFile Read Error");
        if (!error.fileWriteErr)    printf("\nFile Write Error");
        if (!error.fileCloseErr)    printf("\nFile Close Error\n");
    }
}

