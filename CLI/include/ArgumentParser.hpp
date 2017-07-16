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

            virtual ~ArgumentParser();

             std::tuple<LISTEN_ADDRESSES, unsigned ,unsigned > getServerConfig() {
                 return std::make_tuple(listenAddresses_, port_, maxPendingConnections_);
             }

        private:
            po::options_description generalDescription_;
            po::options_description serverDesc_;
            std::string taskType_;
            std::string addresses_;
            LISTEN_ADDRESSES listenAddresses_;
            unsigned port_;
            unsigned maxPendingConnections_;
            void initDescriptions();
            void startParsing(int argc, char *argv[]);
        };

    }//namespace parser
}//namespace calc_server
