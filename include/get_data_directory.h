#ifndef SIM_GET_DATA_DIRECTORY_H
#define SIM_GET_DATA_DIRECTORY_H

#include <string>

#define STRINGIFY(s) #s
#define DataDir(s) STRINGIFY(s)

namespace sim {

    inline std::string Gauss::dataDir() {
        return std::string(DataDir(SIM_DATA_DIRECTORY));
    }

}