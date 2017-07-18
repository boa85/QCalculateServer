//

#pragma once

#include <QObject>
#include "../../config/include/config.hpp"
#include <QStack>
using namespace calc_server;
using namespace config;
namespace calc_server {
    namespace calculator {
        class Calculator : public QObject {
            Q_OBJECT
        public:
            Calculator(QObject *parent = Q_NULLPTR);

            virtual  ~Calculator();

        public Q_SLOTS:
            void calculate(const QStringList &expression);

        Q_SIGNALS:

            void calculateResult(const CalculationStatus status, const QString &result);

        private:
            QStack stack_;
            QStack operatorStack_;
        };

    }
}




