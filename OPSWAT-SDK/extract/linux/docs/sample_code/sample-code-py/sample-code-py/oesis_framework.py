'''
    Sample Python integration with the MDES SDK V4.
'''
from ctypes import c_int, c_wchar_p, POINTER, byref, CDLL
import os
import sys
from oesis_utils import *
from oesis_constants import *


class OesisFramework:
    
    def __init__(self, oesis_lib, platform_):
        try:
            version = sys.version
            current_dir = os.path.dirname(os.path.abspath(__file__))
            if current_dir.rfind('\\') != -1 :
                dir_path = current_dir[0:current_dir.rfind('\\')]
            else :
                dir_path = current_dir[0:current_dir.rfind('/')]

            if platform_ == "Windows":
                if float(version[:3]) >= 3.8:
                    os.add_dll_directory(dir_path + "\\libs")
                    self.oesis_lib = CDLL(oesis_lib)
                else:
                    from ctypes import WinDLL
                    self.oesis_lib = WinDLL(dir_path + "\\libs\\" + oesis_lib)
            else:
                self.oesis_lib = CDLL(dir_path + "/libs/" + oesis_lib)
        except AssertionError as error:
            print('accept:', error)
            return ""
    
    def setup_oesis(self, json_config):
        setup = self.oesis_lib['wa_api_setup']
        setup.restype = c_int
        setup.argtypes = [c_wchar_p, POINTER(c_wchar_p)]
        json_out = c_wchar_p()
        rc = setup(json_config, byref(json_out))
        return rc, json_out
    
    def invoke_method(self, input):
        invoke = self.oesis_lib['wa_api_invoke']
        invoke.restype = c_int
        invoke.argtypes = [c_wchar_p, POINTER(c_wchar_p)]
        json_out = c_wchar_p()
        if type(input) == type(''):
            json_in = input
        else:
            json_in = OesisUtils.create_json_in(input)
        rc = invoke(json_in, byref(json_out))
        return rc, json_out

    def teardown(self):
        teardown = self.oesis_lib['wa_api_teardown']
        teardown.restype = c_int
        return teardown

    def free(self):
        free = self.oesis_lib['wa_api_free']
        free.restype = c_int
        free.argtypes = [c_wchar_p]
        return free

    def detect_products(self, category = 0, categories = []):
        input = {
            "method": 0,
        }
        if categories:
            input["categories"] = categories
        else:
            input["category"] = category
        rc, json_out = self.invoke_method(input)
        deteced_products = OesisUtils.get_json_value(rc, json_out, ["detected_products"])
        return deteced_products
        