#pragma once
/**
*	@file wa_vmod_api_json_keys.h
*	@brief Defines the JSON object keys used for json_in and json_out values
*
*	@defgroup wavmod_json_keys JSON object key
*	@brief Defines the JSON object keys used for json_in and json_out values
*/

/**
*	@brief Defines our "result" key, for all returned results
*  @brief Represents a JSON Object
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_RESULT L"result"

/**
*	@brief Defines our "results" key, for all returned results from bulk query
*  @brief Represents a JSON Array
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_RESULTS L"results"

/**
*	@brief Defines our "encrypted_result" key, for all returned encrypted data
*  @brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_ENCRYPTED_RESULT L"encrypted_result"

/**
*	@brief Defines our "input" key for all inputs
*  @brief Represents a JSON Object type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_INPUT L"input"

/**
*	@brief Defines our "inputs" key for all inputs in bulk query
*  @brief Represents a JSON Array type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_INPUTS L"inputs"

/**
*	@brief Defines encrypted input
*  @brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_ENCRYPTED_INPUT L"encrypted_input"

/**
*	@brief Defines our "timing" key on all successful results
*  @brief Represents a JSON number type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_TIME L"timing"

/**
*	@brief Defines our 'module' key (for identifying modules when returning multiple results/errors from wa_vmod_api_setup)
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_MODULE L"module"

/**
*	@brief Defines our "error_code" key on failed calls
*  @brief Represents a JSON number type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_ERROR_CODE L"error_code"

/**
*	@brief Defines our "error_trace" key on failed calls
*  @brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_ERRORRACE L"error_trace"

/**
*	@brief Defines our "error_description" key on failed calls
*  @brief Represnts a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_ERROR_DESCRIPTION L"error_description"

/**
*	@brief Defines option to enable/disable showing call tree when the invoke function fails
*	@brief Represents a JSON boolean type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_ENABLE_CALL_TREE L"call_tree"

/**
*	@brief Alias of WA_VMOD_KEY_ENABLE_CALL_TREE
*	@brief Represents a JSON boolean type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_ENABLE_CALLTREE L"calltree"

/**
*	@brief Defines a timestamp for returned query elements
*  @brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_TIMESTAMP  L"timestamp"

/**
*	@brief Defines uid information associated with an element
*  @brief Represents a JSON object type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_UID  L"uid"

/**
*	@brief Defines a component id number
*  @brief Represents a JSON number type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_ID  L"id"

/**
*	@brief Defines the category of products to be detected
*  @brief Represents a JSON number type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_CATEGORY  L"category"

/**
*	@brief Defines the categories of products to be detected
*  @brief Represents a JSON number type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_CATEGORY  L"category"

/**
*	@brief Defines a collection of compliance indicators
*  @brief Represents a JSON object type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_INDICATORS  L"indicators"

/**
*	@brief Defines a Definition Date indicator
*  @brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_INDICATOR_DEF_DATE  L"def_date"

/**
*	@brief Defines a Definition Version indicator
*  @brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_INDICATOR_DEF_VERSION  L"def_version"

/**
*	@brief Defines an Engine Version indicator
*  @brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_INDICATOR_ENGINE_VERSION  L"engine_version"

/**
*	@brief Defines an Engine Name indicator
*  @brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_INDICATOR_ENGINE_NAME  L"am_name"

/**
*	@brief Defines an Definition Signature indicator
*  @brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_INDICATOR_DEF_SIGNATURE  L"def_signature"

/**
*	@brief Defines a Definition Version
*  @brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_DEFINITION_VERSION  L"definition_version"

/**
*	@brief Defines a Definition Signature
*  @brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_DEFINITION_SIGNATURE  L"definition_signature"

/**
*	@brief Defines a Definition Version
*  @brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_DEFINITION_TIME  L"definition_time"

/**
*	@brief Defines a Version of product
*  @brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_EXPECTED_VERSION  L"expected_version"

/**
*	@brief Defines validate
*  @brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_VALIDATE  L"validate_installer"

/**
*	@brief Defines background_patching
*  @brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_BACKGROUND_PATCHING  L"background_patching"

/**
*	@brief Defines user agent from user's input
*  @brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_USER_AGENT  L"user_agent"

/**
*	@brief Defines whether to check file certificate from user's input
*  @brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_SKIP_SIGNATURE_CHECK  L"skip_signature_check"

/**
*	@brief Defines an OESIS Monitor metrics collection
*  @brief Represents a JSON object type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_METRICS  L"metrics"

/**
*	@brief Defines a version count metric
*  @brief Represents a JSON number type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_METRIC_COUNT_BEHIND  L"count_behind"

/**
*	@brief Defines a version count metric (related to Internet Explorer)
*  @brief Represents a JSON number type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_METRIC_COUNT_BEHIND_IE L"ie_count_behind"

/**
*	@brief Defines a version count metric (related to .Net Framework)
*  @brief Represents a JSON number type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_METRIC_COUNT_BEHIND_DOT_NET L"dot_net_count_behind"

/**
*	@brief Defines a details collection
*  @brief Represents a JSON object type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_DETAILS L"details"

/**
*	@brief Defines an array of products affected by some vulnerability
*  @brief Represents a JSON array type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_AFFECTED_PRODUCTS L"affected_products"

/**
*	@brief True - data must be retrieved from source, false - caching can be used.
*  @brief Represents a JSON boolen type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_FORCE_UPDATE L"force_update"

/**
*	@brief >0 - sets timeout in seconds for a non-cached search, used as option for system patch level call
*  @brief Represents a JSON integer type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_FORCE_TIMEOUT L"force_timeout"

/**
*	@brief Defines the OESIS Monitor basic metric
*  @brief Represents a JSON number type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_METRIC_BASIC  L"basic"

/**
*	@brief Defines the OESIS Monitor strict metric
*  @brief Represents a JSON number type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_METRIC_STRICT  L"strict"

/**
*	@brief Defines the OESIS Monitor engine version metric
*  @brief Represents a JSON number type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_METRIC_ENGINE_VERSION  L"engine_version"

/**
*	@brief Defines the OESIS Monitor engine latest metric
*  @brief Represents a JSON number type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_METRIC_ENGINE_LATEST  L"engine_latest"

/**
*	@brief Defines the OESIS Monitor date latest metric
*  @brief Represents a JSON number type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_METRIC_DATE_LATEST  L"date_latest"

/**
*	@brief Defines the OESIS Monitor version latest metric
*  @brief Represents a JSON number type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_METRIC_VERSION_LATEST  L"version_latest"

/**
*	@brief Defines the OESIS Monitor version age metric
*  @brief Represents a JSON number type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_METRIC_VERSION_AGE  L"version_age"

/**
*	@brief Defines the contents of an OESIS Monitor uid feed
*  @brief Represents a JSON array type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_UID_HIST  L"uid_hist"

/**
*	@brief Defines the order of an element in a history with 1 the most recent
*  @brief Represents a JSON number type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_HIST  L"hist"

/**
*	@brief Defines a list of resource elements
*  @brief Represents a JSON array type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_RESOURCE_LIST  L"resource_list"

/**
*	@brief Defines a list of uid elements
*  @brief Represents a JSON array type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_UID_LIST  L"uid_list"

/**
*	@brief Defines a resolution for a vulnerability
*	@brief Represents a JSON array type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_RESOLUTION  L"resolution"

/**
*	@brief Defines a version that a product should update to a newer one to fix some problem
*	@brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_HIGHER_THAN_VERSION L"higher_than_version"

/**
*	@brief Defines a plain text
*	@brief Represents a JSON object type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_TEXT  L"text"

/**
*	@brief Defines an OESIS vendor name
*  @brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_VENDOR_NAME  L"vendor_name"

/**
*	@brief Defines an OESIS vendor id
*  @brief Represents a JSON integer type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_VENDOR_ID  L"vendor_id"

/**
*	@brief Defines an OESIS product id
*  @brief Represents a JSON number type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_PRODUCT_ID  L"product_id"

/**
*	@brief Defines an UpdateVerify update id
*  @brief Represents a JSON number type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_UPDATE_ID  L"update_id"

/**
*	@brief Defines an UpdateVerify history id
*  @brief Represents a JSON number type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_HISTORY_ID  L"history_id"

/**
*	@brief Defines an OESIS product name
*  @brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_PRODUCT_NAME  L"product_name"

/**
*	@brief Defines the parameter represent OESIS product version
*  @brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_PRODUCT_VERSION  L"product_version"

/**
*	@brief Defines the minimum product version
*  @brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_MINIMUM_VERSION  L"minimum_version"

/**
* @brief Defines an element that describe the release date of a product version
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_RELEASE_DATE_ELEM  L"release_date"

/**
*	@brief Defines the parameter represent OESIS product type
*  @brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_PRODUCT_TYPE  L"product_type"

/**
*	@brief Defines an OS id
*  @brief Represents a JSON number type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_OS_ID  L"os_id"

/**
*	@brief Defines a flag to check download (1) or not (0)
*  @brief Represents a JSON number type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_DOWNLOAD  L"download"

/**
* @brief Define the type of the OS
* @brief Represents a JSON number type
* @ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_OS_TYPE L"os_type"

/**
*	@brief Defines the version range of an element
*  @brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_VERSION_RANGE  L"version_range"

/**
*	@brief Defines the parameters used to know status of data queried (from cache, live or in cache and expired)
*  @brief Represents a JSON number type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_DATA_STATUS  L"data_status"

/**
*	@brief Defines the parameters used to query the OPSWAT vmod server
*  @brief Represents a method id number
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_METHOD_ID  L"method"

/**
*	@brief Defines the return code returned by the API
*  @brief Represents a return code number
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_RETURN_CODE  L"code"

/**
*	@brief Defines the data returned by the API
*  @brief Represents a JSON object type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_DATA  L"data"

/**
*	@brief Defines the parameters used to query the OPSWAT vmod server
*  @brief Represents a JSON object type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_QUERY_PARAMS  L"qparams"

/**
*	@brief Defines an Resource Object returned from a bulk query
*  @brief Represnts a JSON object type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_RESOURCES  L"resources"

/**
*	@brief Defines the parameter represent security interface from V3
*  @brief Represents a JSON integer type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_DETECTION_INTERFACE  L"detection_interface"

/**
*	@brief Defines the parameter represent OOD initialize result
*  @brief Represents a JSON object type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_OOD  L"ood"

/**
*	@brief Defines the parameter represent OOD initialization status
*  @brief Represents a JSON integer type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_STATUS  L"status"

/**
*	@brief Defines the parameter represent detected products info
*  @brief Represents a JSON object type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_PRODUCTS_INFO  L"products_info"

/**
*	@brief Defines the parameter represent one detected product info
*  @brief Represents a JSON object type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_DETECTED_PRODUCT  L"detected_product"

/**
*	@brief Defines the parameter represent detected products
*  @brief Represents a JSON object type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_DETECTED_PRODUCTS  L"detected_products"

/**
*	@brief Defines the parameter represent array of products
*  @brief Represents a JSON array type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_PRODUCTS  L"products"

/**
*	@brief Defines a element describing browser status
*  @brief Represents a JSON object type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_BROWSER_STATUS  L"browser_status"

/**
*	@brief Defines a element describing whether product is running or not
*  @brief Represents a JSON bool type
*	@ingroup bool
*/
#define WA_VMOD_KEY_IS_RUNNING  L"is_running"

/**
*	@brief Defines a element describing is product is the default for this product type
*  @brief Represents a JSON bool type
*	@ingroup bool
*/
#define WA_VMOD_KEY_IS_DEFAULT  L"is_default"

/**
*	@brief Defines an OESIS Resource Object returned when a a query delivers a specific OESIS product
*  @brief Represnts a JSON object type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_OESIS_RESOURCE  L"prod_resource"

/**
*	@brief Defines the parameter represent OESIS product information
*  @brief Represents a JSON object type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_PUID  L"puid"

/**
*	@brief Defines the parameter represent OESIS product metric
*  @brief Represents a JSON object type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_PROD_METRICS  L"prod_metrics"

/**
*	@brief Defines the parameter represent OESIS product version
*  @brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_PROD_VERSION  L"prod_version"

/**
*	@brief Defines the parameter represent OESIS product record, which contains latest product version
*  @brief Represents a JSON object type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_RECORD  L"record"

/**
*	@brief Defines the parameter represent OESIS product remediations
*  @brief Represents a JSON array type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_REMEDIATIONS  L"remediations"

/**
*	@brief Defines the parameter represent an OESIS product remediation
*  @brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_REMEDIATION  L"remediation"

/**
*	@brief Defines an element that describes an Operating System
*  @brief Represents a JSON object type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_OS_ELEM  L"os"

/**
*	@brief Defines an element name
*  @brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_ELEM_NAME  L"name"

/**
*	@brief Defines an element that describes a product
*  @brief Represents a JSON object type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_PRODUCT_ELEM  L"product"

/**
*	@brief Defines an element that describes a vendor
*  @brief Represents a JSON object type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_VENDOR_ELEM  L"vendor"

/**
*	@brief Defines an element that describes a product's current version
*  @brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_CURRENT_VERSION L"current_version"

/**
*	@brief Defines an element that describes a product version
*  @brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_VERSION_ELEM  L"version"

/**
*	@brief Defines an element that describes an array of product versions
*  @brief Represents a JSON array type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_VERSIONS_ELEM  L"versions"

/**
*	@brief Defines an element that describe the release date of a product version
*  @brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_DATE_ELEM  L"date"

/**
*	@brief Defines an element that describes an indicator
*  @brief Represents a JSON object type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_INDICATORS_ELEM  L"indicators"

/**
*	@brief Defines an element containing regular expression strings
*  @brief Represents a JSON object type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_QUERY_REGEXES  L"regexes"

/**
*	@brief Defines a regular expression that matches a product name
*  @brief Represents a JSON string
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_QUERY_PRODUCT_REGEX  L"product_regex"

/**
*	@brief Defines a regular expression that matches a vendor name
*  @brief Represents a JSON string
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_QUERY_VENDOR_REGEX  L"vendor_regex"

/**
*	@brief Defines a query element that determines the 'history limit' of a metric
*  @brief Represents a JSON number type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_QUERY_HIST_LIMIT  L"hist_limit"

/**
*	@brief Defines a query element for matching the version of a product
*  @brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_QUERY_VERSION  L"version"

/**
*	@brief Defines a query element for specifying the desired type of result
*  @brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_QUERY_RESULT_TYPE  L"type"

/**
*	@brief Defines a format
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_RESULT_QUERY_FORMAT  L"format"

/**
*	@brief Defines a query parameter that forces the return of a list
*  @brief Represents a JSON boolean type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_QUERY_FORCE_LIST_FORMAT  L"force_list"

/**
*	@brief Defines the page number of a list of results
*  @brief Represents a JSON number type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_LIST_PAGE  L"page"

/**
*	@brief Defines a previous page of results
*  @brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_PREV_LIST_URI  L"prev"

/**
*	@brief Defines a next page of results
*  @brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_NEXT_LIST_URI  L"next"


/**
*	@brief Defines a uri string
*  @brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_URI  L"uri"

/**
*	@brief Defines our 'config' key
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_CONFIGURATION L"config"

/**
*	@brief Defines our 'configs' key
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_CONFIGURATIONS L"configs"

/**
*	@brief Defines our 'error' key
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_ERROR L"error"

/**
*	@brief Defines our 'errors' key
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_ERRORS L"errors"

/**
*	@brief Defines our 'teardown' key (for invoking teardown via wa_vmod_invoke)
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_TEARDOWN L"teardown"

/**
*	@brief Defines our 'is_current' key
*	@brief Represents a boolean type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_IS_CURRENT L"is_current"

/**
*	@brief Defines our 'details' key
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_DETAILS L"details"

/**
*	@brief Defines our 'is_missing_service_pack' key
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_IS_MISSING_SERVICE_PACK L"is_missing_service_pack"

/**
*	@brief Defines the patch id
*	@brief Represents a number type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_PATCH_ID L"patch_id"

/**
*	@brief Defines the feed id
*	@brief Represents a number type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_FEED_ID L"feed_id"

/**
*	@brief Defines our 'timeframe' key
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_TIMEFRAME L"timeframe"

/**
*	@brief Defines our 'signature' key
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_SIGNATURE L"signature"

/**
*	@brief Defines our 'new_signature' key
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_NEW_SIGNATURE L"new_signature"

/**
*	@brief Defines the max number of definitions in history to check
*	@brief Represents a number type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_TOLERANCE L"tolerance"

/**
*	@brief Defines the type of antimalware product
*	@brief Represents a number type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_AM_TYPE L"am_type"

/**
*	@brief Defines whether the product is defunct or not
*	@brief Represents a boolean type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_IS_DEFUNCT L"is_defunct"

/**
*	@brief Defines the link to product
*	@brief Represents a string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_REMEDIATION_LINK L"remediation_link"

/**
*	@brief Defines our 'expiration' key
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_EXPIRATION L"expiration"

/**
*	@brief Defines our 'enabled' key
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_ENABLED L"enabled"

/**
*	@brief Defines our 'get_current_config' key
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_GET_CURRENT_CONFIG L"get_current_config"

/**
*	@brief Defines our 'reset_defaults' key
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_RESET_DEFAULTS L"reset_defaults"

/**
*	@brief Defines whether VMod should take input from user or from detection
*	@brief Represents a boolean type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_DIRECT_INPUT L"direct_input"

/**
* @brief Define the description
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_DESCRIPTION L"description"

/////////////////////keys for Offline VMod//////////////////////////////////////////////
/**
* @brief Define whether a query use offline VMod or not
* @brief Represents a JSON boolean type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_OFFLINE L"offline"

/**
* @brief Define the database content as string
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_DB_INPUT_SOURCE L"dat_input_source"

/**
* @brief Define the path to the file that contain database
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_DB_INPUT_SOURCE_FILE L"dat_input_source_file"

/**
*	@brief Defines path to checksum database
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_DB_INPUT_CHECKSUM_FILE L"dat_input_checksum_file"

/**
* @brief Define the path to the location to save database to
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_DB_OUTPUT_SOURCE_FILE L"dat_output_source_file"

/**
* @brief Define whether to update database files using delta (diff) mechanism or not
* @brief Represents a JSON number type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_DELTA_UPDATE L"delta_update"

/**
* @brief Define the database download information
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_DB_DOWNLOAD_INFO L"dat_download_info"

/**
* @brief Define the database name
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_DB_NAME L"dat_name"

/**
* @brief Define the database timestamp
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_DB_TIMESTAMP L"dat_timestamp"

/**
* @brief Define the path to the file that contain VMod SCAP database
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_SCAP_INPUT_SOURCE_FILE L"scap_input_source_file"

/**
* @brief Define the token string provided to download database
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_TOKEN L"token"

/**
* @brief Define the name of a file
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_FILE_NAME L"file_name"

///////////////////CVSS info//////////////////
/**
* @brief Define the score of the CVSS
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_CVSS_SCORE L"score"

/**
* @brief Define the access vector field of the CVSS
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_CVSS_ACCESS_VECTOR L"access_vector"

/**
* @brief Define the access complexity field of the CVSS
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_CVSS_ACCESS_COMPLEXITY L"access_complexity"

/**
* @brief Define the authentication field of the CVSS
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_CVSS_AUTHENTICATION L"authentication"

/**
* @brief Define the impact of a vulnerability
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_IMPACT L"impact"

/**
* @brief Define the confidentiality impact of the CVSS
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_CVSS_CONFIDENTIALITY_IMPACT L"confidentiality_impact"

/**
* @brief Define the availability impact of the CVSS
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_CVSS_AVAILABILITY_IMPACT L"availability_impact"

/**
* @brief Define the integrity impact of the CVSS
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_CVSS_INTEGRITY_IMPACT L"integrity_impact"

/**
* @brief Define the source of the CVSS
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_CVSS_SOURCE L"source"

/**
* @brief Define the timestamp of the generated time of the CVSS
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_CVSS_GENERATED_ON_EPOCH L"generated_on_epoch"

/**
* @brief Define the CWE of the CVSS
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_CVSS_CWE L"cwe"

/**
* @brief Define the CPE of the CVSS
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_CVSS_CPE L"cpe"

/**
* @brief Define the CVE of the CVSS
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_CVSS_CVE L"cve"

/**
* @brief Define the ELEMENT field of the static_feed
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_ELEMENT L"element"

/**
* @brief Define the CVE of the ELEMENT
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_ELEMENT_CVE L"cve"

/**
* @brief Define the timestamp of the publishing time of the CVSS
* @brief Represents a JSON number type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_CVSS_PUBLISHED_EPOCH L"published_epoch"

/**
* @brief Define the timestamp of the last modified time of the CVSS
* @brief Represents a JSON number type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_CVSS_LAST_MODIFIED_EPOCH L"last_modified_epoch"

/**
* @brief Define the references of the CVSS
* @brief Represents a JSON array type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_CVSS_REFERENCES L"references"

/**
* @brief Define the products information related to the CVE
* @brief Represents a JSON array type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_OPSWAT_PRODUCTS_INFO L"opswat_products_info"

/**
* @brief Define the ranges of product's versions
* @brief Represents a JSON array type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_RANGES L"ranges"

/**
* @brief Define the start of a version range
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_START L"start"

/**
* @brief Define the end of a version range
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_LIMIT L"limit"

/**
* @brief Define the CVSS
* @brief Represents a JSON object type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_CVSS L"cvss"

/**
* @brief Define the CVSS 2.0
* @brief Represents a JSON object type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_CVSS_2_0 L"cvss_2_0"

/**
* @brief Define the CVSS 3.0
* @brief Represents a JSON object type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_CVSS_3_0 L"cvss_3_0"

/**
* @brief Define the impact score of a vulnerability
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_IMPACT_SCORE L"impact_score"

/**
* @brief Define the vector string of a vulnerability
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_VECTOR_STRING L"vector_string"

/**
* @brief Define the attack vector of a vulnerability
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_ATTACK_VECTOR L"attack_vector"

/**
* @brief Define the attack complexity of a vulnerability
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_ATTACK_COMPLEXITY L"attack_complexity"

/**
* @brief Define the privileges required to trigger a vulnerability
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_PRIVILEGES_REQUIRED L"privileges_required"

/**
* @brief Define the user interaction required to trigger a vulnerability
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_USER_INTERACTION L"user_interaction"

/**
* @brief Define the scope of a vulnerability
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_SCOPE L"scope"

/**
* @brief Define the confidentiality impact of a vulnerability
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_CONFIDENTIALITY_IMPACT L"confidentiality_impact"

/**
* @brief Define the integrity impact of a vulnerability
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_INTEGRITY_IMPACT L"integrity_impact"

/**
* @brief Define the availability impact of a vulnerability
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_AVAILABILITY_IMPACT L"availability_impact"

/**
* @brief Define the base score of a vulnerability
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_BASE_SCORE L"base_score"

/**
* @brief Define the base severity of a vulnerability
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_BASE_SEVERITY L"base_severity"

/**
* @brief Define the exploitability score of a vulnerability
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_EXPLOITABILITY_SCORE L"exploitability_score"

/**
* @brief Define the severity index
* @brief Represents a JSON number type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_SEVERITY_INDEX L"severity_index"

/**
* @brief Define the severity protection
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_SECURITY_PROTECTION L"security_protection"

/**
* @brief Define the severity string of the corresponding severity index
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_SEVERITY L"severity"

/**
* @brief Define whether a product or a file has CVE vulnerability or not
* @brief Represents a JSON boolean type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_HAS_VULNERABILITY L"has_vulnerability"

/**
* @brief Define whether a product has any KB or MSB associated with it or not
* @brief Represents a JSON boolean type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_HAS_KB L"has_kb"

/**
* @brief Define the array of vulnerabilities of a product
* @brief Represents a JSON array type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_VULNERABILITIES L"vulnerabilities"

/**
* @brief Define the static id
* @brief Represents a JSON number type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_STATIC_ID L"static_id"

/**
* @brief Define the array of static id
* @brief Represents a JSON array type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_STATIC_IDS L"static_ids"

///////////////////Infection module//////////////////
/**
* @brief Define the hash to be used in functions querying infection database
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_HASH L"hash"

/**
*	@brief Defines number of hashes in database
*	@brief Represents a JSON number type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_NUM_HASHES L"number_of_hashes"

/**
* @brief Define information associated with product version
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_VERSION_DATA L"version_data"

/**
* @brief Define signature name
* @brief Represents a JSON string type
* @ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_SIG_NAME L"sig_name"

/**
*	@brief Defines the information on a file
*	@brief Represents a JSON object type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_FILE_INFO  L"file_info"

/**
*	@brief Defines the SHA1 hash
*	@brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_SHA1  L"sha1"

/**
*	@brief Defines the MD5 hash
*	@brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_MD5 L"md5"
/**
*	@brief Defines the MD5 hash from data
*	@brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_EXPECTED_MD5 L"expected_md5"

/**
*	@brief Defines the sha1 hash from data
*	@brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_EXPECTED_SHA1 L"expected_sha1"

/**
*	@brief Defines the sha256 hash from data
*	@brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_EXPECTED_SHA256 L"expected_sha256"

/**
*	@brief Defines the sha512 hash from data
*	@brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_EXPECTED_SHA512 L"expected_sha512"

/**
*	@brief Defines the SHA256 hash
*	@brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_SHA256  L"sha256"

/**
*	@brief Defines the serial number
*	@brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_SERIAL_NUMBER L"serial_number"

/**
*	@brief Defines the array certificates
*	@brief Represents a JSON array string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_CERTIFICATES L"certificates"

/**
*	@brief Defines the issuer
*	@brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_ISSUER L"issuer"

/**
*	@brief Defines the signature algorithm
*	@brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_SIG_ALGORITHM L"signature_algorithm"

/**
*	@brief Defines the subject
*	@brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_SUBJECT L"subject"

/**
*	@brief Defines the parameter represent an raw file
*	@brief Represents a JSON object type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_RAW_FILE  L"raw_file"

/**
*	@brief Defines the parameter represent a file name
*	@brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_FILE_NAME  L"file_name"

/**
*	@brief Defines the parameter represent version of a file
*	@brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_FILE_VERSION  L"version"

/**
*	@brief Defines the parameter represent id of a CVE element
*	@brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_CVE_ID  L"cve_id"

/**
* @brief Define Microsoft Security Bulletin ID
* @brief Represents a JSON string type
* @ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_MSB_ID L"msb_id"

/**
* @brief Define Microsoft Security Bulletin ID
* @brief Represents a JSON string type
* @ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_MSB L"msb"

/**
* @brief Define an array of Microsoft Security Bulletins
* @brief Represents a JSON array type
* @ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_MSBS L"msbs"

/**
* @brief Define a Knowledge Base article ID
* @brief Represents a JSON string type
* @ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_KB_ID L"kb_id"

/**
* @brief Define a Knowledge Base article ID
* @brief Represents a JSON string type
* @ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_KB L"kb"

/**
* @brief Define an array of Knowledge Base articles
* @brief Represents a JSON array type
* @ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_KBS L"kbs"

/**
* @brief Define an array of CVE IDs
* @brief Represents a JSON array type
* @ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_CVES L"cves"

/**
* @brief Define a type of some piece of information
* @brief Represents a JSON string type
* @ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_TYPE L"type"

/**
* @brief Define name of a platform
* @brief Represents a JSON string type
* @ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_PLATFORM L"platform"

/**
* @brief Define a URL
* @brief Represents a JSON string type
* @ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_URL L"url"

/**
* @brief Define a URL for searching a KnowledgeBase
* @brief Represents a JSON string type
* @ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_SEARCH_URL L"search_url"

/**
* @brief Define a URL for more details regarding a KnowledgeBase
* @brief Represents a JSON string type
* @ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_DETAIL_URL L"detail_url"

/**
* @brief Define a URL for more information on the CVEs associatied with a KnowledgeBase
* @brief Represents a JSON string type
* @ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_ADVISORY_URL L"advisory_url"

/**
* @brief Define the JSON container for a knowledge base ID and its URL that are related to a Microsoft Security Bulletin
* @brief Represents a JSON object type
* @ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_PATCH_RESOLUTION L"patch_resolution"

/**
* @brief Define the array of Microsoft Security Bulletin (MSB) IDs superseded by a MSB
* @brief Represents a JSON array type
* @ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_SUPERSEDES L"supersedes"

/**
* @brief Define the timestamp at which the information was published
* @brief Represents a JSON number type
* @ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_MSB_PUBLISHED_EPOCH L"published_epoch"

/**
* @brief Define the date at which the information was published
* @brief Represents a JSON string type
* @ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_MSB_PUBLISHED_DATETIME L"published_datetime"

/**
* @brief Define the architecture of the OS
* @brief Represents a JSON string type
* @ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_ARCHITECTURE L"architecture"

/**
* @brief Define the architecture of the OS for some special products
* @brief Represents a JSON string type
* @ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_OS_ARCHITECTURE L"os_architecture"

/**
* @brief Define the log directory
* @brief Represents a JSON string type
* @ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_LOG_DIR L"log_dir"

/**
* @brief Define the service pack version of the OS
* @brief Represents a JSON string type
* @ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_SERVICE_PACK L"service_pack"

/**
* @brief Define product channel
* @brief Represents a JSON string type
* @ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_CHANNEL L"channel"



/**
* @brief Define the sources of vulnerability database
* @brief Represents a JSON array type
* @ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_SOURCES L"sources"

/**
* @brief Define the MSB source of vulnerabilities
* @brief Represents a JSON string type
* @ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_SOURCE_MSB L"MSB"

/**
* @brief Define the CVE source of vulnerabilities
* @brief Represents a JSON string type
* @ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_SOURCE_CVE L"CVE"

/**
* @brief Define the KB source of vulnerabilities
* @brief Represents a JSON string type
* @ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_SOURCE_KB L"KB"

/**
* @brief Defines the id list of installed OS patches
* @brief Represents a JSON array type
* @ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_INSTALLED_PATCHES L"installed_patches"

/**
* @brief Defines the id list of missing OS patches
* @brief Represents a JSON array type
* @ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_MISSING_PATCHES L"missing_patches"

/**
* @brief Define the timestamp of the publishing time of the information
* @brief Represents a JSON string type
* @ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_PUBLISHED_EPOCH L"published_epoch"

/**
* @brief Define the timestamp of the last modified time of the information
* @brief Represents a JSON string type
* @ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_CONTENT_UPDATED_EPOCH L"content_updated_epoch"

/**
* @brief Define the current baseline epoch
* @brief Represents a JSON string type
* @ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_CURRENT_BASELINE_EPOCH L"current_baseline_epoch"

/**
* @brief Define the date at which the information was published
* @brief Represents a JSON string type
* @ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_PUBLISHED_DATETIME L"published_datetime"

/**
*	@brief Defines verison of database's schema
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_SCHEMA_VERSION  L"schema_version"

/**
*	@brief Defines number of CVEs in database
*	@brief Represents a JSON number type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_NUM_CVES L"number_of_cves"

/**
*	@brief Defines number of MSBs in database
*	@brief Represents a JSON number type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_NUM_MSBS L"number_of_msbs"

/**
*	@brief Defines number of KBs in database
*	@brief Represents a JSON number type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_NUM_KBS L"number_of_kbs"

///////////////////VMod SCAP module//////////////////
/**
*	@brief Defines whether to collect data again or reuse collected data if possible
*	@brief Represents a JSON boolean type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_RECOLLECT L"recollect"

/**
* @brief Define a simple view of the test
* @brief Represents a JSON object type
* @ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_TEST L"test"

/**
* @brief Define the list of tests
* @brief Represents a JSON array type
* @ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_TESTS L"tests"

/**
*	@brief Define a clue for a reason
*	@brief Represents JSON object type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_CLUE L"clue"

/**
*	@brief Define the type of a clue
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_TYPE L"type"

/**
*	@brief Define the array of clues
*	@brief Represents a JSON array type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_ITEMS L"items"

/**
*	@brief Defines a language identifier of downloaded product file (same format as OESIS)
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_LANGUAGE L"language"

/**
*	@brief Define the path
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_PATH L"path"

/**
*	@brief Define the file size in bytes
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_SIZE L"size"

/**
*	@brief Define the eula link
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_EULA L"eula"

/**
*	@brief Define the release note link
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_REALASE_NOTE L"release_note"

/**
*	@brief Define the source timestamp
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_SOURCE_TIMESTAMP L"source_timestamp"

/**
*	@brief Defines the processes flag
*	@brief Represents a JSON number type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_FORCE_CLOSE  L"force_close"

/**
*	@brief Defines whether to uninstall product before installation
*	@brief Represents a JSON number type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_UNINSTALL_FIRST  L"uninstall_first"

/**
*	@brief Defines whether the product need to be uninstalled before installation
*	@brief Represents a JSON number type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_REQUIRE_UNINSTALL_FIRST L"require_uninstall_first"

/**
*	@brief Defines whether the machine need to be restarted after installation
*	@brief Represents a JSON number type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_REQUIRE_RESTART  L"require_restart"

/**
*	@brief Defines whether the application need restart to apply the update
*	@brief Represents a JSON number type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_REQUIRE_APP_RESTART  L"require_app_restart"

/**
*	@brief Defines whether the product need to be closed before installation
*	@brief Represents a JSON number type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_REQUIRE_CLOSE_FIRST  L"require_close_first"

/**
*	@brief Defines the return code returned by the installer after installation
*	@brief Represents a JSON number type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_INSTALL_RETURN_CODE L"install_return_code"

/**
*	@brief Defines names or paths of the processes blocked the installation
*	@brief Represents a JSON array type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_BLOCKING_PROCESSES  L"blocking_processes"

/**
*	@brief Defines paths to the log files of installation
*	@brief Represents a JSON array type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_LOG_PATHS  L"log_paths"

/**
*	@brief Defines patch data
*	@brief Represents a JSON object type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_PATCH_DATA  L"patch_data"

/**
*	@brief Defines user input
*	@brief Represents a JSON object type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_USER_INPUT L"user_input"

/**
*	@brief Defines use delta update or not
*	@brief Represents a JSON bool type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_USE_WUO_DELTA L"use_delta"

/**
*	@brief Defines delta operation mode
*	@brief Represents a JSON bool type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_USE_WUO_DELTA_FLOW L"use_delta_flow"

/**
*	@brief Defines path to a file
*	@brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_FILE_PATH L"file_path"

/**
*	@brief Defines groupId
*	@brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_GROUP_ID L"groupId"

/**
*	@brief Defines artifactId
*	@brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_ARTIFACT_ID L"artifactId"

/**
*	@brief Defines support signature for auto patching
*	@brief Represents a JSON array type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_SUPPORT_SIGNATURES L"support_signatures"

/**
*	@brief Defines support install only signatures for auto patching
*	@brief Represents a JSON array type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_SUPPORT_INSTALL_SIGNATURES L"support_install_signatures"

/**
*	@brief Defines signatures for products for which auto-patching only support downloading and installation but do not support link retrieval
*	@brief Represents a JSON array type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_SELF_UPDATE_SIGNATURES L"self_update_signatures"

/**
*	@brief Defines index in an array
*	@brief Represents a JSON number type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_INDEX L"index"

/**
*	@brief Define the type identifier of output schema
*	@brief Represents a JSON number type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_TYPE_ID L"type_id"

/**
*	@brief Defines our 'ap_checksum' key
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_CHECKSUMS_DB L"checksums_db"


/**
*	@brief Define the type identifier of output schema
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_FILE_TYPE L"file_type"

/**
*	@brief Define whether to use online database
*	@brief Represents a JSON number type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_ONLINE L"online"

/**
*	@brief Defines list of vulnerability identifiers to be ignored
*	@brief Represents a JSON array type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_WHITELIST_VULNERABILITIES L"whitelist_vulnerabilities"

/**
*	@brief Defines our 'analog_id' key
*	@ingroup waapi_json_keys
*/
#define  WA_VMOD_KEY_ANALOG_ID L"analog_id"

/**
*	@brief Defines list of break packages
*	@brief Represents a JSON array type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_BREAK_PACKAGES L"breaks"

/**
*	@brief Defines list of prerequisite packages
*	@brief Represents a JSON array type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_PREREQUISITE_PACKAGES L"prerequisites"

/**
*	@brief Defines list of depend packages
*	@brief Represents a JSON array type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_DEPEND_PACKAGES L"depends"

/**
*	@brief Defines an array of packages affected by some vulnerability
*   @brief Represents a JSON array type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_AFFECTED_PACKAGES L"affected_packages"

/**
*	@brief Defines package name
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_PACKAGE_NAME L"package"

/**
*	@brief Defines source name of package
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_PACKAGE_SOURCE L"source"

/**
*	@brief Defines section of package
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_PACKAGE_SECTION L"section"

/**
*	@brief Defines maintainer name of package
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_PACKAGE_MAINTAINER L"maintainer"

/**
*	@brief Defines version string of package
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_PACKAGE_VERSION L"version"

/**
*	@brief Defines list of patches that can fix the CVE
*	@brief Represents a JSON Array
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_PATCHES L"patches"

/**
*	@brief Defines KB id for this KB, patch id for 3rd-party apps
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_UPDATE_ID L"update_id"

/**
*	@brief Defines Is the KB installable to this machine.
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_INSTALLABLE L"installable"

/**
*	@brief Defines list of input KBs to check if it is patchable
*	@brief Represents a JSON Array type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_UPDATE_IDS L"update_ids"

/**
*	@brief Defines list of output KBs is patched successfully
*	@brief Represents a JSON Array type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_RESOLVED_UPDATE_IDS L"resolved_update_ids"

/**
*	@brief Defines max loop get version after install product
*	@brief Represents a JSON int type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_MAX_LOOP_GET_VERSION L"max_loop_get_version"

/**
*	@brief Defines expected loop get version after install product
*	@brief Represents a JSON int type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_EXPECTED_LOOP_GET_VERSION L"expected_loop_get_version"

/**
*	@brief Defines ps_script object in the patch_*.dat.
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_PS_SCRIPT L"ps_script"

/**
*	@brief Defines patch_info object in the patch_*.dat.
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_PATCH_INFO L"patch_info"

/**
*	@brief Defines release_note_link field in the patch_*.dat.
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_RELEASE_NOTE_LINK L"release_note_link"

/**
*	@brief Defines eula_link field in the patch_*.dat.
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_EULA_LINK L"eula_link"

/**
*	@brief Defines install_param field in the patch_*.dat.
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_INSTALL_PARAM L"install_param"

/**
*	@brief Defines extract_first field in the patch_*.dat.
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_EXTRACT_FIRST L"extract_first"

/**
*	@brief Defines cu_install_type field in the patch_*.dat.
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_CU_INSTALL_TYPE L"cu_install_type"

/**
*	@brief Defines blocking_categories field in the patch_*.dat.
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_BLOCKING_CATEGORIES L"blocking_categories"

/**
*	@brief Defines blocking_pids field in the patch_*.dat.
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_BLOCKING_PIDS L"blocking_pids"

/**
*	@brief Defines alternative_signatures field in the patch_*.dat.
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_ALTERNATIVE_SIGNATURES L"alternative_signatures"

/**
*	@brief Defines require_version field in patching linux.
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_REQUIRED_VERSION L"required_version"

/**
*	@brief Defines require_version field in patching linux.
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_TO_BE_UPDATED_VERSION L"to_be_updated_version"

/**
*	@brief Defines dependencies field in patching linux.
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_DEPENDENCIES  L"dependencies"

/**
*	@brief Defines dependencies_installed field in patching linux.
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_DEPENDENCIES_INSTALLED  L"dependencies_installed"

/**
*	@brief Defines dependencies_missing field in patching linux.
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_DEPENDENCIES_MISSING L"dependencies_missing"

/**
*	@brief Defines dependencies_missing field in patching linux.
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_DEPENDENCIES_MODIFIED L"modified_dependencies"

/**
*	@brief Defines children field in patching linux.
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_CHILDREN L"children"

/**
* @brief Define the architectures of the OS
* @brief Represents a JSON string type
* @ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_ARCHITECTURES L"architectures"

/**
* @brief Define the level field in patching linux.
* @brief Represents a JSON string type
* @ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_LEVEL L"level"

/**
* @brief Define the provides of a package.
* @brief Represents a JSON string type
* @ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_PROVIDES L"provides"

/**
*	@brief Defines language_default field in the patch_*.dat.
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_LANGUAGE_DEFAULT L"language_default"

/**
*	@brief Defines os_arch_bl field in the patch_*.dat.
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_OS_ARCH_BL L"os_arch_bl"

/**
*	@brief Defines link_patterns field in the patch_*.dat.
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_LINK_PATTERNS L"link_patterns"

/**
*	@brief Defines use_os_architecture field in the patch_*.dat.
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_USE_OS_ARCHITECTURE L"use_os_architecture"

/**
*	@brief Defines the latest product version
*  @brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_LATEST_VERSION  L"latest_version"

/**
*   @brief Defines the extract package list script in patch data
*   @brief Represents a JSON string type
*	@ingroup wavmod_json_keys
*/
#define WA_VMOD_KEY_EXTRACT_PACKAGE_LIST  L"extract_package_list"
/*
*	@brief Defines script object in the patch_*.dat.
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_SCRIPT L"script"

/**
*	@brief Defines max timeout.
*	@brief Represents a JSON int type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_MAX_TIMEOUT L"max_timeout"

/**
*	@brief Defines script type in embedded scripting.
*	@brief Represents a JSON int type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_SCRIPT_TYPE L"script_type"

/**
*	@brief Defines script data in embedded scripting.
*	@brief Represents a JSON object type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_SCRIPT_PARAM L"script_param"

/**
*	@brief Defines script content in embedded scripting.
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_SCRIPT_CONTENT L"content"

/**
*	@brief Defines script return value in embedded scripting.
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_SCRIPT_RETURN L"script_return"


/**
*	@brief Defines script content in embedded scripting.
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_ERROR_MESSAGE L"error_message"

/**
*	@brief Defines not available field.
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_NOT_AVAILABLE L"n/a"

/**
*	@brief Defines resolvable cves field.
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_RESOLVABLE_CVES L"resolvable_cves"

/**
*	@brief Defines enable resolved cves field.
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_ENABLE_RESOLVED_CVES L"enable_resolved_cves"

/**
*	@brief Defines delay time.
*	@brief Represents a JSON integer type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_DELAY L"delay"

/**
*	@brief Defines current time.
*	@brief Represents a JSON number type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_CURRENT_TIME L"current_time"

/**
*	@brief Defines patch release timestamp.
*	@brief Represents a JSON number type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_PATCH_RELEASE_TIMESTAMP L"patch_release_timestamp"

/**
*	@brief Defines filter package for GetLatesInstaller and GetProducVuln via Package Manager.
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_PACKAGE_FILTER L"package_filter"

/**
*	@brief Defines enable resolved cves field.
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_SYSTEM_PACKAGE_MAPPING L"system_package_mapping"

/**
*	@brief Defines Is the freezing dependencies list.
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_FREEZING_DEPENDENCIES L"freezing_dependencies"

/**
*   @brief Pre-installation package statuses
*/

/**
*	@brief Defines package status: installable
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_DEP_STATUS_INSTALLABLE L"installable"

/**
*	@brief Defines package status: not_installable
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_DEP_STATUS_NOT_INSTALLABLE L"not_installable"

/**
*	@brief Defines package status: resolved
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_DEP_STATUS_RESOLVED L"resolved"

/**
*	@brief Defines package status: upgradable
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_DEP_STATUS_UPGRADABLE L"upgradable"

/**
*	@brief Defines package status: downgradable
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_DEP_STATUS_DOWNGRADABLE L"downgradable"

/**
*	@brief Defines package status: removable 
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_DEP_STATUS_REMOVABLE L"removable"

/**
*   @brief Post-installation package statuses
*/

/** 
*   @brief Defines package status: upgraded (package updated to new version)
*   @brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_STATUS_UPGRADED L"upgraded"

/**
*   @brief Defines package status: installed (package newly installed as a result of a patch)
*   @brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_STATUS_INSTALLED L"installed"

/**
*   @brief Defines package status: removed (package removed as a result of a patch)
*   @brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_STATUS_REMOVED L"removed"

/**
*   @brief Defines package status: downgraded (package downgraded to an older version)
*   @brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_STATUS_DOWNGRADED L"downgraded"

/**
*   @brief Defines package status: not_found
*   @brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_STATUS_NOT_FOUND L"not_found"

/**
*   @brief Defines package status: not_found_in_cache
*   @brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_STATUS_NOT_FOUND_IN_CACHE L"not_found_in_cache"

/**
*   @brief Defines package status: download_failed
*   @brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_STATUS_DOWNLOAD_FAILED L"download_failed"

/**
*   @brief Defines package status: cache_failed
*   @brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_STATUS_CACHE_FAILED L"cached_failed"

/**
*   @brief Defines package status: install_failed
*   @brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_STATUS_INSTALL_FAILED L"install_failed"

/**
*   @brief Defines patch category: security_update
*   @brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_PATCH_CATEGORY_SECURITY_UPDATE L"security_update"

/**
*   @brief Defines patch category: update_rollup
*   @brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_PATCH_CATEGORY_UPDATE_ROLLUP L"update_rollup"

/**
*   @brief Defines patch category: critical_update
*   @brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_PATCH_CATEGORY_CRITICAL_UPDATE L"critical_update"

/**
*   @brief Defines patch category: update
*   @brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_PATCH_CATEGORY_UPDATE L"update"

/**
*   @brief Defines patch category: driver
*   @brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_PATCH_CATEGORY_DRIVER L"driver"

/**
*   @brief Defines patch category: service_pack
*   @brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_PATCH_CATEGORY_SERVICE_PACK L"service_pack"

/**
*   @brief Defines patch category: unknown
*   @brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_PATCH_CATEGORY_UNKNOWN L"unknown"

/**
*	@brief Defines a key for wildcard in JSON
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
**/
#define WA_VMOD_KEY_WILDCARD_CHARACTER L"*"

/**
*	@brief Defines root package
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_ROOT_PACKAGE L"root_package"

/**
*	@brief Defines the name of the database
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_DATABASE_NAME L"database_name"

/**
*	@brief Defines the type of the database
*	@brief Represents a JSON number type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_DATABASE_TYPE L"database_type"

/**
*	@brief Defines the well-known name of the file
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_WELLKNOWN_NAME L"wellknown_name"

/**
*	@brief Defines the filename
*	@brief Represents a JSON string type
*	@ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_FILENAME L"filename"

/**
 * @brief Defines the specific data files
 * @brief Represents a JSON number type
 * @ingroup wa_vmod_json_keys
*/
#define WA_VMOD_KEY_DATA_FILES L"data_files"
/**
*	@brief Defines a key for loaded files in JSON
*	@brief Represents a JSON Array type
*	@ingroup wa_vmod_json_keys
**/
#define WA_VMOD_KEY_LOADED_FILES L"loaded_files"