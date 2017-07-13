//

#pragma once
#include <QTcpServer>
#include "../../config/include/config.hpp"

using namespace calc_server;
using namespace config;
namespace calc_server {
    namespace network {
        class TcpServer : public QTcpServer
        {
        Q_OBJECT
        public:
            explicit TcpServer(QObject *parent = 0);

        signals:
            void newClient(const QVariantList &data);

        public slots:

            void startListen(std::tuple<LISTEN_ADDRESSES, unsigned int, unsigned int> settings);
        private:
            void incomingConnection(qintptr socketId);
        };
    }
}

