#include <Arduino.h>
#include "ota.h"

uint Ota::port = 5222;

Ota::Ota()
{
    debug("Starting OTA.");

    ArduinoOTA.setPort(port);

    ArduinoOTA.onStart([ = ]() {
        debug("START");
    });
    ArduinoOTA.onEnd([ = ]() {
        debug("END");
    });
    ArduinoOTA.onProgress([ = ](unsigned int progress, unsigned int total) {
        debug("Upload Progress: %d \%", (progress / (total / 100)));
    });
    ArduinoOTA.onError([ = ](ota_error_t error) {
        debug("ERROR");
    });
    ArduinoOTA.begin();
}

void Ota::handle()
{
    ArduinoOTA.handle();
}

Ota& Ota::self()
{
    static Ota self;
    return self;
}

Ota::~Ota()
{
}