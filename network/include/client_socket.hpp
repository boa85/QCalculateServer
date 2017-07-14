//

#pragma once
#include <QTcpSocket>


namespace calc_server {
    namespace network {

        class ClientSocket : public QTcpSocket
        {
        Q_OBJECT
        public:
            /**
             * @brief ClientSocket - default constructor
             * @param parent
             */
            explicit ClientSocket(QObject *parent = Q_NULLPTR);

            virtual ~ClientSocket();

            /**
             * @brief socketName
             * @return  getter
             */
            const QString socketName() const { return socketName_; }

            /**
             * @brief setSocketName - setter
             * @param socketName new socketName
             */
            void setSocketName(const QString &socketName) { socketName_ = socketName; }
        signals:

            void newCalculateExpression(const QString &expression);

            void disconnects(const QString &name);

        public slots:

        private slots:
            void readClient();
        private:
            quint16 nextBlockSize_;
            QString socketName_;
        };

    }
}

