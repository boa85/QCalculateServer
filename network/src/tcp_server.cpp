#include "../include/tcp_server.hpp"
#include <QTime>
#include <QDataStream>

namespace calc_server {
    namespace network {

        void TcpServer::incomingConnection(qintptr socketId) {
            ClientSocket *socket = new ClientSocket(Q_NULLPTR);
            socket->setSocketDescriptor(socketId);
            socketMap_.insert(socketId, socket);
            connect(this, &TcpServer::calculationsResult, socket, [socket](const QString &res) {
                QByteArray block;
                QDataStream out(&block, QIODevice::WriteOnly);
                out.setVersion(QDataStream::Qt_4_3);
                out << quint16(0) << res;
                out.device()->seek(0);
                out << quint16(block.size() - sizeof(quint16));
                socket->write(block);
            });
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

        TcpServer::~TcpServer() {

        }
    }
}