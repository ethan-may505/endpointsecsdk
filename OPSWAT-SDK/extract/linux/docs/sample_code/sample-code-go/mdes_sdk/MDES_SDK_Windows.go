//go:build COMPILE_FOR_WINDOWS
// +build COMPILE_FOR_WINDOWS

package mdes_sdk

import (
	"syscall"
	"unsafe"
)

const (
	MSG_SDK_HAS_NOT_LOADED = "SDK has not loaded yet"
)

type MdesSDK struct {
	handle             syscall.Handle
	setupFunctionPtr   uintptr
	invokeFunctionPtr  uintptr
	freeFunctionPtr    uintptr
	teadownFunctionPtr uintptr
	isLoaded           bool
}

func (MdesSDK) wcharPtrToString(output_ptr uintptr) string {
	clonePtr := output_ptr
	var str string
	for {
		wchar := *(*uint16)(unsafe.Pointer(clonePtr))
		if wchar == 0 {
			break
		}
		// Convert wchar_t to a Go rune (wide character)
		runeVal := rune(wchar)
		str += string(runeVal)
		clonePtr += unsafe.Sizeof(uint16(0)) // Move to the next character
	}

	return str
}

func (sdk MdesSDK) Setup(json_config string) (rc int32, json_out string) {
	if !sdk.isLoaded {
		panic(MSG_SDK_HAS_NOT_LOADED)
	}
	var jsonOut uintptr
	wcsJsonIn, err := syscall.UTF16PtrFromString(json_config)
	if err != nil {
		panic(err)
	}
	r1, _, _ := syscall.SyscallN(sdk.setupFunctionPtr, uintptr(unsafe.Pointer(wcsJsonIn)), uintptr(unsafe.Pointer(&jsonOut)))
	defer sdk.free(jsonOut)
	rc = int32(r1)
	json_out = sdk.wcharPtrToString(jsonOut)
	return
}

func (sdk MdesSDK) Invoke(json_in string) (rc int32, json_out string) {
	if !sdk.isLoaded {
		panic(MSG_SDK_HAS_NOT_LOADED)
	}
	var jsonOut uintptr

	wcsJsonIn, err := syscall.UTF16PtrFromString(json_in)
	if err != nil {
		panic(err)
	}
	r1, _, _ := syscall.SyscallN(sdk.invokeFunctionPtr, uintptr(unsafe.Pointer(wcsJsonIn)), uintptr(unsafe.Pointer(&jsonOut)))
	defer sdk.free(jsonOut)
	rc = int32(r1)
	json_out = sdk.wcharPtrToString(jsonOut)
	return
}

func (sdk MdesSDK) free(json_data uintptr) (rc int32) {
	if !sdk.isLoaded {
		panic(MSG_SDK_HAS_NOT_LOADED)
	}
	r1, _, errno := syscall.SyscallN(sdk.freeFunctionPtr, uintptr(unsafe.Pointer(json_data)))
	if errno != syscall.Errno(0) {
		panic(errno)
	}
	rc = int32(r1)
	return
}

func (sdk MdesSDK) Teardown() (rc int32) {
	if !sdk.isLoaded {
		panic(MSG_SDK_HAS_NOT_LOADED)
	}
	r1, _, _ := syscall.SyscallN(sdk.teadownFunctionPtr)
	rc = int32(r1)
	return
}

func (sdk *MdesSDK) Load(lib_path string) bool {
	var err error
	sdk.handle, err = syscall.LoadLibrary(lib_path)
	if err != nil {
		panic(err)
	}
	sdk.setupFunctionPtr, err = syscall.GetProcAddress(sdk.handle, "wa_api_setup")
	if err != nil {
		return false
	}
	sdk.invokeFunctionPtr, err = syscall.GetProcAddress(sdk.handle, "wa_api_invoke")
	if err != nil {
		return false
	}
	sdk.freeFunctionPtr, err = syscall.GetProcAddress(sdk.handle, "wa_api_free")
	if err != nil {
		return false
	}
	sdk.teadownFunctionPtr, err = syscall.GetProcAddress(sdk.handle, "wa_api_teardown")
	sdk.isLoaded = err == nil
	return sdk.isLoaded
}

func (sdk *MdesSDK) Unload() {
	if syscall.FreeLibrary(sdk.handle) == nil {
		sdk.isLoaded = false
	}
}
