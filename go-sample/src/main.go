package main

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wa_api.h"

// CGO wrapper functions
int wa_api_setup_wrapper(const wa_wchar* config_json, wa_wchar** output) {
    return wa_api_setup(config_json, output);
}

int wa_api_invoke_wrapper(const wa_wchar* input, wa_wchar** output) {
    return wa_api_invoke(input, output);
}

int wa_api_teardown_wrapper() {
    return wa_api_teardown();
}

void wa_api_free_wrapper(wa_wchar* ptr) {
    wa_api_free(ptr);
}
*/
import "C"

import (
	"encoding/json"
	"flag"
	"fmt"
	"log"
	"os"
	"path/filepath"
	"strings"
	"unsafe"
)

// LicenseConfig holds the license configuration
type LicenseConfig struct {
	LicenseKey string `json:"license_key"`
	License    string `json:"license"`
}

// stringToWaWChar converts a Go string to a wa_wchar string for C
func stringToWaWChar(str string) *C.wa_wchar {
	cStr := C.CString(str)
	defer C.free(unsafe.Pointer(cStr))
	
	// Calculate length needed for wide string
	length := C.strlen(cStr)
	wstr := (*C.wa_wchar)(C.malloc(C.size_t((length + 1) * C.sizeof_wa_wchar)))
	
	// Convert to wide string (simplified - assumes ASCII input)
	cPtr := cStr
	wPtr := wstr
	for i := 0; i < int(length); i++ {
		*wPtr = C.wa_wchar(*cPtr)
		wPtr = (*C.wa_wchar)(unsafe.Pointer(uintptr(unsafe.Pointer(wPtr)) + C.sizeof_wa_wchar))
		cPtr = (*C.char)(unsafe.Pointer(uintptr(unsafe.Pointer(cPtr)) + 1))
	}
	*wPtr = 0 // null terminator
	
	return wstr
}

// waWCharToString converts a wa_wchar string from C to a Go string
func waWCharToString(wstr *C.wa_wchar) string {
	if wstr == nil {
		return ""
	}
	
	// Calculate length
	length := 0
	ptr := wstr
	for *ptr != 0 {
		length++
		ptr = (*C.wa_wchar)(unsafe.Pointer(uintptr(unsafe.Pointer(ptr)) + C.sizeof_wa_wchar))
	}
	
	// Convert to Go string
	result := make([]byte, length)
	ptr = wstr
	for i := 0; i < length; i++ {
		result[i] = byte(*ptr) // simplified - assumes ASCII output
		ptr = (*C.wa_wchar)(unsafe.Pointer(uintptr(unsafe.Pointer(ptr)) + C.sizeof_wa_wchar))
	}
	
	return string(result)
}

// initializeSDK initializes the WAAPI SDK with the given configuration
func initializeSDK(configJSON string) error {
	configPtr := stringToWaWChar(configJSON)
	defer C.free(unsafe.Pointer(configPtr))
	
	var outputPtr *C.wa_wchar
	
	// Call wa_api_setup
	ret := C.wa_api_setup_wrapper(configPtr, &outputPtr)
	
	// Free output if allocated
	if outputPtr != nil {
		defer C.wa_api_free_wrapper(outputPtr)
	}
	
	if ret != 0 {
		output := waWCharToString(outputPtr)
		if ret == 3 {
			// Code 3 means some components failed but others may work
			return fmt.Errorf("wa_api_setup partial failure (code %d): %s", int(ret), output)
		}
		return fmt.Errorf("wa_api_setup failed with code %d: %s", int(ret), output)
	}
	
	fmt.Printf("SDK initialized successfully\n")
	return nil
}

// detectProducts calls the DetectProducts API
func detectProducts() (string, error) {
	// Create input JSON with DetectProducts method - try different format
	inputJSON := `{"method": "DetectProducts"}`
	input := stringToWaWChar(inputJSON)
	defer C.free(unsafe.Pointer(input))
	
	var outputPtr *C.wa_wchar
	
	// Call wa_api_invoke
	ret := C.wa_api_invoke_wrapper(input, &outputPtr)
	
	// Convert output and free it
	var output string
	if outputPtr != nil {
		output = waWCharToString(outputPtr)
		C.wa_api_free_wrapper(outputPtr)
	}
	
	if ret != 0 {
		return "", fmt.Errorf("DetectProducts failed with code %d: %s", int(ret), output)
	}
	
	return output, nil
}

// teardownSDK cleans up the SDK
func teardownSDK() error {
	ret := C.wa_api_teardown_wrapper()
	if ret != 0 {
		return fmt.Errorf("wa_api_teardown failed with code %d", int(ret))
	}
	
	fmt.Printf("SDK teardown completed\n")
	return nil
}

// loadPasskey reads the passkey from the specified file
func loadPasskey(filepath string) (string, error) {
	data, err := os.ReadFile(filepath)
	if err != nil {
		return "", fmt.Errorf("failed to read passkey file: %v", err)
	}
	return strings.TrimSpace(string(data)), nil
}

// loadLicenseConfig reads and parses the license configuration
func loadLicenseConfig(filepath string) (*LicenseConfig, error) {
	data, err := os.ReadFile(filepath)
	if err != nil {
		return nil, fmt.Errorf("failed to read license config: %v", err)
	}
	
	var config LicenseConfig
	if err := json.Unmarshal(data, &config); err != nil {
		return nil, fmt.Errorf("failed to parse license config: %v", err)
	}
	
	return &config, nil
}

func main() {
	fmt.Println("Starting go-sample application...")
	
	// Define command-line flags
	var (
		licenseDir = flag.String("license-dir", ".", "Directory containing license files")
		debugMode  = flag.Bool("debug", false, "Enable debug mode")
	)
	flag.Parse()
	
	fmt.Printf("License directory: %s\n", *licenseDir)
	fmt.Printf("Debug mode: %t\n", *debugMode)
	
	// Load passkey
	passkeyPath := filepath.Join(*licenseDir, "pass_key.txt")
	fmt.Printf("Reading passkey from: %s\n", passkeyPath)
	passkey, err := loadPasskey(passkeyPath)
	if err != nil {
		log.Fatalf("Failed to load passkey: %v", err)
	}
	fmt.Printf("Passkey loaded successfully (length: %d)\n", len(passkey))
	
	// Load license configuration
	licenseConfigPath := filepath.Join(*licenseDir, "license.cfg")
	fmt.Printf("Reading license config from: %s\n", licenseConfigPath)
	licenseConfig, err := loadLicenseConfig(licenseConfigPath)
	if err != nil {
		log.Fatalf("Failed to load license config: %v", err)
	}
	fmt.Printf("License config loaded successfully (length: %d)\n", len(licenseConfig.License))
	
	// Parse license config
	fmt.Println("License config parsed successfully")
	
	// Create SDK configuration JSON matching C# format
	sdkConfig := map[string]interface{}{
		"config": map[string]interface{}{
			"passkey_string":      passkey,
			"enable_pretty_print": true,
			"online_mode":         true,
			"silent_mode":         true,
		},
	}
	fmt.Printf("entered sdkConfig and finished")
	
	configJSON, err := json.Marshal(sdkConfig)
	if err != nil {
		log.Fatalf("Failed to create config JSON: %v", err)
	}
	
	// Initialize SDK
	err = initializeSDK(string(configJSON))
	if err != nil {
		log.Printf("SDK initialization failed: %v", err)
		log.Printf("Cannot proceed with DetectProducts")
		return
	}
	
	fmt.Printf("SDK initialized successfully\n")
	
	// Ensure cleanup
	defer func() {
		if err := teardownSDK(); err != nil {
			log.Printf("Warning: SDK teardown failed: %v", err)
		}
	}()
	
	// Call DetectProducts
	response, err := detectProducts()
	if err != nil {
		log.Printf("Failed to detect products: %v", err)
		// Don't use Fatalf - let deferred teardown execute
		return
	}
	
	// Print the JSON response
	fmt.Println("DetectProducts Response:")
	fmt.Println(response)
}