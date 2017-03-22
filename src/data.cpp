#include "data.h"
#include "debug.h"

Data::Data() :
    data(new dataStruct)
{
    debug("Starting Data.");
    print();
}

void Data::jsonSet(const char* key, const char* value)
{
    root[0][key] = value;
}

void Data::updateJson()
{
    StaticJsonBuffer<10 * 1024> jsonBuffer;
    root = &jsonBuffer.createObject();
    jsonSet("Sensor", data->hostName.c_str());

    JsonArray& gpsJson = root->createNestedArray("gps");
    gpsJson.add(double_with_n_digits(data->upTime, 7));
    gpsJson.add(double_with_n_digits(data->lat, 7));
    gpsJson.add(double_with_n_digits(data->lon, 7));
}

void Data::print()
{
    updateJson();
    String string;
    string.concat("\n\rNetwork name : ");
    string.concat(data->networkName);
    string.concat("\n\rHost name : ");
    string.concat(data->hostName);
    string.concat("\n\rMAC address : ");
    string.concat(data->macAddress);
    string.concat("\n\rNetwork IP : ");
    string.concat(data->networkIP);

    string.concat("\n\rRSSI : ");
    string.concat(data->RSSI);
    string.concat(" dBm");

    string.concat("\n\rFree memory : ");
    string.concat(data->freeHeap);
    string.concat("\n\rupTime : ");
    string.concat(data->upTime);
    string.concat(" ms");

    debug("%s", string.c_str());
    root->prettyPrintTo(Serial);
}

Data& Data::self()
{
    static Data self;
    return self;
}

Data::~Data()
{
}