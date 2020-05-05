#ifndef SIM_GET_DATA_DIRECTORY_H
#define SIM_GET_DATA_DIRECTORY_H

#include <string>

#define STRINGIFY(s) #s
#define DataDir(s) STRINGIFY(s)

//Why oh why doesn't C++ have an std::path_seperator ? 
#ifdef _WIN32
    const std::string pathsep("\\");
#else
    const std::string pathsep("/");
#endif

namespace sim {

    inline std::string data_dir() {
        return std::string(DataDir(SIM_DATA_DIRECTORY))+"";
    }

}

#endif