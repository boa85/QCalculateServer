
#include "CLI/include/ArgumentParser.hpp"
#include "network/include/tcp_server.hpp"
#include <QCoreApplication>
#include <iostream>
#include <QDebug>
using namespace calc_server;
using namespace parser;
using namespace network;

int main(int argc, char *argv[]) {

    QCoreApplication application(argc, argv);
    ArgumentParser argumentParser(argc, argv);
    TcpServer *server = new TcpServer;
    server->startListen(argumentParser.getServerConfig());
    return application.exec();

}