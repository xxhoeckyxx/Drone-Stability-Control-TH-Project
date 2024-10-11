#ifndef WEBSERVERHANDLER_H
#define WEBSERVERHANDLER_H

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <WebSocketsServer.h>
#include "config.h"
#include <LittleFS.h>

class WebServerHandler {
public:
    WebServerHandler();
    void begin();
    void appendLogString(const String &message);
    void appendLogChar(const char &c);
    void handleWebSocket();
private:
    AsyncWebServer server;
    WebSocketsServer webSocket;
    String log;
    void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length);
    void sendDataToWebSocket(String &data);
};

#endif // WEBSERVERHANDLER_H
