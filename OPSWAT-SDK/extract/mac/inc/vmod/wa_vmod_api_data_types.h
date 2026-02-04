/** @file wa_vmod_api_data_types.h
 *  @brief Defines data types
 *	@defgroup wavmod_datatypes Data types
 *	@brief Defines data types
 */

#ifndef vmod_wa_vmod_api_data_types_h
#define vmod_wa_vmod_api_data_types_h

#include "wa_vmod_api_defs.h"

/**
 *	@typedef __int32 wa_vmod_int
 *	@brief Integer data type
 *	@ingroup wavmod_datatypes
 */
typedef int wa_vmod_int;

/**
 *	@typedef wchar_t wa_vmod_wchar
 *	@brief Character data type
 *	@ingroup wavmod_datatypes
 */
typedef wchar_t wa_vmod_wchar;

/**
 *	@typedef wa_vmod_event_handler
 *	@brief Event handler function pointer for registered events
 *	@ingroup wavmod_datatypes
 */
typedef void (*wa_vmod_event_handler)( wa_vmod_wchar * json_event );

#endif
