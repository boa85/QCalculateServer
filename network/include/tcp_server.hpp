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

            void calculationsResult(const CalculationStatus status,const QString &result);

            void newCalculateExpression(const QStringList &expression);
        public slots:

            void startListen(std::tuple<LISTEN_ADDRESSES, unsigned int, unsigned int> settings);
        private:
            void incomingConnection(qintptr socketId);

            QMap<quintptr, ClientSocket *> socketMap_;


        };
    }//namespace network
}//namespace calc_server

