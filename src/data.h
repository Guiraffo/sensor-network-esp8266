#pragma once
#include <Arduino.h>

struct dataStruct {
    String networkName = "";
    String hostName = "";
    String macAddress = "";
    String networkIP = "0.0.0.0";

    String BSSID = "";
    float RSSI = 0.0f;

    unsigned int upTime = 0;
    unsigned int otaProgress = 0; // ota progress
};

class Data
{
public:
    void print();

    static Data& self();

    ~Data();

    dataStruct* data;

private:
    Data& operator = (Data& other) = delete;
    Data(const Data& other) = delete;
    Data();
};