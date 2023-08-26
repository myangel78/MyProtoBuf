#include "Server.h"
#include <Network.h>
#include <iostream>
#include <thread>
#include "query.pb.h"
#include "ProtocCodec.h"
#include "memory"
#include "dispatcher.h"


using namespace std::chrono_literals;


Server::Server()
{

}

#if 0
void Server::ThreadHandleFunc()
{

    try
    {
        std::unique_ptr<Network> network(new Network());
        network->initialize();

        try
        {
            std::shared_ptr<TCPServer> server;
            TCPSocket socket;
            std::uint16_t portNumber = 48000;

            server = network->createTCPServer(Mode::Nonblocking);
            server->bind(portNumber);
            server->listen();
            std::cout << "Server listening or port " << portNumber << std::endl;

            // Non-blocking update for listen socket
            /********************************************************************************/
            do {
                socket = server->accept();
                std::cout << "Waiting for client connection" << std::endl;
                std::this_thread::sleep_for(1s);
            } while (!socket.isValid() && m_bRunning);
            std::cout << "Client connected from " << socket.getAddress() << std::endl;
            /********************************************************************************/

            // Non-blocking update for socket to client.
            /********************************************************************************/
            TCPData buf;
            do {
                buf = socket.receive();
                std::string msg(buf.getData(), buf.getLength());
                if (buf.getLength() > 0)
                {
                    std::cout << "Received message from client: " << msg << std::endl;
                    std::string data("Here is your data");
                    socket.send(&data[0], data.length());
                }
            } while (buf.getLength() > 0);
            /********************************************************************************/

            std::cout << "Client disconnecting..." << std::endl;
            server->stopListen();
            socket.shutdown();
            socket.close();
        }
        catch(std::runtime_error& rt)
        {
            std::cerr << "Server error = " << rt.what() << std::endl;
        }
        catch (std::exception e)
        {
            std::cerr << "C++ exception = " << e.what() << std::endl;
        }

        network->uninitialize();
    }
    catch (std::runtime_error& rt)
    {
        std::cerr << "Server error = " << rt.what() << std::endl;
    }
    catch (std::exception e)
    {
        std::cerr << "C++ exception = " << e.what() << std::endl;
    }
    return;
}
#else

void Server::ThreadHandleFunc()
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
            std::shared_ptr<TCPServer> server;
            TCPSocket socket;
            std::uint16_t portNumber = 48000;

            server = network->createTCPServer(Mode::Nonblocking);
            server->bind(portNumber);
            server->listen();
            std::cout << "Server listening or port " << portNumber << std::endl;

            // Non-blocking update for listen socket
            /********************************************************************************/
            do {
                socket = server->accept();
                std::cout << "Waiting for client connection" << std::endl;
                std::this_thread::sleep_for(1s);
            } while (!socket.isValid() && m_bRunning);
            std::cout << "Client connected from " << socket.getAddress() << std::endl;
            /********************************************************************************/

            // Non-blocking update for socket to client.
            /********************************************************************************/
            TCPData buf;
            do {
                buf = socket.receive();
                std::string msg(buf.getData(), buf.getLength());
                if (buf.getLength() > 0)
                {

                    std::string buf = msg.substr(sizeof(int32_t));
                    auto *ptr = pProtocCodec->decode(buf);
                    ptr->PrintDebugString();
                    dispatcher.onMessage(ptr);

                    muduo::Answer answer;
                    answer.set_id(1);
                    answer.set_questioner("Chen Shuo");
                    answer.set_answerer("blog.csdn.net/Solstice");
                    answer.add_solution("Jump!");
                    answer.add_solution("Win!");


                    std::cout << "Received message from client: " << msg << std::endl;
                    std::string stranswer = pProtocCodec->encode(answer);
                    socket.send(&stranswer[0], stranswer.length());


//                    std::string data("Here is your data");
//                    socket.send(&data[0], data.length());
                }
            } while (buf.getLength() > 0);
            /********************************************************************************/

            std::cout << "Client disconnecting..." << std::endl;
            server->stopListen();
            socket.shutdown();
            socket.close();
        }
        catch(std::runtime_error& rt)
        {
            std::cerr << "Server error = " << rt.what() << std::endl;
        }
        catch (std::exception e)
        {
            std::cerr << "C++ exception = " << e.what() << std::endl;
        }

        network->uninitialize();
    }
    catch (std::runtime_error& rt)
    {
        std::cerr << "Server error = " << rt.what() << std::endl;
    }
    catch (std::exception e)
    {
        std::cerr << "C++ exception = " << e.what() << std::endl;
    }
    return;
}

#endif
