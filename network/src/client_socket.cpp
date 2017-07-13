//

#include "../include/client_socket.hpp"
namespace calc_server {
    namespace network {

        ClientSocket::ClientSocket(QObject *parent) : QTcpSocket(parent) {
            connect(this, &ClientSocket::readyRead, this, &ClientSocket::readClient);
            connect(this, &ClientSocket::disconnected, this, &ClientSocket::deleteLater);
        }

        ClientSocket::~ClientSocket() {
            auto str = "Client\t" + sockeName_ + "\thas disconnected";
            emit disconnects(str);
        }

        void ClientSocket::readClient() {
        }

    }
}
