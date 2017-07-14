//

#pragma once
#include <QTcpServer>
#include "../../config/include/config.hpp"
#include "client_socket.hpp"

using namespace calc_server;
using namespace config;
namespace calc_server {
    namespace network {
        class TcpServer : public QTcpServer
        {
        Q_OBJECT
        public:
            explicit TcpServer(QObject *parent = Q_NULLPTR);

            virtual ~TcpServer();
        signals:

            void calculationsResult(const QString &result);

        public slots:

            void startListen(std::tuple<LISTEN_ADDRESSES, unsigned int, unsigned int> settings);
        private:
            void incomingConnection(qintptr socketId);

            QMap<quintptr, ClientSocket *> socketMap_;
        };
    }
}
