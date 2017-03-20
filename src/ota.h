#pragma once

#include <Arduino.h>
#include <ArduinoOTA.h>
#include <WiFiUdp.h>
#include "debug.h"

class Ota
{
public:
    void handle();

    enum States {
        START,
        DOWNLOADING,
        FINISHED,
        ERROR,
    };

    static Ota& self();
    ~Ota();

private:
    Ota& operator = (Ota& other) = delete;
    Ota(const Ota& other) = delete;
    Ota();

    static uint port;
};