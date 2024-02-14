# Nugget Portal

### Features

- Easy integration with the ESP32-S2 Mini.
- Customizable captive portal web page.
- Captive portal phishing page - store creds.
- Makes use of the Nugget display to show captured creds.

## Getting Started

Follow these steps to set up the WiFi captive portal on your ESP32-S2 Mini:

1. Clone or download this repository to your local machine.

2. Open the project using the Arduino IDE or PlatformIO.

3. Configure the SSID and password for your Wi-Fi network in the code.

```cpp
const char *ssid = "Guest_Wifi";
const char *password = NULL;
```

4. Customize the captive portal HTML page by modifying the `html_code.h` file. This is the web page that users will see when they connect to your network.

5. Flash the code to your ESP32-S2 Mini.

6. Once the code is uploaded, the ESP32-S2 Mini will act as a captive portal ready to catch login attempts.

## Usage

When a user connects to your Wi-Fi network, they will be redirected to the captive portal web page you customized. From there, you can implement authentication or display any information you desire. Once the user meets the required conditions (if any), they can click a button or perform an action to access the internet.

To handle user authentication, you can implement custom logic within the Arduino sketch, such as checking credentials against a database or requiring users to accept terms and conditions.

## Credits

This project was heavily inspired and adapted from this project by HakCat-Tech - [SSDP-Phisher](https://github.com/HakCat-Tech/Nugget-SSDP-Phisher)

## Disclaimer

Please be aware that implementing a captive portal may be subject to legal and privacy regulations in your region. Make sure to comply with local laws and respect user privacy when using this technology.

## About WiFi-Nugget

The WiFi-Nugget platform aims to simplify Wi-Fi development on ESP32-S2 Mini and similar microcontrollers. For more information about WiFi-Nugget or USB nugget, visit the [official website](https://retia.io).

---
