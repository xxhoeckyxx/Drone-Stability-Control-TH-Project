#include "GPXExport.h"

GPXExport::GPXExport() {}

bool GPXExport::begin(int year, int month, int day, int hour, int minute, int second) {
    // Initialisiere die GPX-Datei mit den gegebenen Zeit- und Datumsinformationen
    gpxFile = SD.open("/track.gpx", FILE_WRITE);
    if (!gpxFile) {
        return false;
    }

    gpxFile.println("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>");
    gpxFile.println("<gpx version=\"1.1\" creator=\"ESP32\" xmlns=\"http://www.topografix.com/GPX/1/1\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://www.topografix.com/GPX/1/1 http://www.topografix.com/GPX/1/1/gpx.xsd\">");
    gpxFile.println("<metadata>");
    gpxFile.printf("\t<name>Motorcycle Ride</name>\n");
    gpxFile.printf("\t<desc>Recorded by ESP32 GPS Logger</desc>\n");
    gpxFile.printf("\t<author>\n");
    gpxFile.printf("\t\t<name>Christopher Höck</name>\n");
    gpxFile.printf("\t\t<email>\n");
    gpxFile.printf("\t\t\t<id>chrisi.hoeck</id>\n");
    gpxFile.printf("\t\t\t<domain>@gmail.com</domain>\n");
    gpxFile.printf("\t\t</email>\n");
    gpxFile.printf("\t</author>\n");
    gpxFile.printf("\t<copyright author=\"Christopher Höck\">\n");
    gpxFile.printf("\t\t<year>%d</year>\n", year);
    gpxFile.printf("\t</copyright>\n");
    gpxFile.printf("\t<time>%04d-%02d-%02dT%02d:%02d:%02dZ</time>\n", year, month, day, hour, minute, second);
    gpxFile.printf("\t<bounds minlat=\"49.3300756\" minlon=\"11.0240433\" maxlat=\"49.337933\" maxlon=\"11.033276\" />\n");
    gpxFile.println("</metadata>");
    gpxFile.println("<trk>");
    gpxFile.println("<name>Track 001</name>");
    gpxFile.println("<trkseg>");

    return true;
}

void GPXExport::exportData(double lat, double lng, int year, int month, int day, int hour, int minute, int second, float speed, int satellites, float hdop) {
    // Implementiere die Funktion zum Exportieren von GPX-Daten
    if (gpxFile) {
        gpxFile.printf("<trkpt lat=\"%.6f\" lon=\"%.6f\">\n", lat, lng);
        gpxFile.printf("\t<ele>0.0</ele>\n");
        gpxFile.printf("\t<time>%04d-%02d-%02dT%02d:%02d:%02dZ</time>\n", year, month, day, hour, minute, second);
        gpxFile.printf("\t<speed>%.2f</speed>\n", speed);
        gpxFile.printf("\t<sat>%.d</sat>\n", satellites);
        gpxFile.printf("\t<hdop>%.2f</hdop>\n", hdop);
        gpxFile.println("</trkpt>");
    }
}

void GPXExport::end() {
    // Schließe die GPX-Datei
    if (gpxFile) {
        gpxFile.println("</trkseg>");
        gpxFile.println("</trk>");
        gpxFile.println("</gpx>");
        gpxFile.close();
    }
}
