#include <iostream>
#include <string>
#include <ctime>
#include "../include/read.h"
#include "../include/build.h"
#include "../include/diag.h"
#include "../include/write.h"
#include "../include/util.h"

int main(int argc, char* argv[]) {
    std::ios_base::sync_with_stdio(false);
	std::cout << "EZNMA> ***********************************************" << std::endl
	          << "EZNMA> Normal Mode Analysis with Elastic Network Model" << std::endl
	          << "EZNMA> version 1.0 beta, Feburary 2017." << std::endl
	          << "EZNMA> ***********************************************" << std::endl 
              << std::endl;
    if(argc!=2) {
        std::cout << "ERROR> Missing input file!" << std::endl;
        return 1;
    }

    /* 1. read input */
    std::string inp_name = argv[1];
    Config config;
    if(!read_config(inp_name, config)) { return 1; }
    print_config(config);
    
    /* 2. build array */
    Leading_Dim leading_dim = build_hessian(config.nma_coor, config.r_cutoff);

    /* 3. diagonalize array*/
    diag_hessian_gpu(leading_dim.LD_matrix, config.tol);
    
    /* 4. calculate overlap if requested, currently not implemented.
        calc_overlap(config.job_name, config.ref_coor);
    */

    /* 5. write output */
    std::string out_name = config.job_name + std::string("_eigen_data_cutoff") + 
                           real2str(config.r_cutoff) + std::string(".dat");

    write_data(leading_dim, config.n_modes, out_name, config.tol);

    std::cout << "EZNMA> Normal termination of the program." << std::endl;
    
    return 0;
}
