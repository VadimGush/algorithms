# Python script to build one header for the static library.
import os
import re

header_names = []
headers = []

for subdir, dirs, files in os.walk("src"):
    for file in files:
        if (file.endswith(".h") or file.endswith(".hpp")) and "experiments" not in subdir:
            filepath = os.path.join(subdir, file)
            headers.append(filepath)
            header_names.append(file)

local_header_pattern = re.compile(r"#include \".*\"")
include_pattern = re.compile(r"#include <.*>")
pragma_pattern = re.compile(r"#pragma once")

content = []
includes = set()
for header in headers:
    f = open(header)
    lines = f.readlines()
    for line in lines:
        if local_header_pattern.match(line):
            continue
        if pragma_pattern.match(line):
            continue
        if include_pattern.match(line):
            includes.add(line.replace("\n", ""))
            continue
        content.append(line)
    f.close()

print("#pragma once")
for header in header_names:
    print("// " + header)
for include in includes:
    print(include.replace("\n", ""))
for line in content:
    print(line.replace("\n", ""))