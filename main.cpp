
#include "CLI/include/ArgumentParser.hpp"
#include "network/include/tcp_server.hpp"
#include <QCoreApplication>
using namespace calc_server;
using namespace parser;
using namespace network;

int main(int argc, char *argv[]) {
    QCoreApplication application(argc, argv);
    ArgumentParser argumentParser(argc, argv);
    TcpServer server;
    server.startListen(argumentParser.getServerConfig());
    return application.exec();

}