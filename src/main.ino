#include <Arduino.h>
#include <Thread.h>
#include <ThreadController.h>

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

Thread printDataThread = Thread();
Thread connectionThread = Thread();
ThreadController groupOfThreads = ThreadController();

void setup()
{
    hardwareInit();

    //Start data thread
    Data::self();
    printDataThread.onRun([]() {
        const static unsigned long startTime = micros();
        Data::self().data->freeHeap = ESP.getFreeHeap();
        Data::self().data->upTime = (micros() - startTime)/1e3;
        Data::self().print();
    });
    printDataThread.setInterval(1000);

    //Start connection manager thread
    Connection::self();
    Connection::self().setData(Data::self().data);
    if(Connection::self().scanForNetwork("provant")) {
        debug("provant network found, set Slave Mode");
        Connection::self().addWifi("provant");
    } else {
        debug("provant network not found, set Master Mode");
        const static char* apname = "provant";
        Connection::self().wifi()->softAP(apname);
    }

    connectionThread.onRun([]() {
        if(Connection::self().run()) {
            digitalWrite(LED, !digitalRead(LED));
        }
    });
    connectionThread.setInterval(1000);

    //Add all threads in ThreadController
    groupOfThreads.add(&printDataThread);
    groupOfThreads.add(&connectionThread);

    //Start OTA
    Ota::self();
}

void loop()
{
    groupOfThreads.run();
    Ota::self().handle();
    yield();
}