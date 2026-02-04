function init() {
	setupScroll();
	//setupSearch(); // temp disabled until search is updated and automated
	prettyPrint();
}

/**
 *	Handles setting up scroll click and view stuff that bootstrap doesnt handle, call in <body onload="">
 * 	Taken and modified from:
 *  http://stackoverflow.com/questions/11909474/why-isnt-bootstraps-scrollspy-working
 */
function setupScroll() {
	var offset = $("#navContainer").outerHeight(true) + $(".strip").outerHeight(true) + 1, // offset distance below the navContainer with border compensation
		$htmlbody = $('html, body');

	// nav scrolls
	$(function(){
		var $topMenu = $(".nav-scroll"),
			$menuItems = $topMenu.find("a");
		/*
			$scrollItems = $menuItems.map(function() {
				var $item = $($(this).attr("href"));
				if($item.length)
					return $item;
			});
		 */

		$menuItems.click( function(e) {
			e.preventDefault();
		    var href = $(this).attr("href"),
		        offsetTop = href === "#" ? 0 : $(href).offset().top - offset;
		    $htmlbody.stop().animate({
		        scrollTop: offsetTop
		    }, 300);
		});
	});

	// handle scrolls needed for locations outside of current page
	var jump = function(e) {
		if( !e )
		{
			var target = location.hash;
			$htmlbody.animate(
				{ scrollTop: $(target).offset().top - offset },
				0,
				function() { location.hash = target; }
			);
		}
	};

	$htmlbody.hide();

	$(function()
	{
	    $('a[href^="#"]').bind("click", jump);

	    if(location.hash)
		{
	        setTimeout(function() {
	            $htmlbody.scrollTop(0).show();
	            jump();
	        }, 0);
	    }
		else
		{
	        $htmlbody.show();
	    }
	});
}

/**
 *	Will setup the search functionality and dynamically append search data .js files.
 */
function setupSearch() {

	// must all exist in the "search" directory at the root of the site
	// TODO: add any additional search files here
	var search_scripts = [ 	"auto_configurations_search.js",
							"auto_error_codes_search.js",
							"auto_product_categories_search.js",
							"manual_data_types_search.js",
							"manual_functions_search.js",
							"manual_components_search.js",
							"manual_mid_detect_search.js",
							"manual_mid_common_search.js",
							"manual_mid_remote_search.js"
						 ];


	// append scripts to head
	var head = document.getElementsByTagName('head')[0];
	for(var index in search_scripts){

		// create and append
		var script = document.createElement('script');
		script.type = 'text/javascript';
		script.src =  'search/' + search_scripts[index];

		head.appendChild( script );
	}

	// initializes search mechanism
	$(document).ready(function() {
		 $('#tipue_search_input').tipuesearch({
			'showURL' : true,
			'descriptiveWords' : 50,
			'show' : 4,
			'newWindow' : false
		 });
	});
}

function createComponentDefine( define, value ) {
	document.write( "<p>The component method definition:</p>" );
	document.write( "<pre class='prettyprint c'><code> #define " + define + " " + value  +"</code></pre>" );
}

/**
 * Creates the component supported table for component methods
 * @param {boolean} deployment true if supports deployment component, false otherwise
 * @param {boolean} local true if supports local component, false otherwise
 * @param {boolean} remote true if supports remote component, false otherwise
 */
function createComponentSupportTable( deployment, local, remote ) {
	document.write( "<p>Supports: " );

	if( deployment ) {
		document.write( "<span class='label label-info'><a class='white' href='c_api.html#WANET_CID_SELF'>Deployment <i class='icon-ok'></i></a></span>&nbsp;" );
	}
	if( local ) {
		document.write( "<span class='label label-info'><a class='white' href='c_api.html#WANET_CID_LOCAL'>Local <i class='icon-ok'></i></a></span>&nbsp;" );
	}
	if( remote ) {
		document.write( "<span class='label label-info'><a class='white' href='c_api.html#WANET_CID_REMOTE'>Remote <i class='icon-ok'></i></a></span>&nbsp;" );
	}
	document.write( "</p>" );
}

// FV-17311 : Add Responsive tables to make them scroll horizontally on small devices (under 768px).
// When viewing on anything larger than 768px wide, you will not see any difference in these tables. 
function getJsonTable() {
	return	`<div class="table-responsive">
				<table class='table table-condensed'>
					<thead>
						<tr>
							<th>Key</th>
							<th width='20%'>JSON</th>
							<th width='50%'>Description</th>
						</tr>
					</thead>
					<tbody>`;
};

/**
 * starts a json description table
 */
function startJsonTable() {
	document.write( getJsonTable() );
}

function getJsonRow( key, type, desc ) {
	return	`<tr>
				<td>${key}</td>
				<td>${type}</td>
				<td>${desc}</td>
			</tr>`;
};

/**
 * Will add a entry to the JSON table
 * @param {String} key the key in the json object
 * @param {String} type the type of entry
 * @param {String} desc the description of the key
 */
function addJsonRow( key, type, desc ) {
	document.write( getJsonRow( key, type, desc ) );
}

function getJsonTableEnd(){
	return "</tbody></table></div>";
}

/**
 * Closes a JSON map description table
 */
function endJsonTable(){
	document.write( getJsonTableEnd() );
}

/**
 * Dumps string in code block
 * @param {String} json
 */
function printJson( json ) {
	document.write( "<pre class='prettyprint c'><code>" + json + "</code></pre>" );
}

/**
 * Adds json_in description intro
 */
function addJsonInIntro() {
	document.write( "<p>The <code>json_in</code> parameter must provide the following JSON:</p>" );
}

function getJsonOutIntro() {
	return "<p>The <code>json_out</code> parameter will contain the following JSON result upon successful call:</p>";
}

/**
 * Adds json_out description intro
 */
function addJsonOutIntro() {
	document.write( getJsonOutIntro() );
}

/**
 * A lot of functions have json_in with just method id and signature. Because of this, I added
 * a simple one call to create the HTML for this.
 */
function writeProductIdTable(method) {
	// add JSON intro like all others
	addJsonInIntro();

	var json = " {\n"
			 + "        \"input\" : \n"
			 + "        {\n"
			 + "                \"method\" : " + method + ",\n"
			 + "                \"signature\" : number\n"
			 + "        }\n"
			 + " }";
	printJson( json );

	// add description table
	startJsonTable();
	addJsonRow( "method", "number", "The id of the method being invoked.");
	addJsonRow( "signature", "number", "The signature id of the product returned from the detection call.");
	endJsonTable();
}

function getResultDesc(customDesc = "") {
	// default description
	const defaultDesc = "The results of this function are determined by the <a href='c_return_codes.html#error-codes' target='_blank'>error code</a> returned by the call. If successful, <a href='c_return_codes.html#error-codes' target='_blank'>WAAPI_OK</a> or a <a href='c_return_codes.html#WAAPI_SUCCESS_SPECIAL' target='_blank'>special success code</a> will be returned.";
	if (!customDesc)
		return `<p>${defaultDesc}</p>`;

	return `<p>${defaultDesc}<br>${customDesc}</p>`;
}

function buildNav(activeIndex, language, docSetIndex)
{
    var waapiDocs = ["index.html", "c_sdk.html", "c_method.html", "c_return_codes.html", "c_guide.html", "c_faq.html"];
		var $navContainer = $("<div id='navContainer'></div>"),
		$logo = $("<a target='blank' href='http://www.opswat.com'><img class='logo' src='img/logo.png' /></a>"),
		$navBanner = $("<div class='nav-banner blue-bg'>MetaDefender Endpoint Security SDK <span class='superscript'>V4</span> <span>API Documentation</span></div>"),
		$navTabs = $("<ul class='nav nav-tabs'>"+
				"<li " + (activeIndex == 0 ? "class=active" : "") + "><a href='" + waapiDocs[0] + "'>About</a></li>"+
				"<li " + (activeIndex == 1 ? "class=active" : "") + "><a href='" + waapiDocs[1] + "'>Getting Started</a></li>"+
				"<li " + (activeIndex == 2 ? "class=active" : "") + "><a href='" + waapiDocs[2] + "'>Methods</a></li>"+
				"<li " + (activeIndex == 3 ? "class=active" : "") + "><a href='" + waapiDocs[3] + "'>Return Codes</a></li>"+
				"<li " + (activeIndex == 4 ? "class=active" : "") + "><a href='" + waapiDocs[4] + "'>Guides</a></li>"+
				"<li " + (activeIndex == 5 ? "class=active" : "") + "><a href='" + waapiDocs[5] + "'>FAQ</a></li>"+
			"</ul>");

	$navContainer
		.append($logo)
		.append($navBanner)
		.append($navTabs);

	$('#mainContainer').append($navContainer);
}

/**
 * Creates the DOM representations for method json_in and json_out params.
 * @param {array} params The method params array
 * @return {object} Will return an object with the following keys defined:
 *		json_str - the string representation for the passed in params array
 *		json_rows - the table rows representation for the params array
 */
function constructParamsJson(params)
{
	let jsonStr = "";
	let jsonRows = "";
	const paramLen = params.length;
	const wrapperObj = {};

	for(let j = 0; j < paramLen; j++)
	{
		const param = params[j];
		const type = param.type;
		let ref = wrapperObj;
		// split the key name into namespaces so we can insert the element at the appropriate level
		const namespaces = param.name.split(".");
		const cur = namespaces.pop();
		for(let k = 0; k < namespaces.length; k++)
		{
			const ns = namespaces[k];
			if( !ref.hasOwnProperty(ns) )
				ref[ns] = {};
			ref = ref[ns];
			// if it's an array of objects then we need to add to the first element
			if(ref instanceof Array)
			{
				ref = ref[0];
			}
		}
		// we need to expand out the json for arrays and objects
		if(type === "object")
		{
			ref[cur] = {};
		}
		else if(typeof type === 'string' && type.indexOf("array") === 0)
		{
			const subType = type.substring(6, type.length - 1);
			if(subType !== "object")
				ref[cur] = [subType, "..."];
			else
				ref[cur] = [{}, "..."];
		}
		else
		{
			ref[cur] = param.type;
		}

		if(param.optional)
			param.desc = "(optional) " + param.desc;
		jsonRows += getJsonRow(param.name, param.type, param.desc);
	}

	jsonStr = JSON.stringify(wrapperObj, null, 8)
		.replace(/([\s].*)\"(\w+?)\"([,\n])/gm, "$1$2$3") // strip off quotes on type names
		.replace(/\"(\.\.\.)\"/gm, "$1") // strip off quotes on ellipsis
		.replace(/\{([\s\S\n]+)\}/gm, "$1") // remove outer object braces
		.replace(/(        .+\n)/gm, "        $1"); // add an extra tab to each line
	return {
		json_str: jsonStr,
		json_rows: jsonRows.replace(/array<(.+?)>/gm, "array&lt;$1&gt;") // escape array notation tags
	};
}

function buildMethods()
{
	let $core = $('#collapseCore > .nav-sidebar'),
		$manage = $('#collapseManageability > .nav-sidebar'),
		$removal = $('#collapseRemoval > .nav-sidebar'),
		$device = $('#collapseDeviceInfo > .nav-sidebar'),
		$vcr = $('#collapseVulnerability > .nav-sidebar'),
		$driver = $('#collapseDriver > .nav-sidebar'),
		$diagnostic = $('#collapseDiagnostic > .nav-sidebar'),
		$browser = $('#collapseBrowser > .nav-sidebar'),
		$infection = $('#collapseInfection > .nav-sidebar'),
		// $addon = $('#collapseAddon > .nav-sidebar'),	// no addon category
		$netscan = $('#collapseNetscan > .nav-sidebar'),
		$dlp = $('#collapseDLP > .nav-sidebar'),
		$mobile = $('#collapseMobile > .nav-sidebar'),
		$methods = $('.bottom-container-scroll-area');

	//* OESIS Mobile SDK
	G_METHODS.push(
		//Security
		{"brief":"Will retrieve lockscreen protection status.","friendly_name":"GetLockScreenInfo","id":500,"name":"WaApi.method.id.getLockScreenInfo","out_params":[{"desc":"True if lockscreen is protected by some sort of security.","name":"is_protected","optional":false,"type":"boolean"}],"override_default_in":true,"returns":"An @ref waapi_errorcodes 'error code'"},
		{"brief":"Will retrieve OS related information.","friendly_name":"GetOSInfo","id":501,"name":"WaApi.method.id.getOSInfo","out_params":[{"desc":"Name of the operating system.","name":"os_name","optional":false,"type":"string"},{"desc":"Version of the operating system.","name":"os_version","optional":false,"type":"string"}],"override_default_in":true,"returns":"An @ref waapi_errorcodes 'error code'"},
		{"brief":"Displays information about ad tracking.","friendly_name":"GetAdTracking","id":502,"name":"WaApi.method.id.getAdTracking","out_params":[{"desc":"True if ad tracking has been opted out.","name":"allowed","optional":false,"type":"boolean"}],"override_default_in":true,"returns":"An @ref waapi_errorcodes 'error code'"},
		{"brief":"Will retrieve encryption information.","friendly_name":"GetEncryptionState","id":503,"name":"WaApi.method.id.getEncryptionState","out_params":[{"desc":"True if device is encrypted.","name":"encrypted","optional":false,"type":"boolean"}],"override_default_in":true,"returns":"An @ref waapi_errorcodes 'error code'"},

		//Health
		{"brief":"Will retrieve last system reboot information.","friendly_name":"GetRebootRecency","id":600,"name":"WaApi.method.id.getRebootRecency","out_params":[{"desc":"Unix time of system last reboot.","name":"last_system_reboot","optional":false,"type":"string"}],"override_default_in":true,"returns":"An @ref waapi_errorcodes 'error code'"},
		{"brief":"Will retrieve storage related information.","friendly_name":"GetStorageUsage","id":601,"name":"WaApi.method.id.getStorageUsage","out_params":[{"desc":"Total storage space available on the device.","name":"total_space_mb","optional":false,"type":"number"},{"desc":"Free storage space available on the device.","name":"free_space_mb","optional":false,"type":"number"}],"override_default_in":true,"returns":"An @ref waapi_errorcodes 'error code'"},
		{"brief":"Will retrieve battery related information.","friendly_name":"GetBatteryInfo","id":602,"name":"WaApi.method.id.getBatteryInfo","out_params":[{"desc":"Displays battery level percentage.","name":"percentage","optional":false,"type":"number"},{"desc":"Displays if the device is currently charging.","name":"charging","optional":false,"type":"boolean"}],"override_default_in":true,"returns":"An @ref waapi_errorcodes 'error code'"},
		{"brief":"Will retrieve hardware related information.","friendly_name":"GetHardwarePerformance","id":603,"name":"WaApi.method.id.getHardwarePerformance","out_params":[{"desc":"Displays the number of cores in the CPU.","name":"cpu_cores","optional":false,"type":"number"},{"desc":"Displays the CPU speed in megahertz.","name":"cpu_max_speed_mhz","optional":false,"type":"number"},{"desc":"Displays the CPU model.","name":"cpu_model","optional":false,"type":"string"},{"desc":"Displays the free RAM available to the device.","name":"free_memory_mb","optional":false,"type":"number"},{"desc":"Displays the total RAM available to the device.","name":"total_memory_mb","optional":false,"type":"number"}],"override_default_in":true,"returns":"An @ref waapi_errorcodes 'error code'"}
	);
	//*/

	let len = G_METHODS.length,
		cats = G_CATEGORIES;

	for(let i = 0; i < len; i++)
	{
		const cur = G_METHODS[i];
		const elemId = cur.friendly_name;
		const methodId = cur.id;
		const $section = $(`<section class='function-border' id='${elemId}${methodId}'></section>`);
		const customDesc = cur.hasOwnProperty("custom_returns") ? cur.custom_returns : "";

		const deprecationBadge = cur.deprecated ? "<span class='badge badge-dark'><small>DEPRECATED</small></span>" : "";
		$section.append(`<div class='function-title'><h4>${elemId}</h4><div class='badge-container'>${deprecationBadge}</div></div>`);

		if(methodId >= 1000 && methodId < 2000) // category specific manageability methods
		{
			let catLen = cats.length;
			for(let j = 0; j < catLen; j++)
			{
				let cat = cats[j];
				if(cat.hasOwnProperty("supported_methods"))
				{
					let supported = cat.supported_methods;
					if( !(Object.keys(supported)).length )
					{
						// remove empty to speed up future iterations
						cats.splice(j--, 1);
						catLen--;
					}
					if( supported.hasOwnProperty( methodId.toString() ) )
					{
						$section.append("<span class='label label-info'>" + cat.friendly_name + " <i class='icon-ok'></i></span>");
					}
				}
			}
		}

		$section
			.append("<p>" + cur.brief + "</p>")
			.append("<p>The component method definition:</p>"+
				"<pre class='prettyprint c'><code> #define " + cur.name + " " + methodId  +"</code></pre>")
			.append("<p>The <code>json_in</code> parameter must provide the following JSON:</p>");

		// build json_in args string and table
		var jsonIn = "",
			jsonInTbl = getJsonTable();
		if( !cur.hasOwnProperty('override_default_in') ) // blocks the default input params for certain methods, always true
		{
			jsonIn += "                \"method\" : " + methodId + ",\n"+
					  "                \"signature\" : number";
			jsonInTbl += getJsonRow( "method", "number", "The id of the method being invoked.") +
						 getJsonRow( "signature", "number", "The signature id of the product returned from the detection call.");
		}
		else
		{
			// method is still a default, but EVERYTHING has a method id, so we still add this
			jsonIn += "                \"method\" : " + methodId;
			jsonInTbl += getJsonRow( "method", "number", "The id of the method being invoked.");
		}
		// add any additional input params
		if( cur.hasOwnProperty('in_params') )
		{
			jsonIn += ",";

			var inParams = constructParamsJson(cur.in_params);
			jsonIn += inParams.json_str;
			jsonInTbl += inParams.json_rows;
		}
		else
		{
			jsonIn += "\n";
		}
		jsonInTbl += getJsonTableEnd();

		$section
			.append("<pre class='prettyprint c'><code>"+
					" {\n"+
					"        \"input\" : {\n"+
					jsonIn +
					"        }\n"+
					" }"+
				"</code></pre>")
			.append( jsonInTbl );

		// build json_out args string and table
		var jsonOut = "                \"method\" : " + methodId + ",\n"+
				"                \"code\" : number,\n"+
				"                \"timing\" : number,\n"+
				"                \"timestamp\" : string,";
		var jsonOutTbl = getJsonTable() +
				getJsonRow( "method", "number", "The method that generated this result." ) +
				getJsonRow( "code", "number", "The result code for this method call." ) +
				getJsonRow( "timing", "number", "The measured time for the method call in milliseconds." ) +
				getJsonRow( "timestamp", "string", "The timestamp in seconds of when the call was made." );
		if( cur.hasOwnProperty('out_params') )
		{
			var outParams = constructParamsJson(cur.out_params);
			jsonOut += outParams.json_str;
			jsonOutTbl += outParams.json_rows;
		}
		else
		{
			jsonOut += "\n";
		}
		jsonOutTbl += getJsonTableEnd();

		$section
			.append( getJsonOutIntro() )
			.append("<pre class='prettyprint c'><code>"+
				" {\n"+
				"        \"result\" : {\n"+
				jsonOut +
				"        }\n"+
				" }"+
				"</code></pre>")
			.append( jsonOutTbl )
			.append( getResultDesc(customDesc) );

		if(methodId == 107) // manage labels method gets populated with all possible label options
		{
			$section.append("<th>OPSWAT Defined Labels</th>");
			var labelLen = G_LABELS.length;
			var definedLabels = document.createElement("div");
			definedLabels.style.wordBreak = 'break-word';
			for(var j = 0; j < labelLen; j++)
			{
				var label = G_LABELS[j];
				$(definedLabels).append("<span class='label label-info' style='border-radius: 5px'>" + label + "</span><span>&nbsp;</span>");
			}
			$section.append(definedLabels);
		}

		// add to DOM
		$methods.append($section);

		// build menu element
		var $li = $("<li></li>");
		$li.append("<a href='#" + elemId + methodId + "'>" + elemId + "</a>");

		// add to appropriate menu
		// MAINTAINING ORDER IS IMPORTANT HERE: least to greatest
		if(methodId >= 500 && methodId < 700) //mobile
		{
			$li.addClass('mobile-method');
			$mobile.append($li);
		}
		else if(methodId < 1000) // core
		{
			$li.addClass('core-method');
			$core.append($li);
		}
		else if(methodId < 10000) // manageability
		{
			$li.addClass('manageability-method');
			$manage.append($li);
		}
		else if(methodId < 30000) // WaDriver
		{
			$li.addClass('wadriver-method');
			$driver.append($li);
		}
		else if(methodId < 40000) // DeviceInfo
		{
			$li.addClass('deviceinfo-method');
			$device.append($li);
		}
		else if(methodId < 50000) // removal
		{
			$li.addClass('removal-method');
			$removal.append($li);
		}
		else if(methodId < 60000) // vulnerability
		{
			$li.addClass('vulnerability-method');
			$vcr.append($li);
		}
		else if(methodId < 70000) // diagnostic
		{
			$li.addClass('diagnostic-method');
			$diagnostic.append($li);
		}
		else if(methodId < 80000) // browser
		{
			$li.addClass('browser-method');
			$browser.append($li);
		}
		else if(methodId < 90000) // infection
		{
			$li.addClass('infection-method');
			$infection.append($li);
		}
		else if(methodId < 100000) // netscan
		{
			$li.addClass('netscan-method');
			$netscan.append($li);
		}
		else if(methodId < 110000) // addon
		{
			$li.addClass('core-method');	// Addon methods should still go to Core category
			$core.append($li);
		}
		else if(methodId < 130000) // dlp
		{
			$li.addClass('dlp-method');
			$dlp.append($li);
		}
	}
}

function hiddenFeatureMethods(featureClassList) {
    featureClassList.forEach(function(featureClass) {
        // Hidden sidebar
		$('[data-method="' + featureClass + '"]').parent().addClass('hidden');
        // Hidden section
        $("." + featureClass).each(function() {
            let href = $(this).find('a').attr('href');
			if (href?.startsWith('#')) {
                $("section" + href).addClass('hidden');
            }
        });
    });
}
