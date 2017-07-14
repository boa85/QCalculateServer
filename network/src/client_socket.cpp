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

        }
    }
}
