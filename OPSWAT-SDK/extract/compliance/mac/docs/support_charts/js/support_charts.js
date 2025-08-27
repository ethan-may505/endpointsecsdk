const CORE_METHOD_TEMPLATE = {
    "manageability": {
        "100": {
            "id": 100,
            "meta_data": {
                "param_support": {
                    "input": {
                        "instance_id": {
                            "_supported": false,
                            "_optional": true
                        }
                    },
                    "output": {
                        "version": {
                            "_supported": true,
                            "_optional": false
                        },
                        "architecture": {
                            "_supported": true,
                            "_optional": false,
                            "name": {
                                "_supported": true,
                                "_optional": false
                            },
                            "bitness": {
                                "_supported": true,
                                "_optional": false
                            }
                        },
                        "language": {
                            "_supported": true,
                            "_optional": false,
                            "code": {
                                "_supported": true,
                                "_optional": false
                            },
                            "name": {
                                "_supported": true,
                                "_optional": false
                            }
                        },
                        "channel": {
                            "_supported": false,
                            "_optional": true
                        },
                        "release": {
                            "_supported": false,
                            "_optional": true
                        }
                    }
                },
                "admin_required": false,
                "notes": ""
            },
            "name": "GetVersion"
        },
        "101": {
            "id": 101,
            "meta_data": {
                "param_support": {
                    "input": {
                        "instance_id": {
                            "_supported": false,
                            "_optional": true
                        }
                    },
                    "output": {
                        "running": {
                            "_supported": true,
                            "_optional": false
                        }
                    }
                },
                "admin_required": false,
                "notes": ""
            },
            "name": "GetRunningState"
        },
        "102": {
            "id": 102,
            "meta_data": {
                "param_support": {
                    "input": {
                        "instance_id": {
                            "_supported": false,
                            "_optional": true
                        }
                    },
                    "output": {}
                },
                "admin_required": false,
                "notes": ""
            },
            "name": "Run"
        },
        "103": {
            "id": 103,
            "meta_data": {
                "param_support": {
                    "input": {
                        "instance_id": {
                            "_supported": false,
                            "_optional": true
                        }
                    },
                    "output": {}
                },
                "admin_required": false,
                "notes": ""
            },
            "name": "TerminateProcesses"
        },
        "104": {
            "id": 104,
            "meta_data": {
                "param_support": {
                    "input": {
                        "instance_id": {
                            "_supported": false,
                            "_optional": true
                        }
                    },
                    "output": {
                        "main": {
                            "_supported": true,
                            "_optional": false
                        },
                        "directories": {
                            "_supported": true,
                            "_optional": false
                        }
                    }
                },
                "admin_required": false,
                "notes": ""
            },
            "name": "GetInstallationDirectories"
        },
        "105": {
            "id": 105,
            "meta_data": {
                "param_support": {
                    "input": {
                        "include_services": {
                            "_supported": false,
                            "_optional": true
                        },
                        "instance_id": {
                            "_supported": false,
                            "_optional": true
                        }
                    },
                    "output": {
                        "components": {
                            "_supported": true,
                            "_optional": false,
                            "path": {
                                "_supported": true,
                                "_optional": false
                            },
                            "version": {
                                "_supported": true,
                                "_optional": false
                            },
                            "description": {
                                "_supported": true,
                                "_optional": false
                            }
                        },
                        "services": {
                            "_supported": false,
                            "_optional": true,
                            "name": {
                                "_supported": true,
                                "_optional": false
                            },
                            "path": {
                                "_supported": true,
                                "_optional": false
                            },
                            "state": {
                                "_supported": true,
                                "_optional": false
                            },
                            "md5": {
                                "_supported": true,
                                "_optional": false
                            }
                        }
                    }
                },
                "admin_required": false,
                "notes": ""
            },
            "name": "GetComponents"
        }
    }
}
// global maps
var G_VENDOR_MAP = {},
	G_METHOD_MAP = {};
	G_LABELS_MAP = {};
let	IS_CORE_DATA_FILLED = false;
let SUPPORT_METHODS_BY_CATEGORIES = [];
let CATEGORIZED_METHOD_IDS = [];
GetComponentMethods();
/**
 * Builds and populates the support chart list, taking into account search filters.
 * @param {Boolean} useFilters true if filters should be used, false will retreive all.
 */
function buildSupportChart(useFilters)
{
	var container = $("#productContainer");
	var list = $('.product-list');

	// reset before reloading
	list.html("");
	// removed pre element created in pretty print tab
	container.children("#pretty_view").remove();

	var filter = $('#searchFilterInput').val();
	if(useFilters && filter.length > 1) // don't start checking until after a couple chars
	{
		$('#sortHeading').text("Product Search: \""+ filter +"\"");
		buildProductsListBySearchFilter(filter);
	}
	else
	{
		var sortTab = $('#modeTabs').children('.active').prop('id');
		if(sortTab === "categoriesTab")
		{
			var crumb = $("<a class='crumb'>Select a Category</a>");
			crumb.click(function() { $('#categoriesTab > a').trigger('click'); });
			$('#sortHeading').html(crumb);

			//the "all" category
			var all = $("<li class='grid-elem grid-box category'>" +
						"<span>ALL</span>" +
						"</li>");
			list.append(all);

			var allCategories = {};
			if(!IS_CORE_DATA_FILLED)
			{
				fillOESISCoreMethodData();
				IS_CORE_DATA_FILLED = true;
			}
			// add each cat from charts
			$.each(SUPPORT_CHARTS.categories, function()
			{
				if( this.name === "ALL" )
				{
					allCategories = this;
				}
				else
				{
					var elem = $("<li class='grid-elem grid-box category'>" +
								"<span>" + this.name + "</span>" +
								"</li>");
					elem.data('json', this);
					$.each( this.products, function( key, value ) {
						allCategories.products[key] = value;
					});
					list.append(elem);
				}
			});
			all.data('json', allCategories);

			connectGridElemListeners();
		}
		else if(sortTab === "vendorsTab")
		{
			var crumb = $("<a class='crumb'>Select a Vendor</a>");
			crumb.click(function() { $('#vendorsTab > a').trigger('click'); });
			$('#sortHeading').html(crumb);

			buildVendorsFromCategories(SUPPORT_CHARTS.categories, G_VENDOR_MAP);
		}
		else if(sortTab === "prettyPrintTab") {
                    // Crumb trail
                    var crumb = $("<a class='crumb'>View in Pretty Print</a>");
                    crumb.click(function() { $('#prettyPrintTab > a').trigger('click'); });
                    $('#sortHeading').html(crumb);

                    var jsView = document.createElement('pre');
                    jsView.innerHTML = 'loading... please wait';
                    container.append(jsView);
                    var pretty_format;

                    function async(fn, callback) {
                        setTimeout(function() {
                            fn();
                            if (callback) {
                                callback();
                            }
                        }, 0);
                    }

                    async(function() {
                        pretty_format = JSON.stringify(SUPPORT_CHARTS, null, 4);
                    }, function () {
                        setTimeout(function () {
                            jsView.id = "pretty_view";
                            jsView.innerHTML = pretty_format;
                        }, 0);
                    });
		}
		else if (sortTab == "labelsTab") {
			var crumb = $("<a class='crumb'>Select a Label</a>");
			crumb.click(function() { $('#labelsTab > a').trigger('click'); });
			$('#sortHeading').html(crumb);

			if(typeof G_LABELS_MAP === 'undefined' || Object.keys(G_LABELS_MAP).length === 0)
			{
				var label_id_map = {};
				if(typeof G_LABELS_MAP !== "object")
					G_LABELS_MAP = {};

				$.each(SUPPORT_CHARTS.categories, function()
				{
					// go through all products in each cat and map vendor => product
					$.each(this.products, function()
					{
						var product = this;

						if (product.hasOwnProperty("labels") && product.labels && product.labels.length > 0) {
							for (var i = 0; i < product.labels.length; i++) {
								var label = product.labels[i];

								if (!G_LABELS_MAP[label])
									G_LABELS_MAP[label] = []

								if (!label_id_map[label])
									label_id_map[label] = []

								if (label_id_map[label].indexOf(product.id) == -1) {
									G_LABELS_MAP[label].push(product);
									label_id_map[label].push(product.id);
								}
							}
						}
					});
				});
			}

			// add each label with reference
			$.each(G_LABELS_MAP, function(k, v)
			{
				var elem = $("<li class='grid-elem grid-box label'>" +
							"<span>" + k + "</span>" +
							"</li>");
				elem.data('json', v);
				list.append(elem);
			});

			connectGridElemListeners();
		}
		else // "methodsTab"
		{
			var crumb = $("<a class='crumb'>Select a Method</a>");
			crumb.click(function() { $('#methodsTab > a').trigger('click'); });
			$('#sortHeading').html(crumb);

			// build map of method to products
			if(typeof G_METHOD_MAP === 'undefined' || Object.keys(G_METHOD_MAP).length === 0)
			{
				var method_id_map = {};
				if(typeof G_METHOD_MAP !== "object")
					G_METHOD_MAP = {};
				$.each(SUPPORT_CHARTS.categories, function()
				{
					// go through all products in each cat and map vendor => product
					$.each(this.products, function()
					{
						var product = this; // so it's available in inner scope
						$.each(this.signatures, function()
						{
							// get the inner k,v pair
							var sig = this;
							if(sig.methods)
								$.each(sig.methods, function(k, module)
								{
									$.each(module, function(k, v){
										// get the inner k,v pair
										var key = v.name;
										// yes that is 4 nested each loops...
										if(!G_METHOD_MAP[key])
											G_METHOD_MAP[key] = [];
										if(!method_id_map[key])
											method_id_map[key] = [];
										if(method_id_map[key].indexOf( product.id ) == -1)
										{
											G_METHOD_MAP[key].push(product);
											method_id_map[key].push(product.id);
										}
									});
								});
						});
					});
				});
			}

			// add each method with reference
			$.each(G_METHOD_MAP, function(k, v)
			{
				var elem = $("<li class='grid-elem grid-box method'>" +
							"<span>" + k + "</span>" +
							"</li>");
				elem.data('json', v);
				list.append(elem);
			});

			connectGridElemListeners();
		}
	}
}

/**
*	Displays a listing sorted by vendor using selected categories and returns a mapping.
*	@param categories A categories map of k=>v categories, or a single category object.
*	@param vendorMap Either an already build vendor mapping to display or an empty object which will
*					hold the new mapping when the function returns.
*/
function buildVendorsFromCategories(categories, vendorMap)
{
	var list = $('.product-list');
	var categories = new Object(categories);
	// reset before reloading
	list.html("");

	// build the vendor mapped set if this is the first time
	if(typeof vendorMap === 'undefined' || Object.keys(vendorMap).length === 0)
	{
		var vendor_id_map = {};
		if(typeof vendorMap !== "object")
			vendorMap = {};
		var tempMap = {};
		// check for single category or multiple
		if(categories.products)
			$.each(categories.products, function()
			{
				for(var did in this.signatures) break;
				var vname = this.signatures[did].vendor.name
				if(!tempMap[vname])
					tempMap[vname] = [];
				tempMap[vname].push(this);
			});
		else
			$.each(categories, function()
			{
				// go through all products in each cat and map vendor => product
				$.each(this.products, function()
				{
					for(var did in this.signatures) break;
					var vname = this.signatures[did].vendor.name
					if(!tempMap[vname])
						tempMap[vname] = [];
					if(!vendor_id_map[vname])
						vendor_id_map[vname] = [];
					//tempMap[this.vendor].push(this);
					if(vendor_id_map[vname].indexOf( this.id ) == -1)
					{
						tempMap[vname].push(this);
						vendor_id_map[vname].push(this.id);
					}
				});
			});

		// sort it into global map
		var keys = Object.keys(tempMap),
			len = keys.length;

		keys.sort(function (a, b) {
			return a.toLowerCase().localeCompare(b.toLowerCase());
		});

		for (var i = 0; i < len; i++)
		{
			var k = keys[i];
			vendorMap[k] = tempMap[k];
		}
	}

	// add each vendor with reference
	$.each(vendorMap, function(k, v)
	{
		var elem = $("<li class='grid-elem grid-box vendor'>" +
					"<span>" + k + "</span>" +
					"</li>");
		elem.data('json', v);
		list.append(elem);
	});

	connectGridElemListeners();
}

/**
*	Displays the list of products with linking.
*	@param products The products array.
*/
function buildProductsList(products)
{
	var list = $('.product-list');

	// reset before reloading
	list.html("");

	// add each product with reference
	$.each(products, function()
	{
		var elem = $("<li class='grid-elem grid-box product'>" +
					"<span>" + this.name + "</span>" +
					"</li>");
		elem.data('json', this);
		list.append(elem);
	});

	connectGridElemListeners();
}

function buildLabelsList(products)
{
	var list = $('.product-list');

	// reset before reloading
	list.html("");

	// add each product with reference
	$.each(products, function()
	{
		var elem = $("<li class='grid-elem grid-box product'>" +
					"<span>" + this.name + "</span>" +
					"</li>");
		elem.data('json', this);
		list.append(elem);
	});

	connectGridElemListeners();
}

/**
*	Displays the list of products with linking using a search string filter.
*	@param filter The string to find products for.
*/
function buildProductsListBySearchFilter(filter)
{
	var list = $('.product-list');

	// reset before reloading
	list.html("");

	filter = filter.toLowerCase();
	var matchesMarketingNames = function(product, filter){
		if(product.hasOwnProperty("marketing_names")){
			for(var i = 0; i < product.marketing_names.length; i++){
				if( product.marketing_names[i].toLowerCase().indexOf(filter) !== -1){
					return true;
				}
			}
		}
		return false;
	};
	var tempMap = {},
		products = {};
	$.each(SUPPORT_CHARTS.categories, function()
	{
		// go through all products in each cat and map vendor => product
		$.each(this.products, function(){
			if(!tempMap[this.name]){
				if( this.name.toLowerCase().indexOf(filter) !== -1
					|| matchesMarketingNames(this, filter)){
					tempMap[this.name] = this;
				}
			}
		});
	});

	// sort it into global map
	var keys = Object.keys(tempMap),
		len = keys.length;

	keys.sort(function (a, b) {
		return a.toLowerCase().localeCompare(b.toLowerCase());
	});

	for (var i = 0; i < len; i++)
	{
		var k = keys[i];
		products[k] = tempMap[k];
	}

	// add each product with reference
	$.each(products, function(k, v)
	{
		var elem = $("<li class='grid-elem grid-box product'>" +
					"<span>" + k + "</span>" +
					"</li>");
		elem.data('json', v);
		list.append(elem);
	});

	connectGridElemListeners();
}

/**
 * Attaches all necessary listners to the grid elements. This must be called after
 * all the elements are drawn.
 */
function connectGridElemListeners()
{
	$('.grid-elem')
		.mouseenter(function()
		{
			$(this).addClass('grid-highlight');
		})
		.mouseleave(function()
		{
			$(this).removeClass('grid-highlight');
		})
		.click(function()
		{
			if( $(this).hasClass('category') )
			{
				var vendorMap = {};
				buildVendorsFromCategories( $(this).data('json'), vendorMap );

				var crumb = $("<a class='crumb'> > Select a Vendor</a>");
				crumb.click(function() {
					buildVendorsFromCategories( null, vendorMap );
					$(this).next('a').remove();
				});
				$('#sortHeading').append(crumb);
			}
			else if ($(this).hasClass('label'))
			{
				$('#sortHeading').append("<a class='crumb'> > Select a Product</a>");
				buildLabelsList( $(this).data('json') );
			}
			else if( !$(this).hasClass('product') )
			{
				$('#sortHeading').append("<a class='crumb'> > Select a Product</a>");
				buildProductsList( $(this).data('json') );
			}
			else // product
			{
				loadProductOverlay( $(this) );
			}
		});
}

function closePopups()
{
	$(".product-list").removeClass("hidden");

	$('#productOverlay')
		.removeClass('expand')
		.html("")
		.unbind();
}

function flattenParse(path, metaData){
	var entries = [];
	if(metaData.hasOwnProperty("_supported")){
		var support = {
			'supported': metaData._supported,
			'key': path
		};
		if(metaData._supported){
			if(metaData.hasOwnProperty("_values")) {
				var values = [];
				for(k in metaData._values ){
					if(metaData._values[k]){
						values.push(k);
					}
				}
				support.values=values.join(', ');
			}
		}
		entries.push(support);
		
		if(metaData._supported){
			for(var param in metaData){
				if(param.lastIndexOf('_', 0) !== 0){
					var children = flattenParse(path +"."+ param, metaData[param]);
					entries = entries.concat(children);
				}
			}
		}
	}

	return entries;
}

function buildParamSupportChart(title, params){
	var entries = [];

	for(var k in params){
		entries = entries.concat(flattenParse(k, params[k]));
	}
	if(entries.length <= 0){
		return "";
	}
	var output = $("<div class='parameters-support'></div>");
	for(k in entries) {
			var entry = entries[k];
			if(entry.supported){
				$entry = $("<div class='param-support-marker-yes'><b>"+entry.key+"</b><br></div>");
			} else {
				$entry = $("<div class='param-support-marker-no'>"+entry.key+"</div>");
			}
			if(entry.hasOwnProperty('values') && entry.values.length > 0){
				$entry.append(" ("+entry.values+")");
			}
			output.append($entry);
	}
	return output;
}



function createLanguageRow(signatureId, languages)
{
	let row = $("<div class='view-table-row'></div>");
	row.append("<p></p>"); // empty first col
	row.append(`<p class='colored' style='max-width: 270px;'>${languages}</p>`);
	row.append(`<p class='colored'>${signatureId}</p>`);
	return row;
}

/**
 * Shows the product overlay for when a product is selected. The overlay will
 * contain the information associated with the product.
 * @param {Object} product The jquery wrapped DOM object for the product.
 *			This would generally be the $(this) in the context of the objects click listener.
 */
function loadProductOverlay(product)
{
	var overlay = $('#productOverlay'),
		container = $("<div class='def-container'></div>"),
		data = product.data('json');

	// set the start position to be the same as the product so it will look like its animating
	// out from the product element
	var pos = product.position();
	overlay.css('left', pos.left+70)
		.css('top', pos.top+70);

	var table = $("<div class='view-table'></div>");

	var prodRow = $("<div class='view-table-row'></div>");
	prodRow.append("<p>Product:</p>");
	prodRow.append("<p>" + data.name + "</p><p>( ID: " + data.id + " )</p>");
	table.append(prodRow);

	for(var did in data.signatures) break;
	var vname = data.signatures[did].vendor.name
	var vid = data.signatures[did].vendor.id
	var vendRow = $("<div class='view-table-row'></div>");
	vendRow.append("<p>Vendor:</p>");
	vendRow.append("<p>" + vname + "</p><p>( ID: " + vid + " )</p>");
	table.append(vendRow);

	table.append("<div class='view-table-row'><p>Tested Points:</p><p style='text-decoration:underline'>Tested Version</p><p style='text-decoration:underline'>Signature</p><p style='text-decoration:underline'>Release Name</p></div>");
	$.each(data.tested_points, function(k, v)
	{
		const release = v.release ?? "";
		var row = $("<div class='view-table-row'></div>");
		row.append("<p></p>"); // empty first col
		row.append("<p class='colored'>" + v.version + "</p>");
		row.append("<p class='colored'>" + v.signature + "</p>");
		row.append("<p class='colored'>" + release + "</p>");
		table.append(row);
	});

	if (data.hasOwnProperty("labels") && data.labels && data.labels.length >0) {
		table.append("<div class='view-table-row'><p>Labels:</p></div>");
		$.each(data.labels, function(k, v) {
			var row = $("<div class='view-table-row'></div>");
			row.append("<p></p>"); // empty first col
			row.append("<p class='colored'>" + v + "</p>");
			table.append(row);
		});
	}

	if(data.hasOwnProperty("marketing_names") && data.marketing_names.length && data.marketing_names.length > 0){
		table.append("<div class='view-table-row'><p>Marketing Names:</p><p style='text-decoration:underline'>Name</p></div>");
		$.each(data.marketing_names, function(k, v)
		{
			var row = $("<div class='view-table-row'></div>");
			row.append("<p></p>"); // empty first col
			row.append("<p class='colored'>" + v + "</p>");
			table.append(row);
		});
	}

	table.append("<div class='view-table-row'><p>Supported Languages:</p><p style='text-decoration:underline'><a href='https://localizely.com/iso-639-1-list/' target='_blank'>ISO 639-1 codes</a></p><p style='text-decoration:underline'>Signature</p></div>");
	
	const defaultLanguage = "EN";
	$.each(data.signatures, function(signatureId)
	{
		if(data.hasOwnProperty("languages") && Array.isArray(data.languages) && data.languages.length > 0)
		{
			const item = data.languages.find((lang) => lang.signature == signatureId);
			if (item)
				table.append(createLanguageRow(signatureId, `${defaultLanguage}, ${item.languages.join(", ")}`));
			else
				table.append(createLanguageRow(signatureId, defaultLanguage));
		}
		else
			table.append(createLanguageRow(signatureId, defaultLanguage));
	});

	let notSupportedCategoryMethodIds = JSON.parse(JSON.stringify(CATEGORIZED_METHOD_IDS)); // deep copy from CATEGORIZED_METHOD_IDS array

	table.append("<div class='view-table-row'>"
		+"<p>Signatures</p>"
		+"<p style='text-decoration:underline'>Sig-name</p>"
		+"<p style='text-decoration:underline'>Signature</p>"
		+"<p style='text-decoration:underline'>Categories</p>");
	
	$.each(data.signatures, function(signatureId, signature)
	{
		const signatureCategories = signature.categories;
		const categoryNames = Object.values(signatureCategories)
								.map(category => category.name)
								.join('<br>');
		var row = $("<div class='view-table-row'></div>");
		row.append("<p></p>"); // empty first col
		row.append("<p class='colored'><b>" + signature.sig_name + "</b></p>");
		row.append("<p class='colored'>" + signatureId + "</p>");
		row.append("<p class='colored'>" + categoryNames + "</p>");
		row.append("<p class='colored'></p>");
		table.append(row);

    	const signatureCategoryIds = Object.keys(signatureCategories);
		
		signatureCategoryIds.forEach((key) => {
			const categoryId = signatureCategories[key].id;
			const category = SUPPORT_METHODS_BY_CATEGORIES.find(
			  (cat) => cat.id === categoryId
			);
	  
			if (category && category.supported_methods && category.supported_methods.length > 0) {
				$.each(category.supported_methods, function(index, methodId){
					notSupportedCategoryMethodIds = notSupportedCategoryMethodIds.filter(function(v) {
						return v !== methodId;
					});
				})
			}
		});

		if(signature.methods)
		{
			var burnedIds = {};
			$.each(signature.methods, function(module, methods)
			{
				$.each(methods, function(methodId, method)
				{
					if(!notSupportedCategoryMethodIds.includes(methodId) && !burnedIds.hasOwnProperty(methodId))
					{
						burnedIds[methodId] = true;

						var $titleBlock = $("<div class='method-title method-cell margin-cell'></div>");
						var $inputTitle = $("<div class='method-title method-cell'></div>");
						var $outputTitle = $("<div class='method-title method-cell'></div>");
						var $descBlock = $("<div class='method-meta method-cell margin-cell'></div>");
						var $inputTarget = $("<div class='method-meta method-cell'></div>");
						var $outputTarget = $("<div class='method-meta method-cell'></div>");

						$titleBlock.append($("<label>"+methodId + ": " + method.name + "</label>"));

						var shouldDisplayMeta = false;

						if(method.hasOwnProperty('code')){
							shouldDisplayMeta = true;
							$descBlock.append("<div class='param-support-marker-no'>Fixed return: "+method.code+"</div>");
						}

						if(method.hasOwnProperty("meta_data")){
							if(method.meta_data.hasOwnProperty("admin_required") && method.meta_data.admin_required){
								shouldDisplayMeta = true;
								$descBlock.append("<p class='admin-required'>admin_required</p>");
							}

							if(method.meta_data.hasOwnProperty("rtm_supported") && method.meta_data.rtm_supported){
								shouldDisplayMeta = true;
								$descBlock.append("<p class='rtm-supported'>realtime_monitoring_supported</p>");
							}
							
							if(method.meta_data.hasOwnProperty("notes") && method.meta_data.notes.length > 0){
								shouldDisplayMeta = true;
								$descBlock.append($("<p></p>").append(method.meta_data.notes));
							}

							if(method.meta_data.hasOwnProperty("param_support")){
								if(method.meta_data.param_support.hasOwnProperty("input")){
									var paramInput = buildParamSupportChart( "input", method.meta_data.param_support.input);
									if(paramInput){
										shouldDisplayMeta = true;
										$inputTarget = $("<div class='parameters-support-cell'></div>");
										$inputTarget.append( paramInput );
										$inputTitle.append($("<p class='parameters-support-label'>optional input support</p>"));
									}
								}

								if(method.meta_data.param_support.hasOwnProperty("output")){
									var paramOutput = buildParamSupportChart( "output", method.meta_data.param_support.output);
									if(paramOutput){
										shouldDisplayMeta = true;
										$outputTarget = $("<div class='parameters-support-cell'></div>");
										$outputTarget.append( paramOutput );
										$outputTitle.append($("<p class='parameters-support-label'>optional output support</p>"));
									}
								}
							}
						}

						var $titleRow = $("<div class='view-table-row'></div>");
						$titleRow.append("<p></p>");
						$titleRow.append($titleBlock);
						$titleRow.append($inputTitle);
						$titleRow.append($outputTitle);
						table.append($titleRow);

						if(shouldDisplayMeta){
						var $metaRow = $("<div class='view-table-row'></div>");
							$metaRow.append("<p></p>");
							$metaRow.append($descBlock);
							$metaRow.append($inputTarget);
							$metaRow.append($outputTarget);
							table.append($metaRow);
						}
					}
				});
			});
		}
	});

	container.append(table);

	var clear = $("<div class='corner-highlight'></div><span class='remove'>X</span>");
	clear.click(function()
	{
		closePopups();
	});

	$(".product-list").addClass("hidden");

	overlay.append(clear)
		.append(container)
		.addClass('expand');

}

function getCreationTime()
{
	var date = new Date(SUPPORT_CHARTS.timestamp * 1000); // to ms
	return date.toString();
}

/**
 * This method fills core methods into SUPPORT_CHARTS with CORE_METHOD_TEMPLATE if no core methods exist.
 * CORE_METHOD_TEMPLATE generated by fv-local-core\builders\python\gen_core_method_template.py
 * Core methods: 
 * 	- GetVersion
 * 	- GetRunningState
 * 	- Run
 * 	- TerminateProcesses
 * 	- GetInstallationDirectories
 * 	- GetComponents
 */
function fillOESISCoreMethodData()
{
	$.each(SUPPORT_CHARTS.categories, function()
	{
		// go through all products in each cat and map vendor => product
		$.each(this.products, function()
		{
			$.each(this.signatures, function()
			{
				let sig = this;
				if(!sig.methods?.hasOwnProperty("manageability"))
					sig.methods["manageability"] = CORE_METHOD_TEMPLATE["manageability"];
				else
				{
					for(const key in CORE_METHOD_TEMPLATE.manageability)
						if(!sig.methods.manageability.hasOwnProperty(key) && !sig.methods.constant?.hasOwnProperty(key))
							sig.methods.manageability[key] = CORE_METHOD_TEMPLATE.manageability[key];
				}
			});
		});
	});
}

function GetComponentMethods() {
	for (const [categoryKey, category] of Object.entries(SUPPORT_CHARTS.categories)) {
		SUPPORT_METHODS_BY_CATEGORIES.push({
			"id": parseInt(categoryKey),
			"supported_methods": Object.values(category.methods).length > 0 ? Object.values(category.methods).map(m => m.id.toString()) : []
		});
		CATEGORIZED_METHOD_IDS = CATEGORIZED_METHOD_IDS.concat(Object.keys(category.methods));
	}
}