// WiFi credentials are put in environment variables
// PIO_WIFI_SSID and PIO_WIFI_PASS respectively.
// NOTE: if your credentials has a space, please put
// a backslash before the space. Otherwise, the
// compiler will throw random errors that you will
// spend an hour debugging.
// DON'T. ASK ME. HOW I KNOW THIS.

#define WIFI_SSID pio_wifi_ssid
#define WIFI_PASS pio_wifi_pass

// IP Addesses are stored in these
// weird comma seperated values
// for some reason.

#define WIFI_LOCALIP 192,168,0,165
#define WIFI_GATEWAY 192,168,0,1
#define WIFI_SUBNET 255,255,255,0
#define WIFI_PRIMARYDNS 1,1,1,1
#define WIFI_SECONDARYDNS 8,8,8,8
