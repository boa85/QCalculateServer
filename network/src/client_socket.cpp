//

#include "../include/client_socket.hpp"
#include "../../config/include/config.hpp"
#include <QDataStream>

using namespace calc_server;
using namespace config;
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
            qDebug() << "readClient";
            QDataStream in(this);
            in.setVersion(QDataStream::Qt_4_8);
            if (nextBlockSize_ == 0) {
                if (bytesAvailable() < sizeof(quint16)) {
                    return;
                }
                in >> nextBlockSize_;

            }
            if (bytesAvailable() < nextBlockSize_) {
                qDebug() << QString("bytesAvailable =  %1 %2").arg(bytesAvailable()).arg(errorString());
                return;
            }
            QString name;
            in >> name;
            setSocketName(name);
            QStringList data;
            in >> data;
            emit newCalculateExpression(data);
            sendResult("ok");
            qDebug() << "name = " << name << " data = " << data;
        }

        void ClientSocket::sendResult(const QString &result) {
            QByteArray block;
            QDataStream out(&block, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_4_3);
            out << quint16(0) << CalculationStatus::SUCCESS << result;
            out.device()->seek(0);
            out << quint16(block.size() - sizeof(quint16));
            write(block);

        }
    }//namespace network
}//namespace calc_server
