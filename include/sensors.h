#ifndef SENSORS_H
#define SENSORS_H

#include <TinyGPS++.h>
#include <MPU6050.h>
#include "DataLogger.h"
#include "GPXExport.h"

extern TinyGPSPlus gps;
extern MPU6050 mpu;
extern DataLogger dataLogger;
extern GPXExport gpxExport;

void setupSensors();
void readSensors();

#endif // SENSORS_H
