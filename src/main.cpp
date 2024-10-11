#include <Arduino.h>
#include "sensors.h"
#include "WebServerHandler.h"

WebServerHandler webServerHandler;

void setup() {
    Serial.begin(115200);

    setupSensors();
    webServerHandler.begin();
}

void loop() {
    digitalWrite(LED_PIN, HIGH);

    readSensors();
    webServerHandler.handleWebSocket();
    delay(LOG_INTERVAL);

    digitalWrite(LED_PIN, LOW);

}
