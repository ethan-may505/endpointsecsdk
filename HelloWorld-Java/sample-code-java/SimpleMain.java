package sample_code_java;

import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Pointer;
import com.sun.jna.WString;
import com.sun.jna.ptr.PointerByReference;
import org.json.JSONArray;
import org.json.JSONObject;
import java.io.File;
import java.nio.file.Files;
import java.nio.file.Paths;

/**
 * Simple OESIS Framework Demo
 * Load library -> Setup -> Detect products -> Teardown
 */
public class SimpleMain {
    
    // Native library interface
    public interface WaApiLibrary extends Library {
        int wa_api_setup(WString json_config, PointerByReference json_out);
        int wa_api_invoke(WString json_in, PointerByReference json_out);
        int wa_api_teardown();
        int wa_api_free(Pointer json_data);
    }
    
    private static WaApiLibrary library = null;
    
    public static void main(String[] args) {
        System.out.println("=================================================");
        System.out.println("  OESIS Framework - Simple Java Demo");
        System.out.println("=================================================\n");
        
        try {
            // 1. Load library
            System.out.println("[1/4] Loading library...");
            if (!loadLibrary()) {
                System.err.println("Failed to load library");
                return;
            }
            System.out.println("Library loaded successfully\n");
            
            // 2. Setup
            System.out.println("[2/4] Setting up OESIS Framework...");
            if (!setup()) {
                System.err.println("Failed to setup");
                return;
            }
            System.out.println("Setup successful\n");
            
            // 3. Detect products
            System.out.println("[3/4] Detecting products...");
            detectProducts();
            
            // 3.5. Load Patch Database
            System.out.println("\n[3.5/7] Loading patch database...");
            loadPatchDB();

            // 4. Get Latest Installer (with download)
            System.out.println("\n[4/7] Getting and downloading latest installer...");
            int testSignature = 200051;  // Change this to a signature detected on your system
            String downloadDir = System.getProperty("user.home") + File.separator + "oesis_downloads";
            new File(downloadDir).mkdirs();  // Create download directory
            String installerPath = getLatestInstaller(testSignature, 1, downloadDir);

            // 5. Install From Files (to test customer's teardown issue)
            if (installerPath != null && !installerPath.isEmpty()) {
                System.out.println("\n[5/7] Installing from files (testing customer scenario)...");
                installFromFiles(testSignature, installerPath);
            } else {
                System.out.println("\n[5/7] Skipping install from files - no installer downloaded");
                System.out.println("  (This may be because no update is available for signature " + testSignature + ")");
            }

            // 6. Teardown
            System.out.println("\n[6/7] Tearing down...");
            teardown();
            System.out.println("Teardown complete\n");

            System.out.println("=================================================");
            System.out.println("  Demo completed successfully!");
            System.out.println("=================================================");
            
        } catch (Exception e) {
            System.err.println("Error: " + e.getMessage());
            e.printStackTrace();
        }
    }
    
    /**
     * Load the OESIS library
     */
    private static boolean loadLibrary() {
        try {
            library = Native.load("libwaapi", WaApiLibrary.class);
            return true;
        } catch (Exception e) {
            System.err.println("Library load error: " + e.getMessage());
            return false;
        }
    }
    
    /**
     * Setup OESIS Framework
     */
    private static boolean setup() {
        try {
            // Read license.txt file
            String licensePath = "license" + File.separator + "license.txt";
            String licenseContent = new String(Files.readAllBytes(Paths.get(licensePath))).trim();
            
            // Remove "module.exports = " prefix if exists
            if (licenseContent.startsWith("module.exports = ")) {
                licenseContent = licenseContent.substring("module.exports = ".length());
            }
            
            // Parse license.txt to get passkey and license data
            JSONObject licenseData = new JSONObject(licenseContent);
            String passkey = licenseData.getString("passkey");
            JSONObject licenseObj = licenseData.getJSONObject("license");
            String licenseBytes = licenseObj.getString("license");
            String licenseKeyBytes = licenseObj.getString("license_key");
            
            // Escape for JSON
            String escapedPasskey = passkey.replace("\\", "\\\\").replace("\"", "\\\"");
            String escapedLicense = licenseBytes.replace("\\", "\\\\").replace("\"", "\\\"");
            String escapedLicenseKey = licenseKeyBytes.replace("\\", "\\\\").replace("\"", "\\\"");
            
            // Create setup config with license_bytes and license_key_bytes
            String jsonConfig = String.format(
                "{ \"config\" : { \"passkey_string\": \"%s\", \"license_bytes\": \"%s\", \"license_key_bytes\": \"%s\", \"enable_pretty_print\": true } }",
                escapedPasskey, escapedLicense, escapedLicenseKey
            );
            
            // Call setup
            PointerByReference jsonOutRef = new PointerByReference();
            int rc = library.wa_api_setup(new WString(jsonConfig), jsonOutRef);
            
            // Get result
            String jsonOut = "{}";
            Pointer jsonOutPtr = jsonOutRef.getValue();
            if (jsonOutPtr != null) {
                jsonOut = jsonOutPtr.getWideString(0);
                library.wa_api_free(jsonOutPtr);
            }
            
            if (rc != 0) {
                System.err.println("Setup returned code: " + rc);
                System.err.println("Response: " + jsonOut);
                // Code 8 means some optional modules failed, but core is OK - continue anyway
                if (rc > 0) {
                    System.out.println("Warning: Some optional modules failed, but continuing...\n");
                } else {
                    return false;
                }
            }
            
            return true;
            
        } catch (Exception e) {
            System.err.println("Setup error: " + e.getMessage());
            e.printStackTrace();
            return false;
        }
    }
    
    /**
     * Detect products (category = * - all categories)
     */
    private static void detectProducts() {
        try {
            // Create detect request
            String jsonIn = "{ \"input\": { \"method\": 0 } }";
            
            // Call invoke
            PointerByReference jsonOutRef = new PointerByReference();
            int rc = library.wa_api_invoke(new WString(jsonIn), jsonOutRef);
            
            // Get result
            String jsonOut = "{}";
            Pointer jsonOutPtr = jsonOutRef.getValue();
            if (jsonOutPtr != null) {
                jsonOut = jsonOutPtr.getWideString(0);
                library.wa_api_free(jsonOutPtr);
            }
            
            if (rc != 0) {
                System.err.println("Detect failed with code: " + rc);
                System.err.println("Response: " + jsonOut);
                return;
            }
            
            // Print full JSON output
            System.out.println("Detect Result JSON:");
            System.out.println(jsonOut);
            System.out.println();
            
            // Parse and display results
            JSONObject response = new JSONObject(jsonOut);
            if (response.has("result")) {
                JSONObject result = response.getJSONObject("result");
                int code = result.optInt("code", -1);
                
                if (code == 0 && result.has("detected_products")) {
                    JSONArray products = result.getJSONArray("detected_products");
                    
                    System.out.println("Found " + products.length() + " product(s):\n");
                    
                    for (int i = 0; i < products.length(); i++) {
                        JSONObject product = products.getJSONObject(i);
                        System.out.println("Product " + (i + 1) + ":");
                        System.out.println("  Signature ID: " + product.getInt("signature"));
                        System.out.println("  Display Name: " + product.optString("display_name", "N/A"));
                        if (product.has("vendor")) {
                            JSONObject vendor = product.getJSONObject("vendor");
                            System.out.println("  Vendor: " + vendor.optString("name", "N/A"));
                        }
                        System.out.println();
                    }
                } else {
                    System.out.println("Detect failed with code: " + code);
                }
            } else {
                System.out.println("No result found in response");
            }
            
        } catch (Exception e) {
            System.err.println("Detect error: " + e.getMessage());
            e.printStackTrace();
        }
    }
    
    /**
     * Load Patch Database
     */
    private static void loadPatchDB() {
        try {
            // Determine OS and set appropriate patch file path
            String osName = System.getProperty("os.name").toLowerCase();
            String patchFilePath;
            
            if (osName.contains("win")) {
                // Windows: use dll/patch.dat
                patchFilePath = "dll" + File.separator + "patch.dat";
            } else {
                // Linux: use so/patch_linux.dat
                patchFilePath = "so" + File.separator + "patch_linux.dat";
            }
            
            // Get absolute path
            File patchFile = new File(patchFilePath);
            String absolutePath = patchFile.getAbsolutePath().replace("\\", "\\\\");
            
            System.out.println("Loading patch database from: " + absolutePath);
            
            // Create load patch DB request
            String jsonIn = String.format(
                "{ \"input\": { \"method\": 50302, \"dat_input_source_file\": \"%s\" } }",
                absolutePath
            );
            
            // Call invoke
            PointerByReference jsonOutRef = new PointerByReference();
            int rc = library.wa_api_invoke(new WString(jsonIn), jsonOutRef);
            
            // Get result
            String jsonOut = "{}";
            Pointer jsonOutPtr = jsonOutRef.getValue();
            if (jsonOutPtr != null) {
                jsonOut = jsonOutPtr.getWideString(0);
                library.wa_api_free(jsonOutPtr);
            }
            
            if (rc != 0) {
                System.err.println("Load patch DB failed with code: " + rc);
                System.err.println("Response: " + jsonOut);
                return;
            }
            
            System.out.println("Patch database loaded successfully");
            System.out.println("Response: " + jsonOut);
            
        } catch (Exception e) {
            System.err.println("Load patch DB error: " + e.getMessage());
            e.printStackTrace();
        }
    }
    
    /**
     * Get Latest Installer (with optional download)
     * Returns the downloaded file path if download=1, otherwise null
     */
    private static String getLatestInstaller(int signatureID, int download, String downloadPath) {
        try {
            // Create get latest installer request with provided signature
            String jsonIn;
            if (download > 0 && downloadPath != null) {
                String escapedPath = downloadPath.replace("\\", "\\\\");
                jsonIn = String.format(
                    "{ \"input\": { \"method\": 50300, \"signature\": %d, \"download\": %d, \"path\": \"%s\" } }",
                    signatureID, download, escapedPath
                );
            } else {
                jsonIn = String.format(
                    "{ \"input\": { \"method\": 50300, \"signature\": %d } }",
                    signatureID
                );
            }

            System.out.println("Getting latest installer for signature: " + signatureID);
            if (download > 0) {
                System.out.println("Download enabled, path: " + downloadPath);
            }

            // Call invoke
            PointerByReference jsonOutRef = new PointerByReference();
            int rc = library.wa_api_invoke(new WString(jsonIn), jsonOutRef);

            // Get result
            String jsonOut = "{}";
            Pointer jsonOutPtr = jsonOutRef.getValue();
            if (jsonOutPtr != null) {
                jsonOut = jsonOutPtr.getWideString(0);
                library.wa_api_free(jsonOutPtr);
            }

            if (rc != 0) {
                System.err.println("Get latest installer failed with code: " + rc);
                System.err.println("Response: " + jsonOut);
                return null;
            }

            System.out.println("Latest installer info retrieved successfully");
            System.out.println("Response: " + jsonOut);

            // Parse response to get the downloaded file path
            if (download > 0) {
                JSONObject response = new JSONObject(jsonOut);
                if (response.has("result")) {
                    JSONObject result = response.getJSONObject("result");
                    if (result.has("path")) {
                        return result.getString("path");
                    }
                }
            }

            return null;

        } catch (Exception e) {
            System.err.println("Get latest installer error: " + e.getMessage());
            e.printStackTrace();
            return null;
        }
    }

    /**
     * Install From Files - Method ID 50301
     * This is the method the customer reported causes teardown failures on RHEL
     */
    private static void installFromFiles(int signatureID, String installerPath) {
        try {
            // Create install from files request
            String escapedPath = installerPath.replace("\\", "\\\\");
            String jsonIn = String.format(
                "{ \"input\": { \"method\": 50301, \"signature\": %d, \"path\": \"%s\", \"force_close\": 0 } }",
                signatureID, escapedPath
            );

            System.out.println("Installing from file for signature: " + signatureID);
            System.out.println("Installer path: " + installerPath);

            // Call invoke
            PointerByReference jsonOutRef = new PointerByReference();
            int rc = library.wa_api_invoke(new WString(jsonIn), jsonOutRef);

            // Get result
            String jsonOut = "{}";
            Pointer jsonOutPtr = jsonOutRef.getValue();
            if (jsonOutPtr != null) {
                jsonOut = jsonOutPtr.getWideString(0);
                library.wa_api_free(jsonOutPtr);
            }

            if (rc != 0) {
                System.err.println("Install from files failed with code: " + rc);
                System.err.println("Response: " + jsonOut);
                return;
            }

            System.out.println("Install from files completed successfully");
            System.out.println("Response: " + jsonOut);

        } catch (Exception e) {
            System.err.println("Install from files error: " + e.getMessage());
            e.printStackTrace();
        }
    }
    
    /**
     * Teardown OESIS Framework
     */
    private static void teardown() {
        try {
            if (library != null) {
                library.wa_api_teardown();
            }
        } catch (Exception e) {
            System.err.println("Teardown error: " + e.getMessage());
        }
    }
}
