#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LiquidCrystal_I2C.h>
#include <TaskScheduler.h>
#include <auto.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

const int pinRelay = D6;
const int pinSensorPower = D5;
const int pinSensorData = A0;
String localIP_str;

String index_pre(const String &var) {
	if (var == "LOCALIPADDRESS") return localIP_str;

	return String();
}

void setup() {
	pinMode(pinRelay, OUTPUT);
	pinMode(pinSensorPower, OUTPUT);
	digitalWrite(pinSensorPower, LOW);

	Serial.begin(115200);

	if (!WiFi.config(localIP, gateway, subnet, primaryDNS, secondaryDNS)) {
		Serial.println("WiFi failed to configure!");
	}
	WiFi.begin(ssid, password);
	Serial.print("Connecting.");
	while (WiFi.status() != WL_CONNECTED) {
		Serial.print(".");
		delay(500);
	}
	Serial.println("Connected!");
	Serial.println(WiFi.localIP());
	localIP_str = WiFi.localIP().toString();

	server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
		request->send_P(200, "text/html", INDEX_HTML, LEN_INDEX_HTML, index_pre);
	});

	server.on("/dist.css", HTTP_GET, [](AsyncWebServerRequest *request) {
		request->send_P(200, "text/css", DIST_CSS, LEN_DIST_CSS);
	});

	server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request) {
		request->send_P(200, "text/javascript", SCRIPT_JS, LEN_SCRIPT_JS);
	});

	server.on("/icon.png", HTTP_GET, [](AsyncWebServerRequest *request) {
		request->send_P(200, "image/png", ICON_PNG, LEN_ICON_PNG);
	});

	server.begin();
}

void loop() {}
