#include "data.h"
#include "debug.h"

Data::Data() :
    data(new dataStruct)
{
    debug("Starting Data.");
    print();
}

void Data::print()
{
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

    string.concat("\n\rupTime : ");
    string.concat(data->upTime);
    string.concat(" ms");

    debug("%s", string.c_str());
}

Data& Data::self()
{
    static Data self;
    return self;
}

Data::~Data()
{
}