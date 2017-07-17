//
// Created by boa on 11.07.17.
//

#include <iostream>
#include "../include/ArgumentParser.hpp"
#include <QDebug>
namespace calc_server {
    namespace parser {
        using namespace config;

        ArgumentParser::ArgumentParser(int argc, char **argv, QObject *parent)
                : QObject(parent),
                  generalDescription_("server options") {
            initDescriptions();
            startParsing(argc, argv);
        }

        ArgumentParser::~ArgumentParser() {

        }

        void ArgumentParser::initDescriptions() {
            generalDescription_.add_options()
                    ("help,h", "server options: listen addresses, port, max pending connections\n"
                            "e.g ./QCalculateServer -t start -p 7777 -a any -m 30")
                    ("type,t", po::value<std::string>(&taskType_), "start")
                    ("addresses,a", po::value<std::string>(&addresses_),
                     "listen addresses: any, anyv4, anyv6, localhost")
                    ("port,p", po::value<unsigned>(&port_),
                     " listen port: >= 1001, by default = 7777 ")
                    ("max,m", po::value<unsigned>(&maxPendingConnections_),
                     "max pending connections: by default = 30");

        }

        void ArgumentParser::startParsing(int argc, char *argv[]) {
            po::variables_map vm;
            po::parsed_options parsed =
                    po::command_line_parser(argc, argv).
                            options(generalDescription_).
                            allow_unregistered().run();
            po::store(parsed, vm);
            po::notify(vm);
            if (taskType_ == config::START) {
                po::store(po::parse_command_line(argc, argv, generalDescription_), vm);
                if (addresses_ == config::ANY) {
                    listenAddresses_ = LISTEN_ADDRESSES::ANY;
                } else if (addresses_ == config::ANY_IPV4) {
                    listenAddresses_ = LISTEN_ADDRESSES ::ANY_IPV4;
                } else if (addresses_ == config::ANY_IPV6) {
                    listenAddresses_ = LISTEN_ADDRESSES::ANY_IPV6;
                } else if (addresses_ == config::LOCAL_HOST) {
                    listenAddresses_ = LISTEN_ADDRESSES::LOCAL_HOST;
                } else {
                    qWarning() << QString("unknown value for listening to hosts, set default value ANY");
                    listenAddresses_ = LISTEN_ADDRESSES::ANY;
                }
                if (port_ < MIN_PORT) {
                    qWarning() << QString("All ports less than 1000 "
                                                  "are used by the operating system,"
                                                  " set default value %1").arg(config::DEFAULT_PORT);
                    port_ = config::DEFAULT_PORT;
                }
                if (maxPendingConnections_ <= 0) {
                    maxPendingConnections_ = config::DEFAULT_MAX_PENDING_CONNECTIONS;
                }
            } else if (taskType_ == config::HELP) {
                std::cout << "GENERAL HELP" << std::endl << generalDescription_;
                return;
            } else {
                std::cout << "unknown argument, see help " << std::endl << generalDescription_;
            }
        }
    }//namespace parser
}//namespace calc_server


