//
// Created by boa on 11.07.17.
//

#pragma once
#include <boost/program_options.hpp>
#include <boost/signals2.hpp>
#include "../../config/include/config.hpp"
#include <QObject>
namespace calc_server {
    namespace parser {
        using namespace config;
        namespace po=boost::program_options;
        class ArgumentParser : public QObject {
            Q_OBJECT
        public:
            /**
             * @brief ArgumentParser
             * @param argc count of arguments
             * @param argv values of the arguments
             */
            ArgumentParser(int argc, char *argv[], QObject *parent = Q_NULLPTR);

            /**
             * @brief ~ArgumentParser - destrucror
             */
            virtual ~ArgumentParser();

            /**
             * @brief getServerConfig
             * @return  tuple with listen addresses diapasone, listen port and max pending connections
             */
             std::tuple<LISTEN_ADDRESSES, unsigned ,unsigned > getServerConfig() {
                 return std::make_tuple(listenAddresses_, port_, maxPendingConnections_);
             }

        private:
            /**
             * @brief generalDescription_ - command line options description
             */
            po::options_description generalDescription_;
            /**
             * @brief taskType_ - type of task
             */
            std::string taskType_;
            /**
             * @brief addresses - listen addresses diapasone
             */
            std::string addresses_;
            /**
             * @brief listenAddresses_
             */
            LISTEN_ADDRESSES listenAddresses_;
            /**
             * @brief port_ - number of listen port
             */
            unsigned port_;
            /**
             * @brief maxPendingConnections_ - max pending connections
             */
            unsigned maxPendingConnections_;

            /**
             * @brief initDescriptions
             */
            void initDescriptions();

            /**
             * @brief startParsing start command line arguments parser
             * @param argc count of arguments
             * @param argv  - arguments
             */
            void startParsing(int argc, char *argv[]);
        };

    }//namespace parser
}//namespace calc_server
