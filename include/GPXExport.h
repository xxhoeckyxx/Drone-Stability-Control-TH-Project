#ifndef GPXEXPORT_H
#define GPXEXPORT_H

#include <SD.h>

class GPXExport {
public:
    GPXExport();
    bool begin(int year, int month, int day, int hour, int minute, int second);
    void exportData(double lat, double lng, int year, int month, int day, int hour, int minute, int second, float speed, int satellites, float hdop);
    void end();
private:
    File gpxFile;
};

#endif // GPXEXPORT_H
