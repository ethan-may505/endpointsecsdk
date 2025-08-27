if( !tipuesearch ) { var tipuesearch = {"pages": [] }; }

tipuesearch.pages.push( {
    "title" : "Configuration <i class='icon-chevron-right grey'></i> Pretty print JSON",
    "text" : "Configuration key for enabling/disabling pretty printing of JSON output returned in json_out from WANetCall invocations.  Pretty print of JSON output with insert newlines and indentations of size 4.To enable pretty printing, pass this key with value true. The default value is false.  Pretty printing the JSON output can be useful for debugging when you want to dump the structure to view it prior to parsing. All JSON parsers should be able to handle both formats.",
    "tags" : "configuration configurations WANET_CONFIG_PRETTY_PRINT",
    "internal_loc" : "API / Configurations",
    "loc" : "c_api.html#WANET_CONFIG_PRETTY_PRINT"
} );
tipuesearch.pages.push( {
    "title" : "Configuration <i class='icon-chevron-right grey'></i> Component Object Model (COM) concurrency model",
    "text" : "Configuration key for enabling/disabling COM concurrency model. Windows only.  Allows you to determine the COM concurrency model between multi-threaded and apartment-threaded. Set to false if you wish to use apartment-threading model, true to to use multi-threaded model. The default is true (multi-threaded model)",
    "tags" : "configuration configurations WANET_CONFIG_COM_MULTITHREADED",
    "internal_loc" : "API / Configurations",
    "loc" : "c_api.html#WANET_CONFIG_COM_MULTITHREADED"
} );
tipuesearch.pages.push( {
    "title" : "Configuration <i class='icon-chevron-right grey'></i> In-memory database storage",
    "text" : "Configuration key for enabling/disabling in-memory databases.  WANet uses internal databases that exist on disk with the deployment. By default, we will fetch from disk each time access is needed to the data held in the database. Set to true, if you wish to hold the entire database in memory, rather than on disk. In-memory databases can have faster query times, however, the process memory will increase, and vise-versa for on-disk databases. Default is false.",
    "tags" : "configuration configurations WANET_CONFIG_INMEMORY_DATABASE",
    "internal_loc" : "API / Configurations",
    "loc" : "c_api.html#WANET_CONFIG_INMEMORY_DATABASE"
} );
tipuesearch.pages.push( {
    "title" : "Configuration <i class='icon-chevron-right grey'></i> Database location",
    "text" : "Configuration key to set the location of the database.   Allows you to specific the location of the database in your deployment. By default, the database will be read from the directory of your WANet deployment.",
    "tags" : "configuration configurations WANET_CONFIG_DATABASE_LOCATION",
    "internal_loc" : "API / Configurations",
    "loc" : "c_api.html#WANET_CONFIG_DATABASE_LOCATION"
} );
tipuesearch.pages.push( {
    "title" : "Configuration <i class='icon-chevron-right grey'></i> Caching",
    "text" : "Configuration key for enabling/disabling on-the-fly caching. During runtime, we will internally cache information that is constantly fetched in order to speed up function calls. On deinitialization, the in-memory cache will be dumped to disk in the specified location. On the first time cache is accessed, it will be reloaded from the cache location. Turning cache off will result in slower function calls.",
    "tags" : "configuration configurations WANET_CONFIG_CACHE",
    "internal_loc" : "API / Configurations",
    "loc" : "c_api.html#WANET_CONFIG_CACHE"
} );
tipuesearch.pages.push( {
    "title" : "Configuration <i class='icon-chevron-right grey'></i> Cache location",
    "text" : "Configuration key to set the location where cache should be persistently stored. The directory path that is provided must exist on disk.",
    "tags" : "configuration configurations WANET_CONFIG_CACHE_LOCATION",
    "internal_loc" : "API / Configurations",
    "loc" : "c_api.html#WANET_CONFIG_CACHE_LOCATION"
} );
