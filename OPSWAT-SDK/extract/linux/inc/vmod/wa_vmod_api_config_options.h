#pragma once
/**
 *	@file wa_vmod_api_config_options.h
 *	@brief Defines our configuration option keys and their purpose
 *
 *	@defgroup wavmod_configuration Configurations
 *	@brief Defines our configuration option keys and their purpose
 */

/**
 *	@brief Configuration key for enabling/disabling pretty printing of JSON output returned in json_out from @ref wa_vmod_api_invoke invocations.
 *  @brief Format: boolean
 *	@ingroup wavmod_configuration
 */
#define WA_VMOD_CONFIG_PRETTY_PRINT L"enable_pretty_print"

/**
 *	@brief Configuration key for setting the location of the RESTful service for queries and updates.
 *  @brief Format: string
 *	@ingroup wavmod_configuration
 */
#define WA_VMOD_CONFIG_SERVER_NAME L"server_name"

/**
 *	@brief Configuration key for setting the location of the HTTP port to use.
 *  @brief Format: number
 *	@ingroup wavmod_configuration
 */
#define WA_VMOD_CONFIG_SERVER_PORT L"server_port"

/**
 *	@brief Configuration key for setting the location of the RESTful licensing service for queries and updates.
 *  @brief Format: string
 *	@ingroup wavmod_configuration
 */
#define WA_VMOD_CONFIG_LICENSE_SERVER_NAME L"license_server_name"

/**
 *	@brief Configuration key for setting the location of the HTTP port to use.
 *  @brief Format: number
 *	@ingroup wavmod_configuration
 */
#define WA_VMOD_CONFIG_LICENSE_SERVER_PORT L"license_server_port"

 /**
 *	@brief Configuration key for setting the HTTP timeout in seconds.
 *  @brief Format: number
 *	@ingroup wavmod_configuration
 */
#define WA_VMOD_CONFIG_SERVER_TIMEOUT L"server_timeout"

/**
 *	@brief Configuration key for enabling/disabling in memory caching for queries.
 *  @brief Format: boolean
 *	@ingroup wavmod_configuration
 */
#define WA_VMOD_CONFIG_CACHING L"caching"

/**
 *	@brief Configuration key for setting the cache lifetime for cache, in seconds. Elements in the cache that exceed this
 *		lifetime will be removed.
 *  @brief Format: number
 *	@ingroup wavmod_configuration
 */
#define WA_VMOD_CONFIG_CACHE_LIFETIME L"cache_lifetime"

/**
 *	@brief Configuration key for setting the soft cache lifetime, in seconds. This determines when the cache is
 *		considered old, but is still allowed to be used.
 *  @brief Format: number
 *	@ingroup wavmod_configuration
 */
#define WA_VMOD_CONFIG_CACHE_SOFT_LIFETIME L"cache_soft_lifetime"

/**
 *	@brief Configuration key for setting the definition cache item lifetime, in seconds. Elements in the cache that exceed this
 *		lifetime will be removed.
 *  @brief Format: number
 *	@ingroup wavmod_configuration
 */
#define WA_VMOD_CONFIG_CACHE_DEF_LIFETIME L"cache_def_lifetime"

/**
 *	@brief Configuration key for setting the soft cache lifetime for definition item, in seconds. This determines when the definition item is
 *		considered old, but is still allowed to be used.
 *  @brief Format: number
 *	@ingroup wavmod_configuration
 */
#define WA_VMOD_CONFIG_CACHE_DEF_SOFT_LIFETIME L"cache_def_soft_lifetime"

/**
 *	@brief Configuration key for the language of error code descriptions.
 *  @brief Format: string
 *	@ingroup wavmod_configuration
 */
#define WA_VMOD_CONFIG_LANGUAGE L"language"

/**
 *	@brief Configuration key for the selected history (see document)
 *  @brief Format: number
 *	@ingroup wavmod_configuration
 */
#define WA_VMOD_CONFIG_HIST_LIMIT L"hist_limit"

/**
 *	@brief Configuration key to set the location of the database
 *	@ingroup wavmod_configuration
 */
#define WA_VMOD_CONFIG_DATABASE_LOCATION L"database_location"

/**
 *	@brief Configuration key for license string
 *	@ingroup wavmod_configuration
 */
#define WA_VMOD_CONFIG_LICENSE_KEY L"license_string"

/**
 *	@brief Configuration key for passkey string
 *	@ingroup wavmod_configuration
 */
#define WA_VMOD_CONFIG_PASSKEY_KEY L"passkey_string"

/**
 *	@brief Configuration key for license file location
 *	@ingroup wavmod_configuration
 */
#define WA_VMOD_CONFIG_LICENSE_LOCATION L"license_location"

/**
 *	@brief Configuration key for URI prefix
 *	@ingroup wavmod_configuration
 */
#define WA_VMOD_CONFIG_URI_PREFIX L"uri_prefix"

/**
 *	@brief Configuration key for web proxy type
 *	@ingroup wavmod_configuration
 */
#define WA_VMOD_CONFIG_PROXY_TYPE L"proxy_type"

/**
 *	@brief Configuration key for web proxy name
 *	@ingroup wavmod_configuration
 */
#define WA_VMOD_CONFIG_PROXY_NAME L"proxy_name"

/**
 *	@brief Configuration key for web proxy port
 *	@ingroup wavmod_configuration
 */
#define WA_VMOD_CONFIG_PROXY_PORT L"proxy_port"

 /**
  *	@brief Configuration key for web proxy username
  *	@ingroup wavmod_configuration
  */
#define WA_VMOD_CONFIG_PROXY_USER L"vmod_proxy_username"

  /**
   *	@brief Configuration key for web proxy password
   *	@ingroup wavmod_configuration
   */
#define WA_VMOD_CONFIG_PROXY_PASSWORD L"vmod_proxy_password"

/**
 * @brief Configuration key for VMod's online database URI
 * @ingroup wavmod_configuration
 */
#define WA_VMOD_CONFIG_ONLINE_DATABASE_URI L"online_database_uri"

 /**
  * @brief Configuration key for VMod's online secure protocols
  * @ingroup wavmod_configuration
  */
#define WA_VMOD_CONFIG_OPTION_SECURE_PROTOCOL L"secure_protocol"

 /**
 * @brief Configuration key for VMod's online custom header for url
 * @ingroup wavmod_configuration
 */
#define WA_VMOD_CONFIG_ONLINE_CUSTOM_HEADER L"online_custom_header"

 /**
  * @brief Configuration key for VMod's online miss expired time
  * @ingroup wavmod_configuration
 */
#define WA_VMOD_CONFIG_ONLINE_MISS_EXPIRED_TIME L"online_miss_expired_time"

 /**
  * @brief Configuration key for VMod's online hit expired time
  * @ingroup wavmod_configuration
 */
#define WA_VMOD_CONFIG_ONLINE_HIT_EXPIRED_TIME L"online_hit_expired_time"