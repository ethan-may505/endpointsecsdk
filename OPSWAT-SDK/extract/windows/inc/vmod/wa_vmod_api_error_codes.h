#pragma once
/**	@file wa_vmod_api_error_codes.h
 *	@brief Defines success and error codes returned from API calls
 *	@defgroup wavmod_errorcodes Error codes
 *	@brief Defines the return codes that can be returned by the @ref wavmod_integration_interface "Functions"
 */
#include <string>
#include "wa_vmod_api_data_types.h"

/**
 *	@def WA_VMOD_SUCCESS(code)
 *	@brief Checks an error @a code for success. Equates to true if successful error code, false otherwise
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_SUCCESS(code) (((wa_vmod_int)(code))>=0)

/**
 *	@def WA_VMOD_FAILED(code)
 *	@ingroup wavmod_errorcodes
 *	@brief Checks an error @a code for failure. Equates to true if failure error code, false otherwise
 */
#define WA_VMOD_FAILED(code) (((wa_vmod_int)(code))<0)

/**
 *	@brief Defines a success.
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_OK 0

/**
 *	@brief Defines a success and value of TRUE.
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_OK_TRUE 1

/**
 *	@brief Defines a success and value of FALSE.
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_OK_FALSE 2

/**
 *	@brief Defines a partial success (for multiple operations, some succeeded and some failed).
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_PARTIAL_SUCCESS 3

 /**
 *	@brief Defines a success but validation failed
 *	@ingroup wavmod_errorcodes
 */
#define WAAPI_OK_VALIDATION_FAILED 14

 /**
  *	@brief Defines a success but cannot perform validation
  *	@ingroup waapi_errorcodes
 */
#define WAAPI_OK_CANNOT_VALIDATE 15

 /**
  *	@brief Define a success, but validation is not supported for the product
  *	@ingroup waapi_errorcodes
 */
#define WAAPI_OK_VALIDATION_NOT_SUPPORTED 16

/**
 *	@brief Defines data is live
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_DATA_LIVE 1000

/**
 *	@brief Defines data is cached
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_DATA_CACHED 1001

/**
 *	@brief Defines data is expired
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_DATA_EXPIRED 1002

 /**
 *	@brief Defines product installation requires restart
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_INSTALLATION_NEED_RESTART 1003

 /**
 *	@brief Defines product installation requires restart after sucessfully install partially
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_PARTIAL_INSTALLATION_NEED_RESTART 1004

/**
 *	@brief Defines a general failure.
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_GENERAL -1

/**
 *	@brief Defines an error when the license file is missing.
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_LICENSE_MISSING -2

/**
 *	@brief Defines an error when the license provided does not match the license file.
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_LICENSE_MISMATCH -3

/**
 *	@brief Defines an error when the license key has expired, not be to be confused with component licenses.
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_LICENSE_EXPIRED -4

/**
 *	@brief Defines an error when the API has not been initialized, yet a call requiring initialization was invoked.
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_NOT_INITIALIZED -5

/**
 *	@brief Defines an error when initialization is called when the API is already initialized.
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_ALREADY_INITIALIZED -6

/**
 *	@brief Defines an error when a call is made to a component that is not licensed.
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_COMPONENT_NOT_LICENSED -7

/**
 *	@brief Defines an error when a call is made to a component whose license has expired.
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_COMPONENT_LICENSE_EXPIRED -8

/**
 *	@brief Defines an error when a call is made to a component that is licensed, but is not deployed.
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_COMPONENT_NOT_DEPLOYED -9

/**
 *	@brief Defines an error when the component module from disk has been tampered with, therefore unloaded by the api.
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_COMPONENT_TAMPERED -10

/**
 *	@brief Defines an error when a method call was made on a component that does not support it.
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_COMPONENT_METHOD_NOT_SUPPORTED -11

/**
 *	@brief Defines an error when a method call was made on a component that does not implement it.
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_COMPONENT_METHOD_NOT_IMPLEMENTED -12

/**
 *	@brief Defines an error when the database is queried when it has yet to be initialized.
 *	@ingroup WA_VMOD_errocodes
 */
#define WA_VMOD_ERROR_DATABASE_NOT_INITIALIZED -16

/**
 *	@brief Defines an error when a remote call is made when there is no connection.
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_NO_CONNECTION -17

/**
 *	@brief Defines an error when the provided computer name or IP to a remote call is not found in the network.
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_IP_NOT_FOUND -18

/**
 *	@brief Defines an error when the provided user, password, or domain information is invalid.
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_INVALID_CREDENTIALS -19

/**
 *	@brief Defines an error when the input arguments provided do not match the methods documented input requirements. Not to be confused with @ref WA_VMOD_ERROR_INVALID_JSON
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_INVALID_INPUT_ARGS -20

/**
 *	@brief Defines an error when the input arguments provided are not in proper @JSON format. Not to be confused with @ref WA_VMOD_ERROR_INVALID_INPUT_ARGS
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_INVALID_JSON -21

/**
 *	@brief Defines an error when the access is denied for the invocation call requested.
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_ACCESS_DENIED -22

/**
 *	@brief Defines an error when the system or product is in an invalid state to perform the invocation call requested.
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_INVALID_STATE -23

/**
 *	@brief Defines an error when a request is dispatched and an exception is thrown.
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_DISPATCH_EXCEPTION -26

/**
 *	@brief Defines an error in a native system API.
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_NATIVE_API -27

/**
 *	@brief Defines an error when an object is not found. This can be objects held internally, or objects on the endpoint, such as files, backup times, etc.
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_NOT_FOUND -28

/**
 *	@brief Defines an error that occurs with our encryption/decryption security module
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_CRYPTO -33

/**
 *	@brief Defines an error when the configuration value for a valid key is of the incorrect type.
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_INVALID_CONFIG_VALUE -36

/**
 *	@brief Defines an error when the configuration key is not a valid configuration option
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_INVALID_CONFIG_KEY -37

/**
 *  @brief Defines an error when an OS is not supported
 *  @ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_OS_NOT_SUPPORTED -38

/**
 *	@brief Defines an error when the OESIS COM object is not available
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_OESIS_COM_NOT_AVAILABLE -1000

/**
 *	@brief Defines an error when the OESIS On Demand object is not available
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_OOD_NOT_AVAILABLE -1001

/**
 *	@brief Defines an error when there is problem initialize COM lib
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_INITIALIZE_COM -1002

/**
 *	@brief Defines an error when there is problem activating OESIS On Demand
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_ACTIVATE_OOD -1003

/**
 *	@brief Defines an error when OOD object is not initialized
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_OOD_NOT_INITIALIZED -1004

/**
 *	@brief Defines an error when queried product can't be found
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_PRODUCT_NOT_FOUND -1005

/**
 *	@brief Defines an error when queried product interface isn't supported
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_INTERFACE_NOT_SUPPORTED -1006

/**
 *	@brief Defines an error when queried product cannot update
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_CANNOT_UPDATE_PRODUCT -1007

/**
 *	@brief Defines an error when cache file cannot be found
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_CANNOT_FIND_CACHE_FILE -1008

/**
 *	@brief Defines an error when queried call isn't cached
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_QUERY_ISNT_CACHED -1009

/**
 *	@brief Defines an error when caching isn't enabled
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_CACHING_IS_DISABLED -1010

/**
 *	@brief Defines an error when definition state cannot be retrieved
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_CANNOT_GET_DEF_STATE -1011

/**
 *	@brief Defines an error when GEARS cannot detect products
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_CANNOT_DETECT_PRODUCTS -1012

/**
 *	@brief Defines an error when GEARS cannot be initialized
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_GEARS_CANNOT_INITIALIZE -1013

/**
 *	@brief Defines an error when an operation did not complete because it requires a newer version of server
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_LEGACY_SERVER -1014

/**
 *	@brief Defines an error when an operation did not complete because server couldn't be reached
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_NOROUTETOSERVER -1015

 /**
 *	@brief Defines an error when there is a mismatch in output format between internal components
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_INTERNAL_FORMAT_MISMATCH -1016

 /**
 *	@brief Defines an error when UpdateVerify is not initialized
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_UPDATEVERIFY_NOT_INITIALIZED -1017

 /**
 *	@brief Defines an error when 4V is not initialized
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_4V_NOT_INITIALIZED -1018

 /**
 *	@brief Defines an error when VMod Source is not initialized
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_OFFLINEVMOD_NOT_INITIALIZED -1019

 /**
 *	@brief Defines an error when GEARS cannot get product's version
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_CANNOT_GET_VERSION -1020

 /**
 *	@brief Defines an error when the procedure to retrieve system updates is timeout
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_GET_SYSTEM_PATCH_TIMEOUT -1021

 /**
 *	@brief Defines an error when GEARS cannot retrieve OS info
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_GEARS_CANNOT_GET_OS_INFO -1022

 /**
 *	@brief Defines an error when the vulnerability source in input is invalid
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_INVALID_VULN_SOURCE -1023

 /**
 *	@brief Defines an error when VMod SCAP is not initialized
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_VMOD_SCAP_NOT_INITIALIZED -1024

 /**
 *	@brief Defines an error when current system has not been supported
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_SYSTEM_NOT_SUPPORTED -1025

/**
 *	@brief Defines an error when a product is not supported
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_PRODUCT_NOT_SUPPORTED -1026

/**
 *	@brief Defines an error when a language is not supported
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_LANGUAGE_NOT_SUPPORTED -1027

/**
 *	@brief Defines an error when an architecture is not supported
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_ARCHITECTURE_NOT_SUPPORTED -1028

/**
 *	@brief Defines an error when a file type is not supported
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_NOT_RECOGNIZED_FILE -1029

 /**
 *	@brief Defines an error when cannot terminate processes
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_CANNOT_TERMINATE_PRODUCT -1030

 /**
 *	@brief Defines an error when cannot get components of product
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_CANNOT_GET_PROCESSES -1031

 /**
 *	@brief Defines an error when cannot get components of product
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_CANNOT_UNINSTALL_PRODUCT -1032

 /**
 *	@brief Defines product installation requires uninstall first
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_NEED_UNINSTALL_PRODUCT_FIRST -1033

 /**
 *	@brief Defines product installation is failed
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_INSTALLATION_FAILED -1034

 /**
 *	@brief Defines an error when the file size in input is too big
 *	@ingroup waapi_errorcodes
 */
#define WA_VMOD_ERROR_TOO_BIG_FILE_SIZE -1035

 /**
 *	@brief Defines extract file is failed
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_EXTRACT_FAILED -1036

 /**
 *	@brief Defines that there isn't enough memory
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_OUT_OF_MEMORY -1037

 /**
 *  @brief Defines an error when the type of data/content is not supported
 *  @ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_DATA_TYPE_NOT_SUPPORTED -1038

 /**
 *  @brief Defines an error when the queried index is out of array range
 *  @ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_OUT_OF_RANGE -1039

 /**
 *  @brief Defines an error when the online database prefix is not set or invalid
 *  @ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_INVALID_ONLINE_DB_URI -1040

 /**
 *  @brief Defines an error when the operation fails because another msi installation process is running.
 *  @ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_ANOTHER_MSI_INSTALLATION_INPROGRESS -1041

 /**
 *	@brief Defines an error when product version mismatches with expected version
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_VERSION_MISMATCH -1042

 /**
 *	@brief Defines an error when SDK cannot perform the requested verification
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_CANNOT_VERIFY -1043

 /**
 *  @brief Defines an error when detected circular package
 *  @ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_CIRCULAR_PACKAGE -1044

 /**
 *	@brief Defines an error when validate failed
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_VALIDATE_FAILED -1045

 /**
 *	@brief Defines an error when delay timeframe not passed
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_DELAY_TIMEFRAME_NOT_REACHED -1047

 /**
 *	@brief Request returned an http 300 multiple choices notification
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_HTTP_MULTIPLE_CHOICES -300

/**
 *	@brief Request returned an http 301 moved permanently notification
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_HTTP_MOVED_PERMANENTLY -301

/**
 *	@brief Request returned an http 302 found notification
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_HTTP_FOUND -302

/**
 *	@brief Request returned an http 303 see other notification
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_HTTP_SEE_OTHER -303

/**
 *	@brief Request returned an http 304 not modified notification
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_HTTP_NOT_MODIFIED -304

/**
 *	@brief Request returned an http 305 use proxy notification
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_HTTP_USE_PROXY -305

/**
 *	@brief Request returned an http 307 temporary redirect notification
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_HTTP_TEMPORARY_REDIRECT -307

/**
 *	@brief Request returned an http 400 bad request error
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_HTTP_BAD_REQUEST -400

/**
 *	@brief Request returned an http 401 unauthorized error
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_HTTP_UNAUTHORIZED -401

/**
 *	@brief Request returned an http 403 forbidden error
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_HTTP_FORBIDDEN -403

/**
 *	@brief Request returned an http 404 not found error
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_HTTP_NOT_FOUND -404

/**
 *	@brief Request returned an http 405 method not allowed error
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_HTTP_METHOD_NOT_ALLOWED -405

/**
 *	@brief Request returned an http 406 not acceptable error
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_HTTP_NOT_ACCEPTABLE -406

/**
 *	@brief Request returned an http 407 proxy authentication required error
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_HTTP_PROXY_AUTHENTICATION_REQUIRED -407

/**
 *	@brief Request returned an http 408 request timeout error
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_HTTP_REQUEST_TIMEOUT -408

/**
 *	@brief Request returned an http 409 conflict
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_HTTP_CONFLICT -409

/**
 *	@brief Request returned an http 410 gone error
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_HTTP_GONE -410

/**
 *	@brief Request returned an http 411 length required error
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_HTTP_LENGTH_REQUIRED -411

/**
 *	@brief Request returned an http 412 precondition failed error
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_HTTP_PRECONDITION_FAILED -412

/**
 *	@brief Request returned an http 413 request entity too large error
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_HTTP_REQUEST_ENTITY_TOO_LARGE -413

/**
 *	@brief Request returned an http 414 request uri too long error
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_HTTP_REQUEST_URI_TOO_LONG -414

/**
 *	@brief Request returned an http 415 unsupported media type error
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_HTTP_UNSUPPORTED_MEDIA_TYPE -415

/**
 *	@brief Request returned an http 416 range not satisfiable error
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_HTTP_REQUESTED_RANGE_NOT_SATISFIABLE -416

/**
 *	@brief Request returned an http 417 expectation failed error
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_HTTP_EXPECTATION_FAILED -417

/**
 *	@brief Request returned an http 500 internal server error
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_HTTP_INTERNAL_SERVER_ERROR -500

/**
 *	@brief Request returned an http 501 not implemented error
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_HTTP_NOT_IMPLEMENTED -501

/**
 *	@brief Request returned an http 502 bad gateway error
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_HTTP_BAD_GATEWAY -502

/**
 *	@brief Request returned an http 503 service unavailable error
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_HTTP_SERVICE_UNAVAILABLE -503

/**
 *	@brief Request returned an http 504 gateway timeout error
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_HTTP_GATEWAY_TIMEOUT -504

/**
 *	@brief Request returned an http 505 version not supported error
 *	@ingroup wavmod_errorcodes
 */
#define WA_VMOD_ERROR_HTTP_VERSION_NOT_SUPPORTED -505
