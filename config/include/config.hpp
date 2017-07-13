//
// Created by boa on 11.07.17.
//
#pragma once

#include <string>

namespace calc_server {
    namespace config {
#define OR ||
#define AND &&

        const std::string MAX_PENDING_CONNECTIONS = "max_con";
        const std::string PORT = "port";
        const std::string ADDRESSES = "addresses";
        const std::string ANY = "any";
        const std::string LOCAL_HOST = "localhost";
        const std::string ANY_IPV4 = "anyv4";
        const std::string ANY_IPV6 = "anyv6";
        const std::string HELP = "help";
        enum class LISTEN_ADDRESSES {
            ANY,
            LOCAL_HOST,
            ANY_IPV4,
            ANY_IPV6,
            UNKNOWN
        };
        /**
         * @brief MIN_PORT - All ports < 1000 were used by the OS and not available
         */
        const unsigned int MIN_PORT = 1001;

    }
}

