//
// Created by boa on 11.07.17.
//
#pragma once

#include <string>

namespace calc_server {
    namespace config {
#define OR ||
#define AND &&

        const std::string ANY = "any";
        const std::string LOCAL_HOST = "localhost";
        const std::string ANY_IPV4 = "anyv4";
        const std::string ANY_IPV6 = "anyv6";
        const std::string HELP = "help";
        enum class LISTEN_ADDRESSES {
            ANY,
            LOCAL_HOST,
            ANY_IPV4,
            ANY_IPV6
        };
        /**
         * @brief MIN_PORT - All ports < 1000 were used by the OS and not available
         */
        const unsigned int MIN_PORT = 1001;
        const unsigned int DEFAULT_PORT = 7777;
        const unsigned int DEFAULT_MAX_PENDING_CONNECTIONS = 30;//see official documentation for QTcpServer
    }//namespace config
}//namespace calc_server {

