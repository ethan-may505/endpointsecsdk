#pragma once
/** @file wa_vmod_api_defs.h
*  @brief Defines boiler plate for used by VCR exports/imports function signatures
*/

#if defined(WIN32) || defined(WIN64) || defined (_MSC_VER)
/**
*	@brief Defines the Windows platform
*/
#define _WA_VMOD_WINDOWS
#define WA_VMOD_DLL_EXT L"dll"
#elif defined (__linux__)
/**
*	@brief Defines the Linux platform
*/
#define _WA_VMOD_LINUX
#define WA_VMOD_DLL_EXT L"so"
#elif defined (__APPLE__)
/**
*	@brief Defines the Mac platform
*/
#define _WA_VMOD_APPLE
#define WA_VMOD_DLL_EXT L"dylib"
#endif

// Module id used in output json when returning an array of results from multiple components
#define WA_VMOD_MODULE_VCR "libwavmodapi." WA_VMOD_DLL_EXT

#ifdef _WA_VMOD_WINDOWS
#ifdef _WA_VMOD_EXPORTS_
/**
*  @brief Defines export function names of the API
*/
#define WA_VMOD_DECLSPEC __declspec(dllexport)
#else
/**
*  @brief Defines import function names of the API
*/
#define WA_VMOD_DECLSPEC __declspec(dllimport)

#endif

/**
*	@brief Defines the export/import macro for function declarations
*/
#define WA_VMOD_DECLFUNCTION WA_VMOD_DECLSPEC int32_t __stdcall

/**
*	@brief Defines the macro for internal function declarations that are not exported or imported
*/
#define WA_VMOD_DECLINTERNAL int32_t __stdcall

#else
/**
 *  @brief Defines import function names of the API
 */
#define WA_VMOD_DECLSPEC __attribute__((visibility("default")))

/**
 *	@brief Defines the export/import macro for function declarations
 */
#define WA_VMOD_DECLFUNCTION WA_VMOD_DECLSPEC int32_t

/**
 *	@brief Defines the macro for internal function declarations that are not exported or imported
 */
#define WA_VMOD_DECLINTERNAL int32_t

#endif

/**
 *  @brief Defines the export/import macro for class declarations
 */
#define WA_VMOD_DECLCLASS WA_VMOD_DECLSPEC

/**
 *	@brief Defines the macro for internal returns without __stdcall
 */
#define WA_VMOD_RETURN int32_t

/**
 *	@brief Defines the max number of bulk queries
 */
const int MAX_BULK_QUERY = 250;
