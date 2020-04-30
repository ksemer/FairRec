#ifndef _EDGE_ADD_HPP
#define _EDGE_ADD_HPP

#include "graph.hpp"
#include "pagerank.hpp"

struct step_log {
    double red_pagerank;
    double red_pagerank_prediction;
    double red_pagerank_generalized_prediction;
};

struct edge {
    int source;
    int destination;
};

enum class algorithm_mode {GREEDY, FAST_GREEDY, APPROX, FAST_APPROX, RANDOM, RAND_SRC, ONE_TO_ALL_G, ONE_TO_ALL_FG, ONE_TO_ALL_R};

class Edge_addition {
    public:
        Edge_addition(graph &g, pagerank_algorithms &algs, int n_source = 10, int n_target = 100);
        void greedy_per_one(const double C=0.85, const double eps=1e-4, const int max_iter=100);
        void greedy_all(const double C=0.85, const double eps=1e-4, const int max_iter=100);
        void fast_greedy_per_one(const double C=0.85, const double eps=1e-4, const int max_iter=100);
        void fast_greedy_all(const double C=0.85, const double eps=1e-4, const int max_iter=100);
        void random_edges(int exp, const double C=0.85, const double eps=1e-4, const int max_iter=100);
        void random_sources_per_one(const double C=0.85, const double eps=1e-4, const int max_iter=100);
        void random_sources_all(const double C=0.85, const double eps=1e-4, const int max_iter=100);
        // Every edge I calculate again.
        void one_to_all_greedy(const double C=0.85, const double eps=1e-4, const int max_iter=100);
        // All conections are Calculated in the beginning.
        void one_to_all_fast_greedy(const double C=0.85, const double eps=1e-4, const int max_iter=100);
        void one_to_all_random(const double C=0.85, const double eps=1e-4, const int max_iter=100);
        void source_and_targets(const double C=0.85, const double eps=1e-4, const int max_iter=100);
        //void approx();
        //void fast_approx();
        void save_logs(std::string algo_name, std::vector<step_log> log_vec);
        void save_logs_per_node(std::string algo_name, int src_node, std::vector<step_log> vec);
    
    private:
        // Get n best source nodes.
        pagerank_v get_best_source_nodes(int n = 10, const double C=0.85, const double eps=1e-4, const int max_iter=100);
        // Return values of Objective function.
        pagerank_v get_objective_val(int s_node, const double C=0.85, const double eps=1e-4, const int max_iter=100);
        double get_generalized_objective_val(double init_red_pagerank, double init_source_pagerank, pagerank_v init_red_abs_prob, pagerank_v init_src_abs_prob,
            std::vector<int> init_src_nei, std::vector<edge> new_edges);
        // Save Source Nodes.
        void save_source_nodes(std::string algo_name, std::vector<int> sources);
        void save_target_nodes(std::string algo_name, std::vector<int> sources);
        // Save impact.
        void save_impact(std::vector<double> impact_v);

        graph &g;
        pagerank_algorithms &algs;

        double jump_prob = 0.15;
        int n_source, n_target; // Number of source, target nodes.
};

#endif /* _EDGE_ADD_HPP */
