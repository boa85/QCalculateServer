//

#include "../include/calculator.hpp"
#include <QDebug>
namespace calc_server {
    namespace calculator {

        Calculator::Calculator(QObject *parent) : QObject(parent) {

        }

        Calculator::~Calculator() {

        }

        void Calculator::calculate(const QStringList &expression) {
            qDebug() << "original expression";
            QStringList copy(expression);
            while (!copy.isEmpty()) {
                QString s = copy.takeFirst();
                qDebug() << copy;
            }
        }

        int Calculator::getPrioritet(const char operator_) {
            switch (operator_) {
                case '*':
                case '/':
                    return 1;
                case '+':
                case '-':
                    return 2;
                default:
                    return -1;
            }
        }

        bool Calculator::isOperator(const char operator_) {
            switch (operator_) {
                case '*':
                case '/':
                case '+':
                case '-':
                    return true;
                default:
                    return false;
            }
        }
    }
}
