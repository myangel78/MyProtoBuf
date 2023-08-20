#pragma once

#include "Network_global.h"
#include <Platform.h>
#include <NetworkDefs.h>
#include <TCPServer.h>
#include <TCPClient.h>

#include <list>
#include <memory>

class NETWORK_EXPORT Network
{
public:
    Network() { }
    ~Network() { }

    void initialize();
    void uninitialize();

    std::shared_ptr<TCPServer>& createTCPServer(Mode mode = Mode::Blocking);
    std::shared_ptr<TCPClient>& createTCPClient();

protected:

private:
    std::list<std::shared_ptr<TCPServer>> m_tcpServers;
    std::list<std::shared_ptr<TCPClient>> m_tcpClients;
};
