#pragma once

#include <iostream>
#include <cmath>

struct UsableHost
{
    uint8_t* startHost;
    uint8_t* endHost;
};

class IPV4
{
private:
    static bool isDot(char c);
    static uint8_t* stos(const std::string& str);
    static uint8_t* inverse(const uint8_t* addr);

    uint8_t* ip;
public:
    void setIp(const std::string& ipAddr);

    void setSubnet(const std::string& subnetAddr);

private:
    uint8_t* subnet;
    uint8_t* networkId;
    uint8_t* broadcastId;
    void calculateNetworkId();
    void calculateBroadcastId();
    void calculateTotalHosts();
    UsableHost hostsId;
    uint numberOfHosts;

public:
    IPV4();
    IPV4(const std::string& ipAddr, const std::string& subnetAddr);
    uint8_t* getIp();
    uint8_t* getSubnet();
    uint8_t* getNetworkId();
    uint8_t* getBroadcastId();
    UsableHost getHostsId();
    uint getNumberOfHosts();
    uint getUsableNumberOfHosts() const;
    void update();
    static std::string to_string(uint8_t *addr);
};