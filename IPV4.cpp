#include "IPV4.h"

bool IPV4::isDot(char c)
{
    return c == '.';
}

uint8_t* IPV4::stos(const std::string& str)
{
    auto* arr = new uint8_t[4];
    int j = 0;
    std::string buf;
    for (char i : str)
    {
        if (!isDot(i))
            buf += i;

        if (isDot(i))
        {
            arr[j++] = (uint8_t)stoi(buf);
            buf.clear();
        }
    }
    arr[j] = (uint8_t)stoi(buf);
    return arr;
}

uint8_t* IPV4::inverse(const uint8_t* addr)
{
    auto* inversed = new uint8_t[4];
    for (int i = 0; i < 4; ++i)
        inversed[i] = ~(addr[i]);
    return inversed;
}

IPV4::IPV4()
{
    hostsId.startHost = new uint8_t[4];
    hostsId.endHost = new uint8_t[4];
    networkId = new uint8_t[4];
    broadcastId = new uint8_t[4];
}

IPV4::IPV4(const std::string& addr, const std::string& subnetAddr) : IPV4()
{
    ip = stos(addr);
    subnet = stos(subnetAddr);

    update();
}

void IPV4::setIp(const std::string& ipAddr)
{
    ip = stos(ipAddr);
}

void IPV4::setSubnet(const std::string& subnetAddr)
{
    subnet = stos(subnetAddr);
}

uint8_t *IPV4::getIp()
{
    return ip;
}

uint8_t *IPV4::getSubnet()
{
    return subnet;
}

uint8_t *IPV4::getNetworkId()
{
    return networkId;
}

void IPV4::calculateNetworkId()
{
    for (int i = 0; i < 4; i++)
    {
        networkId[i] = (ip[i] & subnet[i]);
    }
}

UsableHost IPV4::getHostsId()
{
    for (int i = 0; i < 4; ++i)
    {
        if (i == 3)
        {
            hostsId.startHost[i] = networkId[i] + 1;
            hostsId.endHost[i] = broadcastId[i] - 1;
        }
        else
        {
            hostsId.startHost[i] = networkId[i];
            hostsId.endHost[i] = broadcastId[i];
        }
    }
    return hostsId;
}

uint IPV4::getNumberOfHosts()
{
    return numberOfHosts;
}

uint8_t *IPV4::getBroadcastId()
{
    return broadcastId;
}

void IPV4::calculateBroadcastId()
{
    uint8_t* inversedSubnet = inverse(subnet);
    for (int i = 0; i < 4; ++i)
    {
        broadcastId[i] = (networkId[i] | inversedSubnet[i]);
    }
}

void IPV4::calculateTotalHosts()
{
    auto* addr = new uint8_t[4];

    //make a copy of subnet
    for (int i = 0; i < 4; ++i)
    {
        addr[i] = subnet[i];
    }

    uint count = 0;
    for (int i = 0; i < 4; ++i)
    {
        while (addr[i] != 0)
        {
            count++;
            addr[i] >>= 1;
        }
    }
    numberOfHosts = (uint)std::pow(2, 32 - count);
}

uint IPV4::getUsableNumberOfHosts() const
{
    uint overflowCheck = numberOfHosts - 2;
    if (overflowCheck > numberOfHosts)
        return 0;

    return numberOfHosts - 2;
}

void IPV4::update()
{
    calculateNetworkId();
    calculateBroadcastId();
    calculateTotalHosts();
}

std::string IPV4::to_string(uint8_t* addr)
{
    std::string buf;
    for (int i = 0; i < 4; ++i)
    {
        buf += std::to_string(unsigned(addr[i]));
        if (i < 3)
            buf += ".";
    }
    return buf;
}




