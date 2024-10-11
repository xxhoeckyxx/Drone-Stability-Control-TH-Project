#include "sensors.h"
#include <Wire.h>
#include "config.h"
#include "initializeClock.h"
#include "WebServerHandler.h"

extern WebServerHandler webServerHandler;

TinyGPSPlus gps;
HardwareSerial serial_Port(1);
MPU6050 mpu;
DataLogger dataLogger;
GPXExport gpxExport;

void setupSensors() {
    Wire.begin();
    serial_Port.begin(GPS_BAUD_RATE, SERIAL_8N1, 16, 17);
    initializeClock();
    pinMode(LED_PIN, OUTPUT); 
    mpu.initialize();

    digitalWrite(LED_PIN, HIGH);
    Serial.println("LED ON");
    webServerHandler.appendLogString("LED ON");

    if (!mpu.testConnection()) {
        Serial.println("MPU6050 connection failed");
        webServerHandler.appendLogString("MPU6050 connection failed");
    } else {
        Serial.println("MPU6050 initialized");
        webServerHandler.appendLogString("MPU6050 initialized");
    }
    if (!dataLogger.begin()) {
        Serial.println("DataLogger initialization failed");
        webServerHandler.appendLogString("DataLogger initialization failed");
    } else {
        Serial.println("DataLogger initialized");
        webServerHandler.appendLogString("DataLogger initialized");
    }

    // Initialisiere GPXExport mit den aktuellen Uhrzeit- und Datumswerten
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println("Failed to obtain time");
        webServerHandler.appendLogString("Failed to obtain time");
    } else {
        if (!gpxExport.begin(timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec)) {
            Serial.println("GPXExport initialization failed");
            webServerHandler.appendLogString("GPXExport initialization failed");
        } else {
            Serial.println("GPXExport initialized");
            webServerHandler.appendLogString("GPXExport initialized");
        }
    }

    digitalWrite(LED_PIN, LOW);
    Serial.println("LED OFF");
    webServerHandler.appendLogString("LED OFF");

}

void readSensors() {
    while (serial_Port.available() > 0) {
        char c = serial_Port.read();
        gps.encode(c);

        if (gps.location.isValid()) {
            int satellites = gps.satellites.value();
            double speed;
            double course = gps.course.deg();
            double hour = gps.time.hour() + 2;
            double minute = gps.time.minute();
            double second = gps.time.second();
            double day = gps.date.day();
            double month = gps.date.month();
            double year = gps.date.year();
            double hdop = gps.hdop.hdop();
            if(gps.speed.kmph() >= 2.5) {
                speed = gps.speed.kmph();
            } else {
                speed = 0;
            }
            double lng = gps.location.lng();
            double lat = gps.location.lat();

            String data = "Lat: " + String(lat, 6) + ", Lon: " + String(lng, 6);
            String date = "Date: " + String(day) + "." + String(month) + "." + String(year);
            String time = "Time: " + String(hour) + ":" + String(minute) + ":" + String(second);
            webServerHandler.appendLogString("Logging Data at " + time + "\n" + data);
            Serial.println("Logging Data at " + time + "\n" + data);
            webServerHandler.appendLogString("Speed: " + String(speed));
            Serial.println("Speed: " + String(speed));
            webServerHandler.appendLogString("Satellites: " + String(satellites));
            Serial.println("Satellites: " + String(satellites));
            webServerHandler.appendLogString("Course: " + String(course, 2));
            Serial.println("Course: " + String(course, 2));
            Serial.println("HDOP: " + String(hdop, 2));

            digitalWrite(LED_PIN, LOW);
            Serial.println("LED OFF");
            webServerHandler.appendLogString("LED OFF");

            gpxExport.exportData(lat, lng, year, month, day, hour, minute, second, speed, satellites, hdop);
            dataLogger.logData(data);
            dataLogger.logCSV(year, month, day, hour, minute, second, satellites, speed, lat, lng);
            delay(LOG_INTERVAL);

            digitalWrite(LED_PIN, HIGH);
            Serial.println("LED ON");
            webServerHandler.appendLogString("LED ON");
        } else {
            //Serial.println("No valid GPS location");
        }
    }
}
