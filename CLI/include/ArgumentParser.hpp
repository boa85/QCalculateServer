//
// Created by boa on 11.07.17.
//

#pragma once
#include <boost/program_options.hpp>
#include <boost/signals2.hpp>
#include "../../config/include/config.hpp"

namespace calc_server {
    namespace parser {
        using namespace config;
        namespace po=boost::program_options;
        class ArgumentParser {
        public:
            /**
             * @brief ArgumentParser
             * @param argc count of arguments
             * @param argv values of the arguments
             */
            ArgumentParser(int argc, char *argv[]);

            virtual ~ArgumentParser();

            /**
             * использовал бустовские сигналы для того, чтобы не смешивать все в одну кучу
             */
            boost::signals2::signal<void(std::tuple<LISTEN_ADDRESSES, unsigned int, unsigned int>)> serverSettings;

        private:
            /**
             * @brief generalDescription_ -  set of option descriptions. This provides convenient interface for
             * adding new option (the add_options) method, and facilities to search
             * for options by name.
             * contains the user's help
             */
            po::options_description generalDescription_;
            /**
             * @brief serverSettingsDescription_ - contains listen addresses, port, MaxPendingConnections
             */
            po::options_description serverSettingsDescription_;


            /**
             * @brief Concrete variables map which store variables in real map.
             */
            po::variables_map variablesMap_;

            /**
             * @brief initDescriptions - Initializes the description of the parameters
             */
            void initDescriptions();

            /**
             * @brief startParsing - basic parsing of arguments, checking the correctness of the server configuration
             * @param argc - count of arguments
             * @param argv - values of arguments
             */
            void startParsing(int argc, char *argv[]);

            std::string listenAddresses_;

            void prepareSettings(const boost::program_options::variables_map &vm, const std::string &listenAddresses);
        };

    }
}



