/**
 * @file ARUTILS_Manager.h
 * @brief libARUtils Manager header file.
 * @date 21/05/2014
 * @author david.flattin.ext@parrot.com
 **/

#ifndef _ARUTILS_MANAGER_H_
#define _ARUTILS_MANAGER_H_


#include "libARUtils/ARUTILS_Ftp.h"


/**
 * @brief Ftp MANAGER structure
 * @see ARUTILS_Manager_New
 */
typedef struct ARUTILS_Manager_t ARUTILS_Manager_t;

/**
 * @brief BLE Manager (used to send/read data)
 * @note This is an application-provided object, OS Dependant
 */
typedef void* ARUTILS_BLEDeviceManager_t;

/**
 * @brief BLE Device reference for the @ref ARUTILS_BLEDevice_t
 * @note This is an application-provided object, OS Dependant
 */
typedef void* ARUTILS_BLEDevice_t;

/**
 * @brief Create a new Ftp Manager
 * @warning This function allocates memory
 * @param[out] error The pointer of the error code: if success ARUTILS_OK, otherwise an error number of eARUTILS_ERROR
 * @retval On success, returns an ARUTILS_Ftp_Connection_t. Otherwise, it returns null.
 * @see ARUTILS_Manager_Delete ()
 */
ARUTILS_Manager_t* ARUTILS_Manager_New(eARUTILS_ERROR *error);

/**
 * @brief Delete an Ftp Manager
 * @warning This function frees memory
 * @param managerAddr The address of the pointer on the Ftp Manager
 * @see ARUTILS_Manager_New ()
 */
void ARUTILS_Manager_Delete(ARUTILS_Manager_t **managerAddr);


/**
 * @brief Create a new WifiFtp Connection
 * @warning This function allocates memory
 * @param manager The Manager
 * @param cancelSem The pointer of the Ftp get/put cancel semaphore or null
 * @param server The Ftp server IP address
 * @param port The Ftp server port
 * @param username The Ftp server account name
 * @param password The Ftp server account password
 * @retval On success, returns an ARUTILS_OK. Otherwise an error number of eARUTILS_ERROR
 * @see ARUTILS_Manager_CloseWifiFtp ()
 */
eARUTILS_ERROR ARUTILS_Manager_InitWifiFtp(ARUTILS_Manager_t *manager, ARSAL_Sem_t *cancelSem, const char *server, int port, const char *username, const char* password);

/**
 * @brief Delete an WifiFtp Connection
 * @warning This function frees memory
 * @param manager The address of the pointer on the Ftp Connection
 * @see ARUTILS_Manager_InitWifiFtp ()
 */
void ARUTILS_Manager_CloseWifiFtp(ARUTILS_Manager_t *manager);

/**
 * @brief Create a new BLEFtp Connection
 * @warning This function allocates memory
 * @param manager The Manager
 * @param cancelSem The pointer of the Ftp get/put cancel semaphore or null
 * @param server The Ftp server IP address
 * @param port The Ftp server port
 * @param username The Ftp server account name
 * @param password The Ftp server account password
 * @retval On success, returns an ARUTILS_OK. Otherwise an error number of eARUTILS_ERROR
 * @see ARUTILS_Manager_CloseBLEFtp ()
 */
eARUTILS_ERROR ARUTILS_Manager_InitBLEFtp(ARUTILS_Manager_t *manager, ARSAL_Sem_t *cancelSem, ARUTILS_BLEDevice_t device);

/**
 * @brief Delete an WifiFtp Connection
 * @warning This function frees memory
 * @param manager The address of the pointer on the Ftp Connection
 * @see ARUTILS_Manager_InitBLEFtp ()
 */
void ARUTILS_Manager_CloseBLEFtp(ARUTILS_Manager_t *manager);

/**
 * @brief Cancel an Ftp Connection command in progress (get, put, list etc)
 * @param connection The address of the pointer on the Ftp Connection
 * @retval On success, returns ARUTILS_OK. Otherwise, it returns an error number of eARUTILS_ERROR.
 * @see ARUTILS_Manager_NewWifiFtp (), ARUTILS_Manager_NewBLEFtp
 */
eARUTILS_ERROR ARUTILS_Manager_Ftp_Connection_Cancel(ARUTILS_Manager_t *manager);

/**
 * @brief Execute Ftp List command to retrieve directory content
 * @warning This function allocates memory
 * @param manager The address of the pointer on the Ftp Connection
 * @param namePath The string of the directory path on the remote Ftp server
 * @param resultList The pointer of the string of the directory content null terminated
 * @param resultListLen The pointer of the lenght of the resultList string including null terminated
 * @retval On success, returns ARUTILS_OK. Otherwise, it returns an error number of eARUTILS_ERROR.
 * @see ARUTILS_Manager_InitWifiFtp (), ARUTILS_Manager_InitBLEFtp ()
 */
eARUTILS_ERROR ARUTILS_Manager_Ftp_List(ARUTILS_Manager_t *manager, const char *namePath, char **resultList, uint32_t *resultListLen);

/**
 * @brief Get an remote Ftp server file
 * @warning This function allocates memory
 * @param manager The address of the pointer on the Ftp Connection
 * @param namePath The string of the file name path on the remote Ftp server
 * @param data The pointer of the data buffer of the file data
 * @param dataLen The pointer of the length of the data buffer
 * @param progressCallback The progress callback function
 * @param progressArg The progress callback function arg
 * @retval On success, returns ARUTILS_OK. Otherwise, it returns an error number of eARUTILS_ERROR.
 * @see ARUTILS_Manager_InitWifiFtp (), ARUTILS_Manager_InitBLEFtp (), ARUTILS_Ftp_ProgressCallback_t, eARUTILS_FTP_RESUME
 */
eARUTILS_ERROR ARUTILS_Manager_Ftp_Get_WithBuffer(ARUTILS_Manager_t *manager, const char *namePath, uint8_t **data, uint32_t *dataLen,  ARUTILS_Ftp_ProgressCallback_t progressCallback, void* progressArg);

/**
 * @brief Get an remote Ftp server file
 * @param manager The address of the pointer on the Ftp Connection
 * @param namePath The string of the file name path on the remote Ftp server
 * @param dstFile The string of the local file name path to be get
 * @param progressCallback The progress callback function
 * @param progressArg The progress callback function arg
 * @param resume The resume capability requested
 * @retval On success, returns ARUTILS_OK. Otherwise, it returns an error number of eARUTILS_ERROR.
 * @see ARUTILS_Manager_InitWifiFtp (), ARUTILS_Manager_InitBLEFtp (), ARUTILS_Ftp_ProgressCallback_t, eARUTILS_FTP_RESUME
 */
eARUTILS_ERROR ARUTILS_Manager_Ftp_Get(ARUTILS_Manager_t *manager, const char *namePath, const char *dstFile, ARUTILS_Ftp_ProgressCallback_t progressCallback, void* progressArg, eARUTILS_FTP_RESUME resume);

/**
 * @brief Put an remote Ftp server file
 * @param manager The address of the pointer on the Ftp Connection
 * @param namePath The string of the file name path on the remote Ftp server
 * @param srcFile The string of the local file name path to be put
 * @param progressCallback The progress callback function
 * @param progressArg The progress callback function arg
 * @param resume The resume capability requested
 * @retval On success, returns ARUTILS_OK. Otherwise, it returns an error number of eARUTILS_ERROR.
 * @see ARUTILS_Manager_InitWifiFtp (), ARUTILS_Manager_InitBLEFtp (), ARUTILS_Ftp_ProgressCallback_t, eARUTILS_FTP_RESUME
 */
eARUTILS_ERROR ARUTILS_Manager_Ftp_Put(ARUTILS_Manager_t *manager, const char *namePath, const char *srcFile, ARUTILS_Ftp_ProgressCallback_t progressCallback, void* progressArg, eARUTILS_FTP_RESUME resume);

/**
 * @brief Delete an remote Ftp server file
 * @param delete The address of the pointer on the Ftp Connection
 * @param namePath The string of the file name path on the remote Ftp server
 * @retval On success, returns ARUTILS_OK. Otherwise, it returns an error number of eARUTILS_ERROR.
 * @see ARUTILS_Manager_InitWifiFtp (), ARUTILS_Manager_InitBLEFtp ()
 */
eARUTILS_ERROR ARUTILS_Manager_Ftp_Delete(ARUTILS_Manager_t *manager, const char *namePath);

#endif /* _ARUTILS_MANAGER_H_ */

