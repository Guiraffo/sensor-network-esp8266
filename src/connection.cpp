#include "debug.h"
#include "connection.h"

Connection::Connection() :
    WiFiMulti(new ESP8266WiFiMulti), isMaster(false), wifiAdded(false)
{
}

void Connection::addWifi(String ssid, String password = String())
{
    wifiAdded = true;
    if(password.length() != 0)
        WiFiMulti->addAP(ssid.c_str(), password.c_str());
    else
        WiFiMulti->addAP(ssid.c_str());
}

ESP8266WiFiClass* Connection::wifi()
{
    return &WiFi;
}

bool Connection::getStatus()
{
    return WiFiMulti->run() == WL_CONNECTED;
}

bool Connection::run()
{
    data->networkName = wifi()->SSID().c_str();
    data->macAddress = wifi()->macAddress().c_str();
    data->hostName = wifi()->hostname().c_str();
    data->networkIP = wifi()->localIP().toString().c_str();
    data->RSSI = wifi()->RSSI();
    data->BSSID = wifi()->BSSIDstr().c_str();
    if(wifiAdded)
        return getStatus();
    return false;
}

void Connection::setData(dataStruct* d)
{
    data = d;
}

bool Connection::scanForNetwork(const char *ssid)
{
    int numRedes = wifi()->scanNetworks();
    debug("Scan Done");
    for (int i = 0; (i < numRedes) && !isMaster; i++) {
        if(wifi()->SSID(i) == ssid) {
            isMaster = true;
        }
    }
    return isMaster;
}

Connection& Connection::self()
{
    static Connection self;
    return self;
}

Connection::~Connection()
{
};