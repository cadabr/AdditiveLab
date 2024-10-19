#!/usr/bin/python3

import os
import sys

if len(sys.argv) != 2:
    print("Usage: python add.py ClassName")
    sys.exit(1)

h_tmpl = open("Development/VSCode/AddClass/class.h", "r")
cpp_tmpl = open("Development/VSCode/AddClass/class.cpp", "r")
class_name_placeholder = "CLASS_NAME"
class_relative_path = sys.argv[1]
class_path = "Source/" + class_relative_path
class_dir = class_path.split("/")[:-1]
class_name = class_path.split("/")[-1]
project_dir = os.getcwd()

def check_dir_exist(dir_name):
    for dir in dir_name:
        if not os.path.exists(dir):
            os.mkdir(dir)
        os.chdir(dir)

def inst(tmpl_file, res_file_name):
    if os.path.exists(res_file_name):
        print("-- file " + res_file_name + " already exist! File will no be modified.")
        return
    lines = [line for line in tmpl_file]
    result = open(res_file_name, "a+")
    for line in lines:
        if class_name_placeholder in line and "include" in line:
            line = line.replace(class_name_placeholder, class_relative_path)
        if class_name_placeholder in line and "class" in line:
            line = line.replace(class_name_placeholder, class_name)
        result.write(line)
    result.close()
    print("-- file " + os.getcwd() + "/" + res_file_name + " created.")

check_dir_exist(class_dir)
inst(h_tmpl, class_name + ".h")
inst(cpp_tmpl, class_name + ".cpp")
os.chdir(project_dir)

print(f"Class {class_name} created successfully.")
