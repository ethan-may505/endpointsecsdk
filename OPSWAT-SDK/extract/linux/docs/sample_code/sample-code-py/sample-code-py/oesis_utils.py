import json
import os
from os import path


class OesisUtils:
    
    def read_file_content(filename):
        with open(filename) as f:
            content = f.read()
        return content

    def create_folder(pathFolder):
        if not path.exists(pathFolder):
            os.mkdir(pathFolder)
        return 0
    
    def create_json_in(input):
        json_in = ""
        if "method" not in input.keys():
            json_in = "{ \"input\": { \"method\": -1 } }"
        else:
            json_in = "{\"input\": { \"method\": " +  str(input["method"])
            input.pop("method", None)
            for key, value in input.items():
                json_in = json_in + ", \"" + key + "\": "
                if type(value) == type(''):  
                    value = value.replace('\\','\\\\')
                    json_in = json_in + "\"" + value + "\""
                else:
                    json_in = json_in + str(value)
            json_in = json_in + " } }"
        return json_in
    
    def get_json_value(rc, json_out, keys):
        res = {}
        json_ = json.loads(json_out.value)
        if (rc < 0):
            res = json_["error"]
        else:
            json_ = json_["result"];
            if keys:
                for key in keys:
                    if key in json_:
                        res[key] = json_[key];
            else:
                res = json_;
        return res;
