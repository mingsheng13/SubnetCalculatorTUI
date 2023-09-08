#include <string>

#include "ftxui/dom/elements.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui-ip-input/ipv4.hpp"

#include "IPV4.hpp"

using namespace ftxui;

Component display()
{
    class IP : public ComponentBase
    {
    public:
        IP(){Add(container);}

        IPV4 ipv4;
        std::string networkId;
        std::string broadcastId;
        std::string hostStartId;
        std::string hostEndId;
        std::string hostCount;
        std::string usableHostCount;
        std::string ipAddr;
        std::string subnetAddr;

        std::function<void()> enter()
        {
            return [&]
            {
                ipv4.setIp(ipAddr);
                ipv4.setSubnet(subnetAddr);
                ipv4.update();
                networkId = IPV4::to_string(ipv4.getNetworkId());
                broadcastId = IPV4::to_string(ipv4.getBroadcastId());
                hostStartId = IPV4::to_string(ipv4.getHostsId().startHost);
                hostEndId = IPV4::to_string(ipv4.getHostsId().endHost);
                hostCount = std::to_string(ipv4.getNumberOfHosts());
                usableHostCount = std::to_string(ipv4.getUsableNumberOfHosts());
            };
        };

        Decorator inputStyle = size(WIDTH, EQUAL, 16);
        Component ipInput = InputIPV4(&ipAddr);
        Component subnetInput = InputIPV4(&subnetAddr);
        Component enterButton = Button("↵", enter(), ButtonOption::Ascii());

        Component container = Container::Horizontal(
                {
                        ipInput,
                        subnetInput,
                        enterButton
                });

        Element Render() override
        {
            return vbox(
            {
                hbox(
                {
                    hbox({text("ip: "), ipInput->Render()}),
                    separatorEmpty() | flex,
                    hbox({text("subnet: "), subnetInput->Render()}),
                    separatorEmpty() | flex,
                    enterButton->Render()
                }) | border,
                vbox(
                {
                    text("IP:                    " + ipAddr),
                    text("SUBNET:                " + subnetAddr),
                    text("NETWORK ID:            " + networkId),
                    text("BROADCAST ID:          " + broadcastId),
                    text("HOST START:            " + hostStartId),
                    text("HOST END:              " + hostEndId),
                    text("HOST COUNT:            " + hostCount),
                    text("USABLE HOST COUNT:     " + usableHostCount)
                }) | border
            });
        }

        bool Focusable() const override
        {
            return true;
        }
    };
    return Make<IP>();
}

int main()
{
    auto screen = ScreenInteractive::TerminalOutput();
    auto output = display() | size(WIDTH, EQUAL, 48);
    screen.Loop(output);
    return 0;
}