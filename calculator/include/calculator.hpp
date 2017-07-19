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

            int getPriority(const char operator_);

            bool isOperator(const char operator_);
            /**
             * @brief convertToRpn - convert expression in infix notation to Reverse Polish notation
             * @param expression expression in infix notation
             * @return expression in Reverse Polish notation
             */
            QStringList convertToRpn(const QStringList &expression);
        };

    }
}
