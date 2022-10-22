#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <config.h>
static const char* ssid = WIFI_SSID;
static const char* password = WIFI_PASS;
static const IPAddress localIP(WIFI_LOCALIP);
static const IPAddress gateway(WIFI_GATEWAY);
static const IPAddress subnet(WIFI_SUBNET);
static const IPAddress primaryDNS(WIFI_PRIMARYDNS);
static const IPAddress secondaryDNS(WIFI_SECONDARYDNS);