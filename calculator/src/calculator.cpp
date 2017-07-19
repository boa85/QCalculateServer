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
            if (tmp.isEmpty()) {
                emit calculateResult(CalculationStatus::FAILED, QString("calculated error"));
                return;
            }
            QStack<QString> stack;
            double res = .0;
            while (!tmp.isEmpty()) {
                QString s = tmp.takeFirst();//get next token
                if (!s.isEmpty()) {
                    if (s.length() == 1) {
                        char c = s.toStdString()[0];
                        if (isOperator(c)) {//if token is the operator
                            if (stack.size() >= 2) {//предполагаем, что унарных операторов нет
                                double op1 = stack.pop().toDouble();//take two operators
                                double op2 = stack.pop().toDouble();
                                switch (c) {//calculate
                                    case '*':
                                        res = op1 * op2;
                                        break;
                                    case '/':
                                        res = op2 / op1;
                                        break;
                                    case '+':
                                        res = op1 + op2;
                                        break;
                                    case '-':
                                        res = op2 - op1;
                                        break;
                                    default:
                                        emit calculateResult(CalculationStatus::FAILED,
                                                             QString("calculated error, unknown operator %1").arg(c));
                                        return;
                                }
                                stack.push(QString::number(res));//push calculation result to stack
                            } else {
                                emit calculateResult(CalculationStatus::FAILED,
                                                     QString("calculated error, miss math parameter for binary operator"));
                                return;
                            }
                        } else {//if not operator
                            stack.push(s);//push to stack
                        }
                    } else {
                        stack.push(s);//push to stack
                    }
                } else {
                    emit calculateResult(CalculationStatus::FAILED, QString("calculated error"));//тута можно просто
                    // прервать оперцию, а можно запросить следующий токен, что сильно усложнит код
                    return;
                }
            }
            emit calculateResult(CalculationStatus::SUCCESS, QString::number(res));//
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

            QStringList copy(expression);//create copy of original expression
            while (!copy.isEmpty()) {//while not expression empty
                QString s = copy.takeFirst();//take next token

                if (!s.isEmpty()) {
                    if (s.length() > 1) {//т.к. используются только односимвольные операторы, считаем что
                        out_ << s;//все что больше одного символа
                    } else {
                        char o = s.toStdString()[0];//take first symbol
                        if (isOperator(o)) {//if token is operator
                            if (operatorStack_.isEmpty()) {
                                operatorStack_.push(o);//push to operator stack
                            } else if (getPriority(operatorStack_.first()) < getPriority(o)) {//equal operator priority
                                out_ << QString(operatorStack_.pop());//move the operator with a higher priority to the output array
                                operatorStack_.push(o);//put the operator with a lower priority on the stack
                            } else {
                                operatorStack_.push(o);//put the operator on the stack
                            }
                        } else {//if token is not operator
                            out_ << s;//move to output array
                        }
                    }
                    qDebug() << "out = " << out_;
                    qDebug() << "stack = " << operatorStack_;
                } else {
                    qWarning() << "empty token, operation aborted";
                    return QStringList();
                }
            }
            while (!operatorStack_.isEmpty()) {
                out_ << QString(operatorStack_.pop());//move the remaining operators to the output array
            }

            return out_;
        }
    }
}
