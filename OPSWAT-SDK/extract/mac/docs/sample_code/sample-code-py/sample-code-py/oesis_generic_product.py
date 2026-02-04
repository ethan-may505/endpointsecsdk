from oesis_utils import OesisUtils
from oesis_framework import *

class OesisGenericProduct:
    
    def __init__(self,oesis,sig_id, sig_name):
        self.oesis = oesis
        self.sig_id = sig_id
        self.sig_name = sig_name
        
    def get_version(self):
        input = {
            "signature": self.sig_id,
            "method": METHOD_ID["WAAPI_MID_COMMON_GET_VERSION"]
        }
        rc, json_out = self.oesis.invoke_method(input)
        version = OesisUtils.get_json_value(rc, json_out, ["version"])
        return version
    
    def get_running_state(self):
        input = {
            "signature": self.sig_id,
            "method": METHOD_ID["WAAPI_MID_GET_RUNNING_STATE"]
        }
        rc, json_out = self.oesis.invoke_method(input)
        output = OesisUtils.get_json_value(rc, json_out, [])
        return rc, output

    def run(self):
        input = {
            "signature": self.sig_id,
            "method": METHOD_ID["WAAPI_MID_COMMON_RUN"]
        }
        rc, json_out = self.oesis.invoke_method(input)
        output = OesisUtils.get_json_value(rc, json_out, [])
        return rc, output

    def terminate_processes(self):
        input = {
            "signature": self.sig_id,
            "method": METHOD_ID["WAAPI_MID_COMMON_TERMINATE"]
        }
        rc, json_out = self.oesis.invoke_method(input)
        output = OesisUtils.get_json_value(rc, json_out, [])
        return rc, output

    