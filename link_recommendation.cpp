#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include "graph.hpp"
#include "pagerank.hpp"
#include "edge_add.hpp"



static bool get_options(const int argc, char ** const argv, algorithm_mode &algo_mode, int &n_source, int &n_target) {
    if (argc != 6) goto error;
    if (!std::strcmp(argv[1], "-gd") && !std::strcmp(argv[2], "-s") && !std::strcmp(argv[4], "-t")) {
        algo_mode = algorithm_mode::GREEDY;
        n_source = std::atoi(argv[3]);
        n_target = std::atoi(argv[5]);

    } else if (!std::strcmp(argv[1], "-fgd") && !std::strcmp(argv[2], "-s") && !std::strcmp(argv[4], "-t")) {
        algo_mode = algorithm_mode::FAST_GREEDY;
        n_source = std::atoi(argv[3]);
        n_target = std::atoi(argv[5]);

    } else if (!std::strcmp(argv[1], "-apx") && !std::strcmp(argv[2], "-s") && !std::strcmp(argv[4], "-t")) {
        algo_mode = algorithm_mode::APPROX;
        n_source = std::atoi(argv[3]);
        n_target = std::atoi(argv[5]);

    } else if (!std::strcmp(argv[1], "-fapx") && !std::strcmp(argv[2], "-s") && !std::strcmp(argv[4], "-t")) {
        algo_mode = algorithm_mode::FAST_APPROX;
        n_source = std::atoi(argv[3]);
        n_target = std::atoi(argv[5]);

    } else {
        goto error;
    }
    return true;

error:
	std::cerr << "Usage: " << argv[0] << " [options]\n"
		"Options:\n"
		"-gd -s <number of source nodes> -t <number of target nodes>\t\t\t Greedy \n"
		"-fgd -s <number of source nodes> -t <number of target nodes>\t\t\t Fast Greedy\n"
		"-apx -s <number of source nodes> -t <number of target nodes>\t\t\t  Approximation\n"
		"-fapx -s <number of source nodes> -t <number of target nodes>\t\t\t Fast Approximation" << std::endl;
	return false;
}


int main(int argc, char **argv) {
    // Init arguments.
    algorithm_mode algo_mode;
    int n_source = 1;
    int n_target = 1;

    if (!get_options(argc, argv, algo_mode, n_source, n_target)) return 1;

    // Init graph and algorithms.
    graph g("out_graph.txt", "out_community.txt");
    pagerank_algorithms algs(g);
    Edge_addition link_rec(g, algs, n_source, n_target);

    switch (algo_mode)
    {
    case algorithm_mode::GREEDY :
        link_rec.greedy();
        break;
    case algorithm_mode::FAST_GREEDY :
        link_rec.fast_greedy();
        break;
    default:
        std::cout << "Not supported yet\n";
        return 1;
    }
    link_rec.save_logs();
}