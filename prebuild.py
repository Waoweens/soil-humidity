from os import listdir
import re
#Import("env")

def build_page():
	origin = "./web/"
	result = "./src/auto.h"
	list = listdir(origin)
	pages = {}

	for file in list:
		with open(origin+file, "r") as f:
			name = re.sub("[^A-Z]", "_", file.upper())
			pages[name] = f.read()

	print(pages)

	with open(result, "w+") as f:
		f.write("// !!! WARNING: AUTO GENERATED FILE. DO NOT MODIFY!\n\n")
		f.write("#include <Arduino.h>\n")
		f.write("#include <ESP8266WiFi.h>\n")
		f.write("#include <config.h>\n")
		f.write("static const char* ssid = WIFI_SSID;\n")
		f.write("static const char* password = WIFI_PASS;\n")
		f.write("static const IPAddress localIP(WIFI_LOCALIP);\n")
		f.write("static const IPAddress gateway(WIFI_GATEWAY);\n")
		f.write("static const IPAddress subnet(WIFI_SUBNET);\n")
		f.write("static const IPAddress primaryDNS(WIFI_PRIMARYDNS);\n")
		f.write("static const IPAddress secondaryDNS(WIFI_SECONDARYDNS);\n")
		for name, page in pages.items():
			f.write(f"static const char {name}[] PROGMEM = R\"cpprawliteralstr({page})cpprawliteralstr\";\n")
build_page()