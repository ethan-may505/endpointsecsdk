//go:build COMPILE_FOR_UNIX
// +build COMPILE_FOR_UNIX

package mdes_sdk

/*
#cgo LDFLAGS: -ldl -lstdc++
#include <stdlib.h>
#include <dlfcn.h>
#include <wchar.h>


typedef int (*WAAPI_SETUP)( const wchar_t *, wchar_t ** );
typedef int (*WAAPI_INVOKE)( const wchar_t *, wchar_t ** );
typedef int (*WAAPI_FREE) ( wchar_t* );
typedef int (*WAAPI_TEARDOWN) ();

// pointer to V4 exported functions
WAAPI_SETUP	v4_setup = NULL; // wa_api_setup
WAAPI_INVOKE	v4_invoke = NULL; // wa_api_invoke
WAAPI_FREE	v4_free = NULL; // wa_api_free
WAAPI_TEARDOWN	v4_teardown = NULL; // wa_api_teardown

// handle used to store the loaded shared library
void* v4_handle = NULL;

void unloadSDK()
{
	if( v4_handle )
	{
		dlclose( v4_handle );
		v4_handle = NULL;
	}

	v4_setup = NULL;
	v4_invoke = NULL;
	v4_free = NULL;
	v4_teardown = NULL;

}

int loadSDK(const char* lib_path)
{
	// Load the OESIS binaries and setup function pointers
	v4_handle = (void*)dlopen(lib_path, RTLD_NOW);

	if(v4_handle)
	{
		// Assign function pointers
		v4_setup	= (WAAPI_SETUP)		dlsym(v4_handle, "wa_api_setup");
		v4_invoke	= (WAAPI_INVOKE)	dlsym(v4_handle, "wa_api_invoke");
		v4_free		= (WAAPI_FREE)		dlsym(v4_handle, "wa_api_free");
		v4_teardown 	= (WAAPI_TEARDOWN)	dlsym(v4_handle, "wa_api_teardown");

		if(!v4_setup || !v4_invoke || !v4_free || !v4_teardown)
			return 0;
	}
	else
	{
		return 0;
	}
	return 1;
}

int wa_api_setup( const wchar_t * json_config , wchar_t ** json_out) {
    return v4_setup(json_config, json_out);
}

int wa_api_invoke( const wchar_t * json_in , wchar_t ** json_out) {
    return v4_invoke(json_in,json_out);
}

int wa_api_free( wchar_t * json_data   ) {
    return v4_free( json_data );
}

int wa_api_teardown() {
    return v4_teardown();
}
*/
import "C"
import (
	"unsafe"
)

const (
	MSG_SDK_HAS_NOT_LOADED = "SDK has not loaded yet"
)

type MdesSDK struct {
	isLoaded bool
}

func (MdesSDK) stringToWcharPtr(str string) (*C.wchar_t, error) {
	strLen := len(str)
	wcharArr := make([]C.wchar_t, strLen+1) // Allocate space for characters + null terminator

	for i := range str {
		wcharArr[i] = C.wchar_t(str[i]) // Convert each rune to wchar_t
	}
	wcharArr[strLen] = 0 // Add null terminator

	// No need for C.malloc or C.free as wcharArr is a Go slice

	return &wcharArr[0], nil
}

func (MdesSDK) wcharPtrToString(wchar_ptr *C.wchar_t) string {
	var runes []rune
	for ptr := uintptr(unsafe.Pointer(wchar_ptr)); *(*uint16)(unsafe.Pointer(ptr)) != 0; ptr += unsafe.Sizeof(*wchar_ptr) {
		runes = append(runes, rune(*(*uint16)(unsafe.Pointer(ptr))))
	}
	return string(runes)
}

func (sdk *MdesSDK) Load(lib_path string) bool {
	csLibPath := C.CString(lib_path)
	defer C.free(unsafe.Pointer(csLibPath))
	sdk.isLoaded = (int(C.loadSDK(csLibPath)) != 0)
	return sdk.isLoaded
}

func (sdk *MdesSDK) Unload() {
	C.unloadSDK()
	sdk.isLoaded = false
}

func (sdk MdesSDK) Setup(json_config string) (rc int32, json_out string) {
	if !sdk.isLoaded {
		panic(MSG_SDK_HAS_NOT_LOADED)
	}
	wcsJsonIn, err := sdk.stringToWcharPtr(json_config)
	if err != nil {
		panic(err)
	}

	var wcsJsonOut *C.wchar_t
	rc = int32(C.wa_api_setup(wcsJsonIn, &wcsJsonOut))
	defer C.wa_api_free(wcsJsonOut)
	json_out = sdk.wcharPtrToString(wcsJsonOut)
	return
}

func (sdk MdesSDK) Invoke(json_config string) (rc int32, json_out string) {
	if !sdk.isLoaded {
		panic(MSG_SDK_HAS_NOT_LOADED)
	}
	wcsJsonIn, err := sdk.stringToWcharPtr(json_config)
	if err != nil {
		panic(err)
	}

	var wcsJsonOut *C.wchar_t
	rc = int32(C.wa_api_invoke(wcsJsonIn, &wcsJsonOut))
	defer C.wa_api_free(wcsJsonOut)
	json_out = sdk.wcharPtrToString(wcsJsonOut)
	return
}

func (sdk MdesSDK) Teardown() (rc int32) {
	if !sdk.isLoaded {
		panic(MSG_SDK_HAS_NOT_LOADED)
	}
	rc = int32(C.wa_api_teardown())
	return
}
