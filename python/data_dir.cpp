#include <npe.h>

//bartels
#include <get_data_directory.h>

npe_function(data_dir)
npe_begin_code()

    return sim::data_dir();

npe_end_code()

