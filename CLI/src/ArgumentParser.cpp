//
// Created by boa on 11.07.17.
//

#include <iostream>
#include "../include/ArgumentParser.hpp"

namespace calc_server {
    namespace parser {
        using namespace config;

        void ArgumentParser::initDescriptions() {
            generalDescription_.add_options()
                    ("help,h", "Show help");
            serverSettingsDescription_.add_options()
                    ("port,P", po::value<unsigned>(), "port number to listen")
                    ("addresses,A", po::value<std::string>(&listenAddresses_), "any, anyv4, anyv6, localhost")
                    ("max_con,M", po::value<unsigned>(), "max pending connections");

        }

        ArgumentParser::ArgumentParser(int argc, char **argv)
                : generalDescription_("General description"),
                  serverSettingsDescription_("server settings") {
            initDescriptions();
        }

        ArgumentParser::~ArgumentParser() {

        }

        void ArgumentParser::startParsing(int argc, char **argv) {
            try {
                po::parsed_options parsedOptions = po::command_line_parser(argc, argv).options(
                        generalDescription_).allow_unregistered().run();

                po::store(parsedOptions, variablesMap_);
                po::notify(variablesMap_);
                generalDescription_.add(serverSettingsDescription_);
                po::store(po::parse_command_line(argc, argv, generalDescription_), variablesMap_);

                if (listenAddresses_ == config::HELP) {
                    std::cout << "general help " << generalDescription_ << std::endl;
                    return;
                }

                if ((listenAddresses_ == config::ANY)
                    OR (listenAddresses_ == config::ANY_IPV4)
                    OR (listenAddresses_ == config::ANY_IPV6)
                    OR (listenAddresses_ == config::LOCAL_HOST)) {
                    prepareSettings(variablesMap_, listenAddresses_);
                } else {
                    std::cout << "unknown parameters , " << listenAddresses_ << " see help" << std::endl;
                    std::cout << generalDescription_ << std::endl;
                }
            } catch (std::exception &exception) {
                std::cout << "error\t" << exception.what() << std::endl;
                std::cout << generalDescription_ << std::endl;
            }

        }

        void ArgumentParser::prepareSettings(const boost::program_options::variables_map &vm,
                                             const std::string &listenAddresses) {
            ServerSettings settings;

            if (listenAddresses == config::ANY) {
                settings.addresses = LISTEN_ADDRESSES::ANY;
            } else if (listenAddresses == config::LOCAL_HOST) {
                settings.addresses = LISTEN_ADDRESSES::LOCAL_HOST;
            } else if (listenAddresses == config::ANY_IPV6) {
                settings.addresses = LISTEN_ADDRESSES::ANY_IPV6;
            } else if (listenAddresses == config::ANY_IPV4) {
                settings.addresses = LISTEN_ADDRESSES::ANY_IPV4;
            } else {
                settings.addresses = LISTEN_ADDRESSES::ANY;
            }
            if (vm.count(config::PORT)) {
                auto port = vm[config::PORT].as<unsigned>();
                (port > config::MIN_PORT) ? settings.port = port
                                          : throw std::invalid_argument("invalid port value, see help");
            }
            if (vm.count(config::MAX_PENDING_CONNECTIONS)) {
                auto connections = vm[config::MAX_PENDING_CONNECTIONS].as<unsigned>();
                (connections > 0) ? settings.maxPendingConnections = connections
                                  : settings.maxPendingConnections = 30;//30 it is not magic number,
                // this is the default value for QTcpServer
            }
            serverSettings(settings);
        }
    }
}
