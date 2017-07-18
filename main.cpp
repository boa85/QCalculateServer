
#include "CLI/include/ArgumentParser.hpp"
#include "network/include/tcp_server.hpp"
#include "calculator/include/calculator.hpp"
#include <QCoreApplication>
using namespace calc_server;
using namespace parser;
using namespace network;
using namespace calculator;
int main(int argc, char *argv[]) {
    QCoreApplication application(argc, argv);
    ArgumentParser argumentParser(argc, argv);
    TcpServer *server = new TcpServer;
    server->startListen(argumentParser.getServerConfig());
    Calculator *calc = new Calculator;
    QObject::connect(server, &TcpServer::newCalculateExpression, calc, &Calculator::calculate);
    QObject::connect(calc, &Calculator::calculateResult, server, &TcpServer::calculationsResult);
    return application.exec();

}