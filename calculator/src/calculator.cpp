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
            QStringList tmp = convertToRpn(expression);
            QStack<QString> stack;
            double res = .0;
            while (!tmp.isEmpty()) {
                QString s = tmp.takeFirst();
                if (s.length() == 1) {
                    char c = s.toStdString()[0];
                    if (isOperator(c)) {
                        if (stack.size() >= 2) {
                            double op1 = stack.pop().toDouble();
                            double op2 = stack.pop().toDouble();
                            switch (c) {
                                case '*':
                                    res = op1 * op2;
                                    break;
                                case '/':
                                    res = op2 / op1;
                                    qDebug() << "res = op1 / op2" << res;
                                    break;
                                case '+':
                                    res = op1 + op2;
                                    break;
                                case '-':
                                    res = op2 - op1;
                                    break;
                                default:
                                    emit calculateResult(CalculationStatus::FAILED, QString("calculated error"));
                                    return;
                            }
                            stack.push(QString::number(res));
                        } else {
                            emit calculateResult(CalculationStatus::FAILED, QString("calculated error"));
                            return;
                        }
                    } else {
                        stack.push(s);
                    }
                } else {
                    stack.push(s);
                }
            }
            emit calculateResult(CalculationStatus::SUCCESS, QString::number(res));
        }

        int Calculator::getPriority(const char operator_) {
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

        QStringList Calculator::convertToRpn(const QStringList &expression) {
            qDebug() << "original expression" << expression;
            QStringList out_;//сделал локальными переменными, т.к. необходимо каждый раз очищать
            QStack<char> operatorStack_;//можно забыть

            QStringList copy(expression);
            while (!copy.isEmpty()) {
                QString s = copy.takeFirst();
                if (s.length() > 1) {
                    out_ << s;
                } else {
                    char o = s.toStdString()[0];
                    if (isOperator(o)) {
                        if (operatorStack_.isEmpty()) {
                            operatorStack_.push(o);
                        } else if (getPriority(operatorStack_.first()) < getPriority(o)) {
                            out_ << QString(operatorStack_.pop());
                            operatorStack_.push(o);
                        } else {
                            operatorStack_.push(o);
                        }
                    } else {
                        out_ << s;
                    }
                }
                qDebug() << "out = " << out_;
                qDebug() << "stack = " << operatorStack_;
            }
            while (!operatorStack_.isEmpty()) {
                out_ << QString(operatorStack_.pop());
            }
            qDebug() << "out2 = " << out_;
            return out_;
        }
    }
}
