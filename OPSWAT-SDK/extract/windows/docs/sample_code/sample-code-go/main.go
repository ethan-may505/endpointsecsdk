package main

import (
	"encoding/json"
	"fmt"
	"runtime"

	"sample_code/mdes_sdk"
)

const (
	SHARED_OBJECT_NAME string = "libwaapi"
)

var (
	sdk mdes_sdk.MdesSDK
)

type DetectedProductsResult struct {
	Result struct {
		DetectedProducts []struct {
			Categories []int `json:"categories"`
			Vendor     struct {
				Name string `json:"name"`
				ID   int    `json:"id"`
			} `json:"vendor"`
			Signature int `json:"signature"`
			Product   struct {
				Name string `json:"name"`
				ID   int    `json:"id"`
			} `json:"product"`
			SigName string `json:"sig_name"`
		} `json:"detected_products"`
	} `json:"result"`
}

type GetVersionResult struct {
	Result struct {
		Timing   int `json:"timing"`
		Language struct {
			Name string `json:"name"`
			Code string `json:"code"`
		} `json:"language"`
		Version      string `json:"version"`
		Architecture struct {
			Name    string `json:"name"`
			Bitness int    `json:"bitness"`
		} `json:"architecture"`
		Method    int    `json:"method"`
		Code      int    `json:"code"`
		Timestamp string `json:"timestamp"`
		Signature int    `json:"signature"`
	} `json:"result"`
}

func detectProduct() (int32, string) {
	jsonIn := `
	{
		"input": {
			"method": 0
		}
	}
	`

	rc, jsonOut := sdk.Invoke(jsonIn)
	return rc, jsonOut
}

func getVersion(sigId int) (int32, string) {
	jsonIn := fmt.Sprintf(`
	{
		"input": {
			"method": 100,
			"signature": %d
		}
	}
	`, sigId)
	var jsonOut string
	rc, jsonOut := sdk.Invoke(jsonIn)
	return rc, jsonOut
}

func main() {
	var sharedObjectPath string = ""
	os := runtime.GOOS
	switch os {
	case "darwin":
		sharedObjectPath = "./" + SHARED_OBJECT_NAME + ".dylib"
	case "linux":
		sharedObjectPath = "./" + SHARED_OBJECT_NAME + ".so"
	case "windows":
		sharedObjectPath = "./" + SHARED_OBJECT_NAME + ".dll"
	default:
		panic("Do not define platform")
	}

	isLoaded := sdk.Load(sharedObjectPath)
	if !isLoaded {
		panic("Failed to load SDK")
	}
	defer sdk.Unload()
	config := `
	{
		"config": {
		"enable_pretty_print": true,
		"passkey_string" : "passkey_string",
		"caching": false
		}
	}
	`
	if rc, _ := sdk.Setup(config); rc < 0 {
		panic("Setup OESIS is failed")
	}
	defer sdk.Teardown()

	rc, jsonOut := detectProduct()
	if rc < 0 {
		panic("Detect Product is failed")
	}
	var detectedProducts DetectedProductsResult
	err := json.Unmarshal([]byte(jsonOut), &detectedProducts)
	if err != nil {
		panic(err)
	}

	//Get Version for each Product
	fmt.Println("Detected products: ")
	for _, e := range detectedProducts.Result.DetectedProducts {
		fmt.Println("============================")
		rc, jsonOut = getVersion(e.Signature)
		if rc < 0 {
			continue
		}
		var versionResult GetVersionResult
		err := json.Unmarshal([]byte(jsonOut), &versionResult)
		if err != nil {
			panic(err)
		}

		fmt.Println("Sinature: ", e.SigName)
		fmt.Println("Version: ", versionResult.Result.Version)
	}
}
