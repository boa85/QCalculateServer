#include "../include/tcp_server.hpp"
#include <QTime>
#include <QDataStream>
#include <iostream>

namespace calc_server {
    namespace network {

        void TcpServer::incomingConnection(qintptr socketId) {
            qDebug() << "new connection";
            ClientSocket *socket = new ClientSocket(this);
            socket->setSocketDescriptor(socketId);
            connect(socket, &ClientSocket::newCalculateExpression, this, &TcpServer::newCalculateExpression);
            connect(this, &TcpServer::calculationsResult, this,
                    [socket](const CalculationStatus status, const QString &res) {
                        QByteArray block;
                        QDataStream out(&block, QIODevice::WriteOnly);
                        out.setVersion(QDataStream::Qt_4_3);
                        out << quint16(0) << status << res;
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
            QHostAddress address;
            switch (addresses) {
                case LISTEN_ADDRESSES::ANY:
                    address = QHostAddress::Any;
                    break;
                case LISTEN_ADDRESSES::LOCAL_HOST:
                    address = QHostAddress::LocalHost;
                    break;
                case LISTEN_ADDRESSES::ANY_IPV4:
                    address = QHostAddress::AnyIPv4;
                    break;
                case LISTEN_ADDRESSES::ANY_IPV6:
                    address = QHostAddress::AnyIPv6;
                    break;
            }
            listen(address, (quint16) port) ?
            qDebug() << QString("server started port %1").arg(serverPort()) :
            qWarning() << QString("Failed to bind to port, %1 ").arg(errorString()) << "\n";
        }

        TcpServer::~TcpServer() {
            for (auto socket : findChildren<ClientSocket *>()) {
                socket->close();
            }
        }
    }//namespace network
}//namespace calc_server
