
from oesis_framework import *
from oesis_generic_product import *
from oesis_antimalware import *
from oesis_vulnerability_patch import *
from oesis_data_loss_protection import *
from oesis_utils import *

import argparse
import sys
import json
import platform
import time
import queue
from threading import Thread, Lock


def setup_config(oesis):
    try:
        current_dir = os.path.dirname(os.path.abspath(__file__))
        if current_dir.rfind('\\') != -1 :
            dir_path = current_dir[0:current_dir.rfind('\\')]
        else :
            dir_path = current_dir[0:current_dir.rfind('/')]

        passkey = OesisUtils.read_file_content(dir_path + "/libs/pass_key.txt")
        input = "{ \"config\" : { \"enable_pretty_print\": true, \"passkey_string\": \"" + passkey + "\" } }"
        json_config = c_wchar_p(input)
        json_out = c_wchar_p()
        rc, json_out = oesis.setup_oesis(json_config)
        output = ""
        free = oesis.free()
        if rc < 0:
            output = json.loads(json_out.value)
            free(json_out)
        else:
            free(json_out)
        return rc, output
    except AssertionError as error:
        print('accept:', error)
        return -1, ""

def load_libs():
    try:
        platform_ = ""
        if platform.uname()[0] == "Windows":
            platform_ = "Windows"
            lib_file = "libwaapi.dll"
        elif platform.uname()[0] == "Linux":
            platform_ = "Linux"
            lib_file = "libwaapi.so"
        else:
            platform_ = "Darwin"
            lib_file = "libwaapi.dylib"
        return lib_file, platform_
    except AssertionError as error:
        print('accept:', error)
        return "", ""


def call_method_cli(parser, oesis, args):
    params = {}
    for arg in vars(args):
        if arg in MAP_PARAMS and getattr(args, arg) is not None:
            params[MAP_PARAMS.get(arg)] = getattr(args, arg)
    if args.file:
        if len(params) == 0:
            json_in = OesisUtils.read_file_content(args.file)
            rc, json_out = oesis.invoke_method(json_in)
        else:
            parser.print_usage()
    else:
        if type(params["method"]) == type(''):
            params["method"] = METHOD_ID.get(MAP_METHOD.get(params["method"]))
        rc, json_out = oesis.invoke_method(params)
    output = OesisUtils.get_json_value(rc, json_out, [])
    return output


def check_av_cli(oesis):
    output = {
        "check_av": []
    }
    products = oesis.detect_products(5)
    products = products["detected_products"]
    if products:
        for product in products:
            info = {}
            sig_id = int(product['signature'])
            sig_name = product['sig_name']
            info['sig_id'] = sig_id
            info['sig_name'] = sig_name
            
            generic = OesisGenericProduct(oesis, sig_id, sig_name)
            version = generic.get_version()
            info['version'] = version
            antimalware = OesisAntimalware(oesis, sig_id)
            info['GetRTPState'] = antimalware.get_rtp_state()
            info['GetDefinitonState'] = antimalware.get_definition_state()
            info['GetLastScanTime'] = antimalware.get_last_scan_time()
            info['GetScanState'] = antimalware.get_scan_state()
            output["check_av"].append(info)
    return output


def check_vuln_cli(oesis):
    output = {
        "check_av": []
    }
    products = oesis.detect_products(0)
    products = products["detected_products"]
    if products:
        OesisVulnerabilityAndPatch.consume_offline_vmod_database(oesis)
        OesisVulnerabilityAndPatch.load_patch_database(oesis)
        for product in products:
            info = {}
            sig_id = int(product['signature'])
            sig_name = product['sig_name']
            info['sig_id'] = sig_id
            info['sig_name'] = sig_name
            
            generic = OesisGenericProduct(oesis, sig_id, sig_name)
            version = generic.get_version()
            info['version'] = version

            vulnerability = OesisVulnerabilityAndPatch(oesis, sig_id)
            info['GetProductPatchLevel'] = vulnerability.get_product_patch_level()
            info['GetProductVulnerability'] = vulnerability.get_product_vulnerability()
            info['GetRemediations'] = vulnerability.get_remediations()
            rc, info['GetLatestInstaller'] = vulnerability.get_lastest_installer()
            output["check_av"].append(info)
    return output


def patch_product_cli(oesis, sig_id, location, force_close=0):
    output = {
        "patch_product": []
    }
    vulnerability = OesisVulnerabilityAndPatch(oesis, sig_id)
    OesisVulnerabilityAndPatch.consume_offline_vmod_database(oesis)
    OesisVulnerabilityAndPatch.load_patch_database(oesis)
    rc, output = vulnerability.get_lastest_installer(1, location)
    if rc >= 0:
        path = output["path"].replace('\\','\\\\')
        rc, output = vulnerability.install_from_file(path, force_close)
    return output


def remove_product_cli(oesis, sig_id, type='native'):
    input = {
        "signature": sig_id,
        "method": METHOD_ID["WAAPI_MID_COMMON_UNINSTALL"],
        "type": type
    }
    rc, json_out = oesis.invoke_method(input)
    output = OesisUtils.get_json_value(rc, json_out, [])
    return output


def dlp_module_cli(oesis, module, operation, lock):
    setup_method_id = 120010;
    manage_method_id = 120013;
    get_state_method_id = 120012;
    operation = operation;
    message = "A service will be installed and running processes will be injected with a DLL. Please confirm Yes/No [Y/N]? "
    if module == 'akl':
        setup_method_id = 120002;
        manage_method_id = 120001;
        get_state_method_id = 120004;
    dlp_module = OesisDataLossProtection(oesis)
    rc = 0
    output = {}
    if operation.lower() == 'enable':
        lock.acquire()
        confirm = input(
            "A service and driver will be installed, please confirm yes/no [Y/N]? ")
        lock.release()
        if(confirm.lower() == 'y' or confirm.lower() == 'yes'):
            rc, output = dlp_module.setup_dlp_module(setup_method_id)
            if rc < 0:
                pass
            rc, output = dlp_module.manage_dlp_module(manage_method_id, operation)
            if rc >= 0:
                rc, output = dlp_module.get_dlp_state(get_state_method_id)
        else:
            output['message'] = 'user do not accept module'
        
    elif operation.lower() == 'disable':
        if module == 'akl':
            setup_method_id = 120003
        else:
            setup_method_id = 120011
        rc, output = dlp_module.setup_dlp_module(setup_method_id)
    return output
    
def check_args(args_, lock):
    lock.acquire()
    parser = argparse.ArgumentParser()
    subparser = parser.add_subparsers(dest='command')
    call_method = subparser.add_parser('call-method', help='Call a specific method')
    call_method_input = call_method.add_mutually_exclusive_group(required=True)
    call_method_input.add_argument('--file', type=str)
    call_method_input.add_argument('--id', type=int)
    call_method_input.add_argument('--name', type=str)
    call_method_param = call_method.add_argument_group('param')
    call_method_param.add_argument('--sig', type=int)
    call_method_param.add_argument('--scan_type', type=str)
    call_method_param.add_argument('--path', type=str)
    call_method_param.add_argument('--clean', type=str)
    call_method_param.add_argument('--timeframe' , type=int)
    call_method_param.add_argument('--operation', type=str)
    call_method_param.add_argument('--password', type=str)
    call_method_param.add_argument('--user', type=str)
    call_method_param.add_argument('--vm_id', type=str)
    call_method_param.add_argument('--token', type=str)
    call_method_param.add_argument('--dat_input_source_file', type=str)
    call_method_param.add_argument('--dat_input_checksum_file', type=str)
    call_method_param.add_argument('--timeout' , type=int)
    call_method_param.add_argument('--os_id' , type=int)
    call_method_param.add_argument('--tolerance' , type=int)
    call_method_param.add_argument('--online' , type=int)
    call_method_param.add_argument('--type', type=str)
    call_method_param.add_argument('--pid' , type=int)
    check_av = subparser.add_parser('check-av', help='Check for Antimalware product')
    check_vuln = subparser.add_parser('check-vuln', help='Check for vulnerability and patch of all product')
    patch_product = subparser.add_parser('patch-product', help='Download latest version and install product')
    patch_product.add_argument('--sig', type=int, required=True)
    patch_product.add_argument('--location', type=str, required=True)
    patch_product.add_argument('--force_close', type=int)
    remove_product = subparser.add_parser('remove-product', help='Uninstall a product')
    remove_product.add_argument('--sig', type=int, required=True)
    remove_product.add_argument('--type', type=str)
    dlp_module = subparser.add_parser('dlp', help='DLP module for Antikeylogger and AntiScreenCapture').add_mutually_exclusive_group(required=True)
    dlp_module.add_argument('--asc', type=str)
    dlp_module.add_argument('--akl', type=str)
    try:
        args = parser.parse_args()
        lock.release()
        if args.command:
            output = ""
            oesis_lib, platform_ = load_libs()
            oesis = OesisFramework(oesis_lib, platform_)
            if oesis == "":
                return
            rc, output = setup_config(oesis)
            if rc < 0:
                return output
            if args.command == 'call-method':
                output = call_method_cli(parser, oesis, args)
            elif args.command == 'check-av':
                output = check_av_cli(oesis)
            elif args.command == 'check-vuln':
                output = check_vuln_cli(oesis)
            elif args.command == 'remove-product':
                if args.type:
                    output = remove_product_cli(oesis, args.sig, args.type)
                else:
                    output = remove_product_cli(oesis, args.sig)
            elif args.command == 'patch-product':
                if args.force_close:
                    output = patch_product_cli(oesis, args.sig, args.location, args.force_close)
                else:
                    output = patch_product_cli(oesis, args.sig, args.location)
            elif args.command == 'dlp':
                if args.asc:
                    output = dlp_module_cli(oesis, 'asc', args.asc, lock)
                else:
                    output = dlp_module_cli(oesis, 'akl', args.akl, lock)
            return output
        else:
            parser.print_help()
    except AssertionError as error:
        print('accept:', error)
        lock.release()
        return ""

def show_running_status():
    status = 'RUNNING'
    print(status + "\r", end='')
    for i in range(5):
        time.sleep(DELAY)
        status += '.'
        print(status + "\r", end='')
    time.sleep(DELAY)
    clear_running_status()
        
def clear_running_status():
    print('\r            \r', end='')

import logging

def main():
    queue_ = queue.Queue()
    lock = Lock()
    thead_cli = Thread(target=lambda func, arg1, _lock: func.put(check_args(arg1, _lock)), args=(queue_, sys.argv, lock))
    thead_cli.start()
    lock.acquire()
    lock.release()
    i = 0
    while thead_cli.is_alive():
        lock.acquire()
        show_running_status()
        lock.release()
    thead_cli.join()
    output = queue_.get()
    if output != "":
        output = json.dumps(output, indent = 4)
        print(output)



if __name__ == '__main__':
    main()