#ifndef CHECK_ARGUMENTS_H
#define CHECK_ARGUMENTS_H

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <mex.h>

namespace sim {


    struct Dim {
    
        std::pair<size_t, size_t> m_compare_to; 
        size_t m_size;

        bool m_relative;

        Dim(size_t obj, size_t dim) {
            m_compare_to = std::pair<size_t,size_t>(obj,dim);
            m_relative = true;
        }

        Dim(size_t dim) {
            m_size = dim;
            m_relative = false;
        }

    };

    //Utilties to check input the validity of mex input
    struct Argument {
        
        enum {
            DYNAMIC = std::numeric_limits<size_t>::max()
        };

        std::string m_type; //one of the types from here:
                            //https://www.mathworks.com/help/matlab/apiref/mxisclass.html 

        std::vector<std::vector<Dim> > m_dim; //dimensions of each size, each dimension can have 
                                                 //optional sizes

        bool m_optional; //is this argument optional

        Argument(std::string &&type, std::vector<std::vector<Dim> > &&dim, bool &&optional) {
            m_type = type;
            m_dim = dim;
            m_optional = optional;
        }

    };

    bool validate_arguments(std::vector<Argument> &&arg_list,int nrhs, const mxArray *prhs[])
    {
        
        if(nrhs > arg_list.size()) {
            mexPrintf("Error: too many arguments provided\n");   
            mexErrMsgTxt("Exiting ...\n");
            return false;
        }

        int num_to_check = (nrhs < arg_list.size() ? nrhs : arg_list.size());

        int num_optional = 0;

        for(unsigned int ii=0; ii<arg_list.size(); ++ii) {
            
            if(arg_list[ii].m_optional) {
                num_optional++;
            }
        }

        if(nrhs < arg_list.size() - num_optional) {
            mexPrintf("Error: not enough arguments provided\n");   
            mexErrMsgTxt("Exiting ...\n");
            return false;
        }

        for(unsigned int ii=0; ii<num_to_check; ++ii) {

            //check type 
            if(!mxIsClass(prhs[ii], arg_list[ii].m_type.c_str())) {
                mexPrintf("Error: Argument %d is wrong type, %s expected\n", ii, arg_list[ii].m_type.c_str());     
                mexErrMsgTxt("Exiting ...\n");
                return false;
            }

            //check dimensions
            mwSize num_dim = mxGetNumberOfDimensions(prhs[ii]);
            const mwSize *dim = mxGetDimensions(prhs[ii]);

            if(num_dim != arg_list[ii].m_dim.size()) {
                mexPrintf("Error: Argument %d is wrong size, %d dimensions expected, %d specified\n", 
                            ii, arg_list[ii].m_dim.size(), num_dim);
                mexErrMsgTxt("Exiting ...\n");
                return false;
            }

            for(unsigned int jj=0; jj<arg_list[ii].m_dim.size(); ++jj) {

                //dim has to be dynamic or match any of the provided options
                bool dim_match = false;

                
                for(unsigned int ll=0; ll<arg_list[ii].m_dim[jj].size(); ++ll) {
                    
                    //if compare to other argument
                    if(arg_list[ii].m_dim[jj][ll].m_relative) {
                        //check relative argument for validity
                        int arg_index = arg_list[ii].m_dim[jj][ll].m_compare_to.first;
                        int dim_index = arg_list[ii].m_dim[jj][ll].m_compare_to.second;

                        if(arg_index < nrhs) {
                            if(dim_index < mxGetNumberOfDimensions(prhs[arg_index])) {
                                const mwSize *dim_from = mxGetDimensions(prhs[ii]);
                                const mwSize *dim_to = mxGetDimensions(prhs[arg_index]);

                                if(dim_from[jj] == dim_to[dim_index]) {
                                    dim_match=true;
                                }
                            }
                        }

                    } else if(arg_list[ii].m_dim[jj][ll].m_size == Argument::DYNAMIC) {
                        dim_match = true;
                    } else if(dim[jj] == arg_list[ii].m_dim[jj][ll].m_size) {
                        dim_match = true;
                    }
                }
                

                if(!dim_match) {
                    mexPrintf("Error: Argument %d is wrong size, in dimension %d \n", ii, jj); 
                    mexErrMsgTxt("Exiting ...\n");
                    return false;
                }
            }
        }

        return true;
    

    }

}


#endif