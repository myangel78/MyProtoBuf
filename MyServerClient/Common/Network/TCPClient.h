﻿#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include "Network_global.h"
#include <Platform.h>
#include <NetworkDefs.h>
#include <TCPSocket.h>


class NETWORK_EXPORT TCPClient
{
	friend class Network;
protected:
	TCPClient() : m_mode(Mode::Blocking) {}

public:
	~TCPClient() {}

	TCPSocket connect(
		std::string const& host,
		std::uint16_t port,
		Mode mode = Mode::Blocking
		);

protected:

private:
	Mode m_mode;
};

#endif // TCP_CLIENT_H
