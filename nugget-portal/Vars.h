//LittleFS
#define FORMAT_LITTLEFS_IF_FAILED true

// WiFi
#define MAX_CLIENTS 4   // ESP32 supports up to 10 but I have not tested it yet
#define WIFI_CHANNEL 6  // 2.4ghz channel 6 https://en.wikipedia.org/wiki/List_of_WLAN_channels#2.4_GHz_(802.11b/g/n/ax)

// Buttons
#define up_btn 9   // up button
#define dn_btn 18  // down button
#define lt_btn 11  // left button
#define rt_btn 7   // right button