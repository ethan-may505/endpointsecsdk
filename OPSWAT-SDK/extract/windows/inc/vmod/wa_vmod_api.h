#pragma once
/** @file wa_vmod_api.h
 *	@brief Defines the interface
 *
 *	@defgroup wavmod_integration_interface Functions
 *	@brief The C integration interface. Include @ref wa_vmod_api.h to integrate the API.
 */
#include "wa_vmod_api_defs.h"                    // defines our exporters/importers
#include "wa_vmod_api_error_codes.h"             // defines our error codes
#include "wa_vmod_api_fnc_ptr.h"                 // defines our function pointer helpers
#include "wa_vmod_api_data_types.h"              // defines our data types
#include "wa_vmod_api_config_options.h"          // defines our configuration options
#include "wa_vmod_api_invoke_query.h"            // defines our query methods
#include "wa_vmod_api_json_keys.h"               // defines our json object keys that map to json values

#ifdef __cplusplus
extern "C"
{
#endif

	/**
	 *	@brief Setup the interface with the given license key and configuration.
	 *	@ingroup wavmod_integration_interface
	 *
	 *	@param[in] json_config The configuration options for the interface.
	 *	@param[out] json_out The initialization results.
	 *
	 *	@returns An @ref wavmod_errorcodes "error code"
	 */
	WA_VMOD_DECLFUNCTION wa_vmod_api_setup( const wa_vmod_wchar * json_config , wa_vmod_wchar ** json_out );

	/**
	 *	@brief Register an event handler for the given event. When the event is trigger the handler will be invoked
	 *
	 *	@param[in] json_event_info The information about the event to monitor
	 *	@param[in] event_handler The handler to be invoked when the event is triggered
	 *	@param[out] handler_id The assigned handler id. Used to unregister the handler, if needed.
	 *
	 *	@returns An @ref wavmod_errorcodes "error code"
	 */
	WA_VMOD_DECLFUNCTION wa_vmod_api_register_handler( const wa_vmod_wchar * json_event_info, wa_vmod_event_handler event_handler, wa_vmod_int & handler_id );

	/**
	 *	@brief Will unregister the handler
	 *
	 *	@param[in] handler_id The id of the handler to remove
	 *
	 *	@returns An @ref wavmod_errorcodes "error code"
	 */
	WA_VMOD_DECLFUNCTION wa_vmod_api_unregister_handler( const wa_vmod_int handler_id );

	/**
	 *	@brief Performs an invocation call to the component.
	 *	@ingroup wavmod_integration_interface
	 *
	 *	@param[in] json_in The invocation input to dispatch.
	 *	@param[out] json_out The invocation output results. User can never pass @c NULL, must pass a valid wa_vmod_wchar pointer, which can be @c NULL, that can be allocated with content.
	 *
	 *	@returns An @ref wavmod_errorcodes "error code"
	 */
	WA_VMOD_DECLFUNCTION wa_vmod_api_invoke( const wa_vmod_wchar * json_in, wa_vmod_wchar ** json_out );

	/**
	 *	@brief Will release the memory of the pointer allocated from any double pointer passed to any API call.
	 *	@ingroup wavmod_integration_interface
	 *
	 *	@param[in,out] json_data The pointer to the memory that is to be released
	 *
	 *	@returns A @ref wavmod_errorcodes "error code"
	 */
	WA_VMOD_DECLFUNCTION wa_vmod_api_free( wa_vmod_wchar * json_data );

	/**
	 *	@brief Deinitializes the interface and destructs all internal structures created.
	 *	@ingroup wavmod_integration_interface
	 *
	 *	@returns An @ref wavmod_errorcodes "error code"
	 */
	WA_VMOD_DECLFUNCTION wa_vmod_api_teardown();

#ifdef __cplusplus
} // extern "C"
#endif
