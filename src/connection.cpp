#include "debug.h"
#include "connection.h"

Connection::Connection() :
    WiFiMulti(new ESP8266WiFiMulti), connected(false)
{
}

void Connection::addWifi(String ssid, String password)
{
    WiFiMulti->addAP(ssid.c_str(), password.c_str());
}

ESP8266WiFiClass* Connection::wifi()
{
    return &WiFi;
}

bool Connection::getStatus()
{
    debug("IP %s", wifi()->localIP().toString().c_str());
    return WiFiMulti->run() == WL_CONNECTED;
}

void Connection::run()
{
    if (getStatus()) {
        debug("Connected wifi %s", wifi()->SSID().c_str());
        debug("macAddress %s",wifi()->macAddress().c_str());
        debug("Hostname %s",wifi()->hostname().c_str());
        debug("IP %s", wifi()->localIP().toString().c_str());
        debug("BSSID %s",wifi()->BSSIDstr().c_str());
        debug("RSSI %d",wifi()->RSSI());
        return;
    }

    if (!connected) {
        debug("Starting Wifi. (Running..)");
        connected = true;
    }

    debug("NOT connected !");
}

Connection& Connection::self()
{
    static Connection self;
    return self;
}

Connection::~Connection()
{
};