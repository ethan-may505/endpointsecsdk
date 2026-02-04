How to build sample code
1.  Put libraries and license into the same folder with source
2.  fill `passkey_string` into json_config in main.go
3.  Init module by cmd: go mod init sample_code  
4.  Build by cmd: 
-   For linux/macOs: go build -o sample_code -tags COMPILE_FOR_UNIX
-   For Windows: go build -o sample_code.exe -tags COMPILE_FOR_WINDOWS
5.  Run sample_code