if( !tipuesearch ) { var tipuesearch = {"pages": [] }; }

tipuesearch.pages.push( {
    "title" : "Component method <i class='icon-chevron-right grey'></i> Common <i class='icon-chevron-right grey'></i> GetProductVersion",
    "text" : "Will retrieve the version of the product. The product version returned will be as close to the version presented on the product's user interface. In some cases we are unable to determine the very minor versions of a product, in which case they will be omitted. If we are unable to determine the version of the product we will return L\"0.0\".",
    "tags" : "",
    "internal_loc" : "API / Component methods / Common",
    "loc" : "c_mid_common.html#get-version"
} );
tipuesearch.pages.push( {
    "title" : "Component method <i class='icon-chevron-right grey'></i> Common <i class='icon-chevron-right grey'></i> IsProductRunning",
    "text" : "Will check if the given product is running on the endpoint. The running state of the product does not refer to the products capabilities (such as an antivirus product's real-time protection). The running state simply refers to whether the product's process is running or active on the endpoint.",
    "tags" : "",
    "internal_loc" : "API / Component methods / Common",
    "loc" : "c_mid_common.html#is-running"
} );
tipuesearch.pages.push( {
    "title" : "Component method <i class='icon-chevron-right grey'></i> Common <i class='icon-chevron-right grey'></i> LaunchProduct",
    "text" : "Will launch the given product on the endpoint. This is the action is the same as if the user launched the product on the endpoint. In most cases, this will launch the product's user interface (if applicable) on the endpoint.",
    "tags" : "activate start",
    "internal_loc" : "API / Component methods / Common",
    "loc" : "c_mid_common.html#launch"
} );
tipuesearch.pages.push( {
    "title" : "Component method <i class='icon-chevron-right grey'></i> Common <i class='icon-chevron-right grey'></i> TerminateProduct",
    "text" : "Will terminate the given product on the endpoint. Permissions to terminate the product must exist otherwise a termination will not be possible.",
    "tags" : "kill",
    "internal_loc" : "API / Component methods / Common",
    "loc" : "c_mid_common.html#terminate"
} );
tipuesearch.pages.push( {
    "title" : "Component method <i class='icon-chevron-right grey'></i> Common <i class='icon-chevron-right grey'></i> GetProductRunningDir",
    "text" : "Will retrieve the main directory path in which the product is running from. The path will always end with the system file separator.",
    "tags" : "",
    "internal_loc" : "API / Component methods / Common",
    "loc" : "c_mid_common.html#get-running-dir"
} );