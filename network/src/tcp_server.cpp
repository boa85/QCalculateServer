#include "../include/tcp_server.hpp"
#include "../include/client_socket.hpp"

namespace calc_server {
    namespace network {

        void TcpServer::incomingConnection(qintptr socketId) {
            ClientSocket *socket = new ClientSocket;
            socket->setSocketDescriptor(socketId);
            
        }

        TcpServer::TcpServer(QObject *parent) : QTcpServer(parent) {

        }

        void TcpServer::startListen(std::tuple<LISTEN_ADDRESSES, unsigned int, unsigned int> settings) {
            auto addresses = std::get<0>(settings);
            auto port = std::get<1>(settings);
            auto maxConnections = std::get<2>(settings);
            setMaxPendingConnections(maxConnections);
            switch (addresses) {
                case LISTEN_ADDRESSES::ANY:
                    listen(QHostAddress::Any, port);
                    break;
                case LISTEN_ADDRESSES::LOCAL_HOST:
                    listen(QHostAddress::LocalHost, port);
                    break;
                case LISTEN_ADDRESSES::ANY_IPV4:
                    listen(QHostAddress::AnyIPv4, port);
                    break;
                case LISTEN_ADDRESSES::ANY_IPV6:
                    listen(QHostAddress::AnyIPv6, port);
                    break;
                case LISTEN_ADDRESSES::UNKNOWN:
                    throw std::invalid_argument("unknown addresses value");
            }
        }
    }
}