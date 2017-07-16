//

#include "../include/client_socket.hpp"
#include <QDataStream>

namespace calc_server {
    namespace network {

        ClientSocket::ClientSocket(QObject *parent) : QTcpSocket(parent) {
            connect(this, &ClientSocket::readyRead, this, &ClientSocket::readClient);
            connect(this, &QAbstractSocket::disconnected, this, &QObject::deleteLater);//see Qt official documentation
        }

        ClientSocket::~ClientSocket() {
            auto str = "Client\t" + socketName_ + "\thas disconnected";
            emit disconnects(str);
        }

        void ClientSocket::readClient() {
            qDebug() << "new connection";
            QDataStream in(this);
            in.setVersion(QDataStream::Qt_4_8);
            if (nextBlockSize_ == 0) {
                if (bytesAvailable() < sizeof(quint16)) {
                    return;
                }
                in >> nextBlockSize_;

            }
            if (bytesAvailable() < nextBlockSize_) {
                return;
            }
            QString name;
            in >> name;
            QStringList data;
            in >> data;
            sendResult("0");
            qDebug() << "name = " << name << " data = " << data;
        }

        void ClientSocket::sendResult(const QString &result) {
            QByteArray block;
            QDataStream out(&block, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_4_3);
            out << quint16(0) << 0 << result;
            out.device()->seek(0);
            out << quint16(block.size() - sizeof(quint16));
            write(block);

        }
    }//namespace network
}//namespace calc_server
