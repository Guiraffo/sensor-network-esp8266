#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>

struct dataStruct {
    String networkName = "";
    String hostName = "";
    String macAddress = "";
    String networkIP = "0.0.0.0";

    String BSSID = "";
    float RSSI = 0.0f;

    unsigned int upTime = 0;
    unsigned int freeHeap = 0;

    float lat = -27.5965396;
    float lon = -48.5484408;
};

class Data
{
public:
    void print();

    static Data& self();

    ~Data();

    dataStruct* data;
    JsonObject* root;

private:
    void jsonSet(const char* key, const char* value);
    void updateJson();

    Data& operator = (Data& other) = delete;
    Data(const Data& other) = delete;
    Data();
};