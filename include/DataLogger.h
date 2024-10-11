#ifndef DATALOGGER_H
#define DATALOGGER_H

#include <SD.h>
#include <SPI.h>
#include "config.h"

class DataLogger {
public:
    DataLogger();
    bool begin();
    void logData(const String &data);
    void logCSV(uint8_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, int satellites, float speed, double lat, double lng);
private:
    File logFile;
    File csvFile;
};

#endif // DATALOGGER_H
