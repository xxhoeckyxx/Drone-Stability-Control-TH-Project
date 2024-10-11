#include "WebServerHandler.h"
#define MAX_LOG_LENGTH 112

WebServerHandler::WebServerHandler() : server(80), webSocket(81), log("") {}

void WebServerHandler::begin() {
    if (!LittleFS.begin(true)) {
        Serial.println("An error has occurred while mounting LittleFS");
        return;
    }
    Serial.println("LittleFS mounted successfully");

    WiFi.softAP(WIFI_SSID, WIFI_PASSWORD);
    IPAddress IP = WiFi.softAPIP();
    Serial.print(WIFI_SSID);
    Serial.print(" IP address: ");
    Serial.println(IP);

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(LittleFS, "/index.html", "text/html");
    });

    server.on("/log", HTTP_GET, [this](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", this->log);
    });

    server.begin();
    Serial.println("HTTP server started");

    webSocket.begin();
    webSocket.onEvent([this](uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
        this->webSocketEvent(num, type, payload, length);
    });
    Serial.println("WebSocket server started");
}

void WebServerHandler::webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
    if (type == WStype_TEXT) {
        Serial.printf("[%u] get Text: %s\n", num, payload);
        webSocket.sendTXT(num, payload);
    } else if (type == WStype_DISCONNECTED) {
        Serial.printf("[%u] Disconnected!\n", num);
    } else if (type == WStype_CONNECTED) {
        Serial.printf("[%u] Connected from %s\n", num, webSocket.remoteIP(num).toString().c_str());
    }
}

void WebServerHandler::sendDataToWebSocket(String &data) {
    webSocket.broadcastTXT(data);
}

void WebServerHandler::appendLogString(const String &message) {
    log += message + "\n";
    if (log.length() > MAX_LOG_LENGTH) {
        log = log.substring(log.length() - MAX_LOG_LENGTH);
    }
    sendDataToWebSocket(log);
}

void WebServerHandler::appendLogChar(const char &c) {
    log += c;
    if (log.length() > MAX_LOG_LENGTH) {
        log = log.substring(log.length() - MAX_LOG_LENGTH);
    }
    String charAsString(c);
    sendDataToWebSocket(charAsString);
}

void WebServerHandler::handleWebSocket() {
    webSocket.loop();
}
