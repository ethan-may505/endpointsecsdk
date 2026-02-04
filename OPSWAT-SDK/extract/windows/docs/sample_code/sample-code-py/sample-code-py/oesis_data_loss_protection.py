from oesis_framework import *

class OesisDataLossProtection:

    def __init__(self, oesis):
        self.oesis = oesis

    def setup_dlp_module(self, method_id):
        input = {
            "method": method_id
        }
        rc, json_out = self.oesis.invoke_method(input)
        output = OesisUtils.get_json_value(rc, json_out, [])
        return rc, output
    
    def manage_dlp_module(self, method_id, operation = ''):
        input = {
            "method": method_id
        }
        if operation != '':
            input['operation'] = operation
        rc, json_out = self.oesis.invoke_method(input)
        ouput = OesisUtils.get_json_value(rc, json_out, [])
        return rc, ouput

    def get_dlp_state(self, method_id):
        input = {
            "method": method_id
        }
        rc, json_out = self.oesis.invoke_method(input)
        ouput = OesisUtils.get_json_value(rc, json_out, ["state", "enabled"])
        return rc, ouput