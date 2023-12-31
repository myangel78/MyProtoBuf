﻿#include "Client.h"

#include <Network.h>
#include <iostream>
#include <thread>
#include <cstdint>
#include <array>
#include "query.pb.h"
#include "ProtocCodec.h"
#include <memory>
#include "dispatcher.h"


using namespace std::chrono_literals;
struct MessageHeader
{
    std::uint16_t m_id;
    std::uint16_t m_size;
};


Client::Client()
{
    StopThread();
}

#if 0
void Client::ThreadHandleFunc()
{
    try
    {
        std::unique_ptr<Network> network(new Network());
        network->initialize();

        try
        {
            std::shared_ptr<TCPClient> client;
            TCPSocket socket;
            TCPData buf;

            client = network->createTCPClient();
            //socket = client->connect(std::string("MathTixWinDev"), 48000, Mode::Nonblocking);
            socket = client->connect(std::string("localhost"), 48000, Mode::Nonblocking);
//            socket = client->connect(std::string(""), 48000, Mode::Nonblocking);

            std::array<char, 256> buffer;
            MessageHeader* headerPtr = reinterpret_cast<MessageHeader*>(&buffer[0]);
            headerPtr->m_id = 1;
            headerPtr->m_size = 3;
            buffer[4] = 'F';
            buffer[5] = 'u';
            buffer[6] = 'n';

            socket.send(&buffer[0], 7);
            socket.shutdown();

            // Non-blocking update for socket to server.
            /********************************************************************************/
            bool gotTheMessage = false;
            do {
                std::cout << "Waiting for server to send data" << std::endl;
                std::this_thread::sleep_for(1s);

                if (socket.isDataAvailable())
                {
                    do {
                        buf = socket.receive();
                        if (buf.getLength() == TCPData::DATA_PENDING)
                        {
                            break;
                        }
                        else
                        {
                            std::string msg(buf.getData(), buf.getLength());
                            std::cout << msg << std::endl;
                        }
                    } while (buf.getLength() > 0);
                    gotTheMessage = true;
                }
            } while (!gotTheMessage && m_bRunning);
            /********************************************************************************/
            socket.close();
        }
        catch(std::runtime_error& rt)
        {
            std::cerr << "Client error = " << rt.what() << std::endl;
        }
        catch (std::exception e)
        {
            std::cerr << "C++ exception = " << e.what() << std::endl;
        }

        network->uninitialize();
    }
    catch (std::runtime_error& rt)
    {
        std::cerr << "Client error = " << rt.what() << std::endl;
    }
    catch (std::exception e)
    {
        std::cerr << "C++ exception = " << e.what() << std::endl;
    }
    return;
}

#else

void Client::ThreadHandleFunc()
{
    auto pProtocCodec = std::make_shared<ProtocCodec>();

    ProtobufDispatcher dispatcher;
    dispatcher.registerMessageCallback<muduo::Query>(onQuery);
    dispatcher.registerMessageCallback<muduo::Answer>(onAnswer);

    try
    {
        std::unique_ptr<Network> network(new Network());
        network->initialize();

        try
        {
            std::shared_ptr<TCPClient> client;
            TCPSocket socket;
            TCPData buf;


            muduo::Query query;
            query.set_id(1);
            query.set_questioner("Chen Shuo");
            query.add_question("Running?");
            query.PrintDebugString();
            std::cout << query.DebugString();

            client = network->createTCPClient();
            //socket = client->connect(std::string("MathTixWinDev"), 48000, Mode::Nonblocking);
            socket = client->connect(std::string("localhost"), 48000, Mode::Nonblocking);
//            socket = client->connect(std::string(""), 48000, Mode::Nonblocking);


            std::string strqueryMsg = pProtocCodec->encode(query);
            socket.send(&strqueryMsg[0], strqueryMsg.size());

            socket.shutdown();

            // Non-blocking update for socket to server.
            /********************************************************************************/
            bool gotTheMessage = false;
            do {
                std::cout << "Waiting for server to send data" << std::endl;
                std::this_thread::sleep_for(1s);

                if (socket.isDataAvailable())
                {
                    do {
                        buf = socket.receive();
                        if (buf.getLength() == TCPData::DATA_PENDING)
                        {
                            break;
                        }
                        else
                        {
                            if(buf.getLength() > 4)
                            {
                                std::string msg(buf.getData(), buf.getLength());
                                std::string submsg = msg.substr(sizeof(int32_t));
                                auto *ptr = pProtocCodec->decode(submsg);
                                ptr->PrintDebugString();
                                dispatcher.onMessage(ptr);
                            }

                        }
                    } while (buf.getLength() > 0);
                    gotTheMessage = true;
                }
            } while (!gotTheMessage && m_bRunning);
            /********************************************************************************/
            socket.close();
        }
        catch(std::runtime_error& rt)
        {
            std::cerr << "Client error = " << rt.what() << std::endl;
        }
        catch (std::exception e)
        {
            std::cerr << "C++ exception = " << e.what() << std::endl;
        }

        network->uninitialize();
    }
    catch (std::runtime_error& rt)
    {
        std::cerr << "Client error = " << rt.what() << std::endl;
    }
    catch (std::exception e)
    {
        std::cerr << "C++ exception = " << e.what() << std::endl;
    }
    return;
}


#endif

