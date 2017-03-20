#include "debug.h"
#include "connection.h"
#include "ota.h"

#define LED D4

void hardwareInit()
{
    Serial.begin(115200);
    debug("Starting Hardware.");
    pinMode(LED, OUTPUT);
}

void connectionStatus()
{
    if(Connection::self().getStatus()) {
        debug("Connected");
        digitalWrite(LED, LOW);
    } else {
        debug("Not connected");
        digitalWrite(LED, !digitalRead(LED));
        delay(100);
    }
}

void setup()
{
    hardwareInit();
    Connection::self();
    Connection::self().addWifi("LCA-ROBOTICA", "RedeRoboticaLca2015");
    Ota::self();
}

void loop()
{
    connectionStatus();
    Ota::self().handle();
    yield();
}
