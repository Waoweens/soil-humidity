#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <TaskScheduler.h>
#include <LiquidCrystal_I2C.h>
#include <auto.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

const int pinRelay = D6;
const int pinSensorPower = D5;
const int pinSensorData = A0;

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

	server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
		request->send_P(200, "text/html", INDEX_HTML);
	});

	server.begin();
}

void loop() {
}
