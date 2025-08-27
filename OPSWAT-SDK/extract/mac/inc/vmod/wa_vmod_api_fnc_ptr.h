/** @file wa_vmod_api_fnc_ptr.h
 *	@brief Defines function names and pointers to make explicit dynamic linking simpler
 *	@defgroup wavmod_helper_pointers Explicit linking helpers
 *	@brief Defines function names and pointers to make explicit dynamic linking simpler
 */

#ifndef vmod_wa_vmod_api_fnc_ptr_h
#define vmod_wa_vmod_api_fnc_ptr_h

#include "wa_vmod_api_data_types.h"

/**
 *	@brief The helper name define for explicit dynamic linking for \ref wa_vmod_api_setup
 *	@ingroup wavmod_helper_pointers
 */
#define WA_VMOD_SETUP_NAME "wa_vmod_api_setup"

/**
 *	@typedef WA_VMOD_SETUP
 *
 *	@brief The helper function pointer define for explicit dynamic linking for \ref wa_vmod_api_setup
 *	@ingroup wavmod_helper_pointers
 *
 *	@note doxygen documentation generation omits the @c __fastcall calling convention, see source of \ref wa_vmod_api_fnc_ptr.h
 */
typedef wa_vmod_int (*WA_VMOD_SETUP) ( const wa_vmod_wchar *, const wa_vmod_wchar * );

/**
 *	@brief The helper name define for explicit dynamic linking for \ref wa_vmod_api_invoke
 *	@ingroup wavmod_helper_pointers
 */
#define WA_VMOD_INVOKE_NAME "wa_vmod_api_invoke"

/**
 *	@typedef WA_VMOD_INVOKE
 *	@brief The helper function pointer define for explicit dynamic linking for \ref wa_vmod_api_invoke
 *	@ingroup wavmod_helper_pointers
 *
 *	@note doxygen documentation generation omits the @c __stdcall calling convention, see source of \ref wa_vmod_api_fnc_ptr.h
 */
typedef wa_vmod_int (*WA_VMOD_INVOKE) ( const wa_vmod_wchar *, wa_vmod_wchar ** );

/**
 *	@brief The helper name define for explicit dynamic linking for \ref wa_vmod_api_free
 *	@ingroup wavmod_helper_pointers
 */
#define WA_VMOD_FREE_NAME "wa_vmod_api_free"

/**
 *	@typedef WA_VMOD_FREE
 *	@brief The helper function pointer define for explicit dynamic linking for \ref wa_vmod_api_free
 *	@ingroup wavmod_helper_pointers
 *
 *	@note doxygen documentation generation omits the @c __stdcall calling convention, see source of \ref wa_vmod_api_fnc_ptr.h
 */
typedef wa_vmod_int (*WA_VMOD_FREE) ( wa_vmod_wchar ** );

/**
 *	@brief The helper name define for explicit dynamic linking for \ref wa_vmod_api_teardown
 *	@ingroup wavmod_helper_pointers
 */
#define WA_VMOD_TEARDOWN_NAME "wa_vmod_api_teardown"

/**
 *	@typedef WA_VMOD_TEARDOWN
 *
 *	@brief The helper function pointer define for explicit dynamic linking for \ref wa_vmod_api_teardown
 *	@ingroup wavmod_helper_pointers
 *
 *	@note doxygen documentation generation omits the @c __stdcall calling convention, see source of \ref wa_vmod_api_fnc_ptr.h
 */
typedef wa_vmod_int (*WA_VMOD_TEARDOWN) ();


#endif
