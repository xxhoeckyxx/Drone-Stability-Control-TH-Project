#include "DataLogger.h"

DataLogger::DataLogger() {}

bool DataLogger::begin() {
    if (!SD.begin(SD_CS_PIN)) {
        return false;
    }
    logFile = SD.open("/data.txt", FILE_WRITE);
    logFile.println("Latitude, Longitude");
    csvFile = SD.open("/log.csv", FILE_WRITE);
    csvFile.println("Date;Time;Satellites;Speed;Latitude;Longitude;");
    return logFile && csvFile;
}

void DataLogger::logData(const String &data) {
    if (logFile) {
        logFile.println(data);
        logFile.flush();
    }
}

void DataLogger::logCSV(uint8_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, int satellites, float speed, double lat, double lng) {
    if (csvFile) {
        csvFile.print(day);
        csvFile.print(".");
        csvFile.print(month);
        csvFile.print(".");
        csvFile.print(year);
        csvFile.print(";");
        csvFile.print(hour);
        csvFile.print(":");
        csvFile.print(minute);
        csvFile.print(":");
        csvFile.print(second);
        csvFile.print(";");
        csvFile.print(satellites);
        csvFile.print(";");
        csvFile.print(speed);
        csvFile.print(";");
        csvFile.print(lat, 6);
        csvFile.print(";");
        csvFile.print(lng, 6);
        csvFile.println(";");
        csvFile.flush();
    }
}
