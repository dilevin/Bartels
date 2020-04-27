#ifndef SIM_READ_TETGEN_H
#define SIM_READ_TETGEN_H

#include <Eigen/Dense>
#include <EigenTypes.h>

#include <fstream>
#include <iostream>

namespace sim {

    //read in a tetgen file
    template<typename VertexType>
    void read_tetgen(Eigen::MatrixBase<VertexType> &V, Eigen::Ref<Eigen::MatrixXi> F, const std::string &nodeFile, const std::string &eleFile);

}

#ifndef SIM_STATIC_LIBRARY
    # include<../src/read_tetgen.cpp>
#endif

#endif

