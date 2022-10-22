from os import listdir
import re
#Import("env")

def build_page():
	origin = "./web/src/"
	extras = "extras.h"
	ignore = ["package.json", "package-lock.json", "node_modules","tailwind.config.js", "style.css"]
	result = "./src/auto.h"

	list = listdir(origin)
	# "FILENAME": {length: "length", data: "data"}
	pages = {}

	for file in list:
		name = re.sub("[^A-Z]", "_", file.upper())
		if file == extras:
			with open(origin+file, "r") as f:
				page_extras = f.read()
				f.close()
		elif any(ignored in file for ignored in ignore):
			continue
		else:
			with open(origin+file, "rb") as f:
				data = f.read()
				pages[name] = {}
				pages[name]["length"] = len(data)
				pages[name]["data"] = "0x" + data.hex("_").replace("_", ",0x")
				f.close()

	with open(result, "w+") as f:
		f.write("// !!! WARNING: AUTO-GENERATED FILE!\n// !!! PLEASE DO NOT MODIFY IT AND USE \"prebuild.py\"\n//\n\n")
		f.write(page_extras+"\n")
		for name, page in pages.items():
			f.write(f"static const size_t {'LEN_' + name} = {page['length']};\n")
			f.write(f"static const uint8_t {name}[] PROGMEM = {{{page['data']}}};\n")

build_page()