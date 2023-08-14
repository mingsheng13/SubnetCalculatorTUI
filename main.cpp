#include <iostream>
#include <string>

#include "ftxui/dom/elements.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"

#include "IPV4.h"

using namespace ftxui;


ButtonOption SimpleButton() {
    ButtonOption option;
    option.transform = [](const EntryState &s) {
        return s.focused ? text(" " + s.label + " ") | inverted
                         : text("[" + s.label + "]");
    };
    return option;
}

ButtonOption myButton()
{
    ButtonOption o;
//    o = ButtonOption::Animated(Color::Default, Color::White, Color::Default, Color::Red);
    o = ButtonOption::Animated(Color::Red);
    o.transform = [](const EntryState &s) {
        return s.focused ? text(" " + s.label + " ") | inverted
                         : text("[" + s.label + "]");
    };
    return o;
}

Component display()
{
    class IP : public ComponentBase
    {
    public:
        IP()
        {
            Add(container);
        }

        IPV4 ipv4;
        std::string networkId;
        std::string broadcastId;
        std::string hostStartId;
        std::string hostEndId;
        std::string hostCount;
        std::string usableHostCount;
        std::string ipAddr;
        std::string subnetAddr;

        ButtonOption style = ButtonOption::Animated(Color::Default, Color::White, Color::Default, Color::Red);

        Component ipInput = Input(&ipAddr, "....") | size(WIDTH, EQUAL, 16);
        Component subnetInput = Input(&subnetAddr, "....") | size(WIDTH, EQUAL, 16);
        Component enterButton = Button("↵", [&]
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
        }, ButtonOption::Ascii());

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
                   text("ip:                    " + ipAddr),
                   text("subnet:                " + subnetAddr),
                   text("network id:            " + networkId),
                   text("broadcast id:          " + broadcastId),
                   text("host start id:         " + hostStartId),
                   text("host end id:           " + hostEndId),
                   text("host count:            " + hostCount),
                   text("usable host count:     " + usableHostCount)

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