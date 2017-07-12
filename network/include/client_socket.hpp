//

#pragma once
#include <QTcpSocket>


namespace calc_server {
    namespace network {

        class ClientSocket : public QTcpSocket
        {
        Q_OBJECT
        public:
            explicit ClientSocket(QObject *parent = 0);
            virtual ~ClientSocket();

        signals:
            void newClient(const QVariantList &data);
            void disconnects(const QString &name);

        public slots:
        private slots:
            void readClient();
        private:
            quint16 nextBlockSize_;
            QString sockeName_;
        };

    }
}

