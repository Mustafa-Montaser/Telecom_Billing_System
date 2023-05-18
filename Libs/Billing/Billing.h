/**
 * \addtogroup Libs
 * This group contain necessary libraries
 * @{
 * \addtogroup Billing
 * This group includes billing libraries
 * @{
 * \file Billing.h
 * \brief this file contains standard types and functions prototypes for Billing module
 * \author Mustafa M.Montaser
 * \version v1.0.0
 * \date 18-May-2023
 * */

/** @} */
/** @} */

#ifndef BILLING_H_
#define BILLING_H_

/* Macros */

#define BILLING_DATA_FILE_PATH                  "billingData.txt"
#define FILE_MAX_LINE_LENGTH                    96
#define FILE_PRE_NAME                           "Name:"
#define FILE_PRE_PHONE                          "Phone_Number:"
#define FILE_PRE_PAYMENT                        "Amount_Of_Payment:"
#define INPUT_NAME_MAX_LENGTH                   31
#define INPUT_PHONE_MAX_LENGTH                  12
#define INPUT_PAYMENT_MAX_LENGTH                9


/* special types */

/**
 * @struct Billing_Record_t
 *      Record data
 * @var Billing_Record_t::name
 *      record name
 * @var Billing_Record_t::phoneNumber
 *      record phone number
 * @var Billing_Record_t::payment
 *      record amount of payment
 */
typedef struct 
{
    u8 name[INPUT_NAME_MAX_LENGTH];
    u8 phoneNumber[INPUT_PHONE_MAX_LENGTH];
    u8 payment[INPUT_PAYMENT_MAX_LENGTH];
} Billing_Record_t;


/**
 * @enum Billing_Operation_t
 *      Different operation for the billing system
 * @var Billing_Operation_t::ADD_NEW_RECORD
 *      Add new record
 * @var Billing_Operation_t::VIEW_RECORDS_LIST
 *      view list of the records
 * @var Billing_Operation_t::MODIFY_RECORD
 *      Modify certain record
 * @var Billing_Operation_t::VIEW_AMOUNT_OF_PAYMENT
 *      View amount of payment for certian record
 * @var Billing_Operation_t::SEARCH_RECORD
 *      search about certain record or group or records
 * @var Billing_Operation_t::DELETE_RECORD
 *      Delete certain record record
 */
typedef enum
{
    ADD_NEW_RECORD          = 'A',
    VIEW_RECORDS_LIST       = 'L',
    MODIFY_RECORD           = 'M',
    VIEW_AMOUNT_OF_PAYMENT  = 'P',
    SEARCH_RECORD           = 'S',
    DELETE_RECORD           = 'D'
} Billing_Operation_t;


/**
 * @enum Billing_Error_t
 *      Error state
 * @var Billing_Error_t::NOK
 *      certain operation is failed
 * @var Billing_Error_t::OK
 *      certain operation is done
 */
typedef enum
{
    NOK,
    OK
} Billing_Error_t;


/**
 * @struct Billing_Error_Handle_t
 *      Handling error for each operation in each step
 * @var Billing_Error_Handle_t::fileOpenErr
 *      Error state when open the file
 * @var Billing_Error_Handle_t::fileCloseErr
 *      Error state when close the file
 * @var Billing_Error_Handle_t::fileReadErr
 *      Error state when read the file
 * @var Billing_Error_Handle_t::fileWriteErr
 *      Error state when write in the file
 * @var Billing_Error_Handle_t::userInputErr
 *      Error state when getting data from the user
 */
typedef struct
{
    u8 fileOpenErr  : 1;
    u8 fileCloseErr : 1;
    u8 fileReadErr  : 1;
    u8 fileWriteErr : 1;
    u8 userInputErr : 1;
} Billing_Error_Handle_t;


/* function declaration */

/**
 * @brief Add new record into the data file
 * @param record struct of record data
 * @return Billing_Error_Handle_t 
 */
Billing_Error_Handle_t Billing_AddNewRecord(Billing_Record_t record);

/**
 * @brief View records list which stored in the file
 * @param void
 * @return Billing_Error_Handle_t 
 */
Billing_Error_Handle_t Billing_ViewRecordsList();

/**
 * @brief modify selected record which is found by query result
 * @param query searching keyword
 * @param record struct of record data
 * @return Billing_Error_Handle_t 
 */
Billing_Error_Handle_t Billing_ModifyRecord(u8 query[], Billing_Record_t record);

/**
 * @brief View amount of payment for selected record
 * @param query searching keyword
 * @param ptrResult poiner to payment variable
 * @return Billing_Error_Handle_t 
 */
Billing_Error_Handle_t Billing_ViewPayment(u8 query[], f32 *ptrResult);

/**
 * @brief searching about certain record
 * @param query searching keyword
 * @return Billing_Error_Handle_t 
 */
Billing_Error_Handle_t Billing_SearchRecord(u8 query[]);

/**
 * @brief Deleting certain record
 * @param query searching keyword
 * @return Billing_Error_Handle_t 
 */
Billing_Error_Handle_t Billing_DeleteRecord(u8 query[]);

/**
 * @brief print error message
 * @param error struct of error states
 * @return void
 */
void Billing_PrintError(Billing_Error_Handle_t error);

#endif /* BILLING_H_ */