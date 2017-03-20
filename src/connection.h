#pragma once

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>

class Connection
{
public:

    void addWifi(String ssid, String password);

    ESP8266WiFiClass* wifi();

    void run();

    static Connection& self();

    ~Connection();

    bool getStatus();

private:
    Connection& operator = (Connection& other) = delete;
    Connection(const Connection& other) = delete;
    Connection();

    ESP8266WiFiMulti* WiFiMulti;
    bool connected;
};