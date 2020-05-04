#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "edge_add.hpp"
#include <ctime>
#include <cstdlib>

// Class constructor.
Edge_addition::Edge_addition(graph &g, pagerank_algorithms &algs, int n_source, int n_target) : g(g), algs(algs),
    n_source(n_source), n_target(n_target) {
        // Nothing to do here.
}

// Algorithms
void Edge_addition::greedy(const double C, const double eps, const int max_iter) {
    if (l_kind == log_kind::ALL_SOURCES) {
        greedy_all_sources();
    } else if (l_kind == log_kind::PER_SOURCE) {
        greedy_per_source();
    }
}

void Edge_addition::greedy_per_source(const double C, const double eps, const int max_iter) {
    // Declare local variables.
    pagerank_v rank_vector;
    std::vector<int> s_nodes;
    std::vector<step_log> log_vec;
    pagerank_t target_node;
    std::vector<edge> new_edges;
    edge new_edge;
    double red_pagerank;
    int no_edges;

    // Get number of nodes.
    const int nnodes = g.get_num_nodes();

    // Get source nodes.
    s_nodes = get_source_nodes(n_source, C, eps, max_iter);
    // Save source nodes.
    save_vector("out_sources_one.txt", s_nodes);

    // For each Source nodes.
    for (auto s_node = s_nodes.begin(); s_node < s_nodes.end(); s_node++) {// Clear log_vector
        log_vec.clear();
        // Get pagerank.
        rank_vector = algs.get_pagerank(C, eps, max_iter);
        // Get Red pagerank.
        red_pagerank = g.get_pagerank_per_community(rank_vector)[1];
        // Add log point to log vector.
        add_log_point(log_vec, red_pagerank, red_pagerank);
        // Update new edge source.
        new_edge.source = *s_node;
        // Find valide number of new edges.
        no_edges = get_valide_no_edges(new_edge.source);
        // Find n_edges nodes to connect.
        for (int t_node = 0; t_node < no_edges; t_node++) {
            // Get best target node.
            target_node = get_best_target_nodes(new_edge.source, 1)[0];
            // Update new edge destination.
            new_edge.destination = target_node.node_id;
            // Add best node to source node.
            g.add_edge(new_edge.source, new_edge.destination);
            // Add edge to new edges.
            new_edges.push_back(new_edge);
            // Get pagerank.
            rank_vector = algs.get_pagerank(C, eps, max_iter);
            // Get Red pagerank.
            red_pagerank = g.get_pagerank_per_community(rank_vector)[1];
            // Renew log point.
            add_log_point(log_vec, red_pagerank, target_node.pagerank);
        }
        // Save logs.
        save_vector("out_greedy_source_" + std::to_string(new_edge.source) + ".txt", log_vec);
        // Remove edges.
        remove_new_edges(new_edges);
    }
}

void Edge_addition::greedy_all_sources(const double C, const double eps, const int max_iter) {
    // Declare local variables.
    pagerank_v rank_vector;
    std::vector<int> s_nodes;
    std::vector<step_log> log_vec;
    std::vector<edge> new_edges;
    edge new_edge;
    pagerank_t target_node;
    double red_pagerank;
    int no_edges;

    // Get number of nodes.
    const int nnodes = g.get_num_nodes();

    // Get source nodes.
    s_nodes = get_source_nodes(n_source, C, eps, max_iter);
    // Save source nodes.
    save_vector("out_sources_one.txt", s_nodes);
    // Get pagerank.
    rank_vector = algs.get_pagerank(C, eps, max_iter);
    // Get Red pagerank.
    red_pagerank = g.get_pagerank_per_community(rank_vector)[1];
    // Add log point to log vector.
    add_log_point(log_vec, red_pagerank, red_pagerank);

    // For each Source nodes.
    for (auto s_node = s_nodes.begin(); s_node < s_nodes.end(); s_node++) {
        // Find valide number of new edges.
        no_edges = get_valide_no_edges(*s_node);
        new_edge.source = *snode;
        // Find n_edges nodes to connect.
        for (int t_node = 0; t_node < no_edges; t_node++) {
            // Get best node.
            target_node = get_best_target_nodes(new_edge.source, 1)[0];
            new_edge.destination = target_node.node_id;
            // Add best node to source node.
            g.add_edge(new_edge.source, new_edge.destination);
            // Add edge to new edges.
            new_edges.push_back(new_edge);
            // Get pagerank.
            rank_vector = algs.get_pagerank(C, eps, max_iter);
            // Get Red pagerank.
            red_pagerank = g.get_pagerank_per_community(rank_vector)[1];
            // Renew log point.
            add_log_point(log_vec, red_pagerank, target_node.pagerank);
        }
    }
    // Save log vector.
    save_vector("out_greedy_all_sources.txt", log_vec);
    // Remove new edges.
    remove_new_edges(new_edges);
}


void Edge_addition::add_edges(int exp, const double C, const double eps, const int max_iter) {
    if (l_kind == log_kind::ALL_SOURCES) {
        add_edges_all();
    } else if (l_kind == log_kind::PER_SOURCE) {
        add_edges_per_one();
    }
}

void Edge_addition::add_edges_per_one(int exp, const double C, const double eps, const int max_iter) {
    // Declare local variables.
    pagerank_v rank_vector;
    std::vector<int> s_nodes;
    std::vector<step_log> log_vec;
    std::vector<edge> new_edges;
    pagerank_t target_node;
    double red_pagerank;
    int no_edges;

    // Init seed.
    srand(time(NULL));
    // Get pagerank.
    rank_vector = algs.get_pagerank(C, eps, max_iter);
    // Get Red pagerank.
    red_pagerank = g.get_pagerank_per_community(rank_vector)[1];
    // Add log point to log vector.
    add_log_point(log_vec, red_pagerank, red_pagerank);
    // Get edges.
    new_edges() = get_edges(n_edges);

    // Add edges.
    for (auto new_edge = new_edges.begin(); new_edge < new_edges.end(); new_edges++) {
        g.add_edge(new_edge -> source, new_edge -> destination);
        // Get pagerank.
        rank_vector = algs.get_pagerank(C, eps, max_iter);
        // Get Red pagerank.
        red_pagerank = g.get_pagerank_per_community(rank_vector)[1];
        // Add log point to log vector.
        add_log_point(log_vec, red_pagerank);
        g.remove_edge(new_edge -> source, new_edge -> destination);
    }
    // Save logs.
    save_vector("out_random_edges_per_one.txt", log_vec);
}

void Edge_addition::add_edges_all(int exp, const double C, const double eps, const int max_iter) {
    // Declare local variables.
    pagerank_v rank_vector;
    std::vector<int> s_nodes;
    std::vector<step_log> log_vec;
    std::vector<edge> new_edges;
    pagerank_t target_node;
    double red_pagerank;
    int no_edges;

    // Init seed.
    srand(time(NULL));
    // Get pagerank.
    rank_vector = algs.get_pagerank(C, eps, max_iter);
    // Get Red pagerank.
    red_pagerank = g.get_pagerank_per_community(rank_vector)[1];
    // Add log point to log vector.
    add_log_point(log_vec, red_pagerank, red_pagerank);
    
    // Get edges.
    new_edges() = get_edges(n_edges);
    // Add edges.
    for (auto new_edge = new_edges.begin(); new_edge < new_edges.end(); new_edges++) {
        g.add_edge(new_edge -> source, new_edge -> destination);
        // Get pagerank.
        rank_vector = algs.get_pagerank(C, eps, max_iter);
        // Get Red pagerank.
        red_pagerank = g.get_pagerank_per_community(rank_vector)[1];
        // Add log point to log vector.
        add_log_point(log_vec, red_pagerank);
    }
    // Remove new edges.
    remove_new_edges(new_edges);
}

void Edge_addition::one_to_all_greedy(const double C, const double eps, const int max_iter) {
    // Declare local variables.
    pagerank_v objective_val, rank_vector, source_nodes;
    std::vector<int> neighbors, target_nodes;
    std::vector<step_log> log_vec;
    pagerank_s target_node;
    step_log log_point;
    double red_pagerank;
    int s_out_degree;

    // Get number of nodes.
    const int nnodes = g.get_num_nodes();
    // Init n_source.
    n_source = nnodes;

    // Get pagerank.
    rank_vector = algs.get_pagerank(C, eps, max_iter);
    // Get Red pagerank.
    red_pagerank = g.get_pagerank_per_community(rank_vector)[1];
    // Renew log point.
    log_point.red_pagerank = red_pagerank;
    log_point.red_pagerank_prediction = red_pagerank;
    // Store to log vector.
    log_vec.push_back(log_point);

    // For each Source nodes.
    for (int src_node = 0; src_node < n_source; src_node++) {
        // Print Source node.
        std::cout << "---------------------------------------\n";
        std::cout << "Source node: " << src_node << std::endl;
        // Find the best node to connect, if any.
        // Get objective values for all nodes.
        objective_val = get_objective_val(src_node, C, eps, max_iter);
        // Get out degree for source node.
        s_out_degree = g.get_out_degree(src_node);
        // Remove neighbors of source node from "finding the
        // best" procedure. Do that by setting their objective value to -2.
        neighbors = g.get_out_neighbors(src_node);
        for (int nei = 0; nei < s_out_degree; nei++) { 
            objective_val[neighbors[nei]].pagerank = -2;
        }
        // Remove self from "finding the best procedure".
        // Do that by setting its objective value to -2.
        objective_val[src_node].pagerank = -2;
        // Find best edge to add.
        target_node.node_id = -2;
        target_node.pagerank = -2;
        // Search all nodes.
        for (int cand = 0; cand < nnodes; cand++) {
            // If there is better, Renew node information.
            if (objective_val[cand].pagerank > target_node.pagerank) {
                target_node.node_id = cand;
                target_node.pagerank = objective_val[cand].pagerank;
            }
        }
        if (target_node.pagerank > 0) {
            // Add best node to source node.
            g.add_edge(src_node, target_node.node_id);
            target_nodes.push_back(target_node.node_id);
            // Get pagerank.
            rank_vector = algs.get_pagerank(C, eps, max_iter);
            // Get Red pagerank.
            red_pagerank = g.get_pagerank_per_community(rank_vector)[1];
            // Renew log point.
            log_point.red_pagerank = red_pagerank;
            log_point.red_pagerank_prediction = target_node.pagerank;
            // Store to log vector.
            log_vec.push_back(log_point);
        }   
    }
    // Save log vector.
    save_logs("one_to_all_greedy", log_vec);
    save_target_nodes("otag", target_nodes);
}

void Edge_addition::one_to_all_fast_greedy(const double C, const double eps, const int max_iter) {
    // Declare local variables.
    pagerank_v objective_val, rank_vector, source_nodes;
    std::vector<int> neighbors, target_nodes;
    std::vector<step_log> log_vec;
    pagerank_s target_node;
    step_log log_point;
    double red_pagerank;
    int s_out_degree;
    edge new_edge;
    std::vector<edge> new_edges;

    // Get number of nodes.
    const int nnodes = g.get_num_nodes();
    // Init n_source.
    n_source = nnodes;

    // Get pagerank.
    rank_vector = algs.get_pagerank(C, eps, max_iter);
    // Get Red pagerank.
    red_pagerank = g.get_pagerank_per_community(rank_vector)[1];
    // Renew log point.
    log_point.red_pagerank = red_pagerank;
    log_point.red_pagerank_prediction = red_pagerank;
    // Store to log vector.
    log_vec.push_back(log_point);

    // For each Source nodes.
    for (int src_node = 0; src_node < n_source; src_node++) {
        // Print Source node.
        std::cout << "---------------------------------------\n";
        std::cout << "Source node: " << src_node << std::endl;
        // Find the best node to connect, if any.
        // Get objective values for all nodes.
        objective_val = get_objective_val(src_node, C, eps, max_iter);
        // Get out degree for source node.
        s_out_degree = g.get_out_degree(src_node);
        // Remove neighbors of source node from "finding the
        // best" procedure. Do that by setting their objective value to -2.
        neighbors = g.get_out_neighbors(src_node);
        for (int nei = 0; nei < s_out_degree; nei++) { 
            objective_val[neighbors[nei]].pagerank = -2;
        }
        // Remove self from "finding the best procedure".
        // Do that by setting its objective value to -2.
        objective_val[src_node].pagerank = -2;
        // Find best edge to add.
        target_node.node_id = -2;
        target_node.pagerank = -2;
        // Search all nodes.
        for (int cand = 0; cand < nnodes; cand++) {
            // If there is better, Renew node information.
            if (objective_val[cand].pagerank > target_node.pagerank) {
                target_node.node_id = cand;
                target_node.pagerank = objective_val[cand].pagerank;
            }
        }
        if (target_node.pagerank > 0) {
            new_edge.source = src_node;
            new_edge.destination = target_node.node_id;
            new_edges.push_back(new_edge);
        } else {
            new_edge.source = src_node;
            new_edge.destination = -1;
            new_edges.push_back(new_edge);
        }
    }
    for (int src_node = 0; src_node < n_source; src_node++) {
        if (new_edges[src_node].destination >= 0) {
            g.add_edge(new_edges[src_node].source, new_edges[src_node].destination);
            target_nodes.push_back(new_edges[src_node].destination);
            // Get pagerank.
            rank_vector = algs.get_pagerank(C, eps, max_iter);
            // Get Red pagerank.
            red_pagerank = g.get_pagerank_per_community(rank_vector)[1];
            // Renew log point.
            log_point.red_pagerank = red_pagerank;
            log_point.red_pagerank_prediction = target_node.pagerank;
            // Store to log vector.
            log_vec.push_back(log_point);
        }
    }
    // Save log vector.
    save_logs("one_to_all_fast_greedy", log_vec);
    save_target_nodes("otafg", target_nodes);
}

void Edge_addition::one_to_all_random(const double C, const double eps, const int max_iter) {
    // Declare local variables.
    pagerank_v objective_val, rank_vector, source_nodes;
    std::vector<int> neighbors, no_neighbors, target_nodes;
    std::vector<step_log> log_vec;
    pagerank_s target_node;
    step_log log_point;
    double red_pagerank;
    int nnodes = g. get_num_nodes();
    std::vector<int> all_nodes(nnodes);
    for (int i = 0; i < nnodes; i++) {
        all_nodes[i] = i;
    }

    // Init n_source.
    n_source = nnodes;

    // Get pagerank.
    rank_vector = algs.get_pagerank(C, eps, max_iter);
    // Get Red pagerank.
    red_pagerank = g.get_pagerank_per_community(rank_vector)[1];
    // Renew log point.
    log_point.red_pagerank = red_pagerank;
    // Store to log vector.
    log_vec.push_back(log_point);

    // For each Source nodes.
    for (int src_node = 0; src_node < n_source; src_node++) {
        // Print Source node.
        std::cout << "---------------------------------------\n";
        std::cout << "Source node: " << src_node << std::endl;
        // Get Source's neighbors.
        neighbors = g.get_out_neighbors(src_node);
        // Sort vectors for difference.
        std::sort(all_nodes.begin(), all_nodes.end());
        std::sort(neighbors.begin(), neighbors.end());
        // Get difference.
        std::set_difference(all_nodes.begin(), all_nodes.end(), neighbors.begin(), neighbors.end(), std::back_inserter(no_neighbors));
        // Check if there are acceptable edges.
        if (no_neighbors.size() != 0) {
            // Get random target.
            target_node.node_id = no_neighbors[(rand() % no_neighbors.size())];
            std::cout << "edge: " << src_node << " , " << target_node.node_id << std::endl;
            // Clear no_neighbors.
            no_neighbors.clear();
            // Add edge.
            g.add_edge(src_node, target_node.node_id);
            target_nodes.push_back(target_node.node_id);
            // Get pagerank.
            rank_vector = algs.get_pagerank(C, eps, max_iter);
            log_point.red_pagerank = g.get_pagerank_per_community(rank_vector)[1];
            log_vec.push_back(log_point);
        }   
    }
    // Save log vector.
    save_logs("one_to_all_random", log_vec);
    save_target_nodes("otar", target_nodes);
}

// Improve so as to handles n_target greater than possible.
void Edge_addition::source_stats(const double C, const double eps, const int max_iter) {
    // Declare Variables.
    pagerank_v rank_vector, obj_val;
    pagerank_s target_node;
    int src_node, s_out_degree;
    int nnodes = g.get_num_nodes();
    bool is_source;
    edge new_edge;
    std::vector<edge> new_edges;
    std::vector<int> neighbors;
    std::vector<int> src_nodes(n_source);
    std::vector<double> s_impact_1(nnodes, 0), s_impact_10(nnodes, 0), s_impact_max(nnodes, 0);
    std::vector<double> t_impact(nnodes, 0);
    double red_pgrnk, init_red_pagerank;

    // Get random source nodes.
    for (int i = 0; i < n_source; i++) {
        do {
            // Get random int from 0 to nnodes - 1.
            src_node = (rand() % nnodes);
            // Check if already exists.
            if (std::find(src_nodes.begin(), src_nodes.end(), src_node) != src_nodes.end()) {
                is_source = true;
            } else {
                is_source = false;
            }
        } while (is_source);
        // Add node to sources.
        src_nodes[i] = src_node;
    }
    // save source nodes.
    save_source_nodes("sources_and_edges", src_nodes);
    source_nodes = src_nodes;
    // Get impacts for source nodes.
    // For each source node.
    for (int s_node = 0; s_node < n_source; s_node++) {
        src_node = src_nodes[s_node];
        std::cout << "s node: " << src_node << "\n";
        // Get pagerank.
        rank_vector = algs.get_pagerank();
        // Get red pagerank.
        init_red_pagerank = g.get_pagerank_per_community(rank_vector)[1];
        // Init impacts.
        //s_impact_1[src_node] = red_pgrnk;
        //s_impact_10[src_node] = red_pgrnk;
        //s_impact_max[src_node] = red_pgrnk;
        // For each edge.
        for (int t_node = 0; t_node < n_target; t_node++) {
            // Get objective values for all nodes.
            rank_vector = get_objective_val(src_node, C, eps, max_iter);
            // Get out degree for source node.
            s_out_degree = g.get_out_degree(src_node);
            // Remove neighbors of source node from "finding the
            // best" procedure. Do that by setting their objective value to -2.
            neighbors = g.get_out_neighbors(src_node);
            for (int nei = 0; nei < s_out_degree; nei++) { 
                rank_vector[neighbors[nei]].pagerank = -2;
            }
            // Remove self from "finding the best procedure".
            // Do that by setting its objective value to -2.
            rank_vector[src_node].pagerank = -2;
            // Find best edge to add.
            target_node.node_id = -2;
            target_node.pagerank = -2;
            // Search all nodes.
            for (int cand = 0; cand < nnodes; cand++) {
                // If there is better, Renew node information.
                if (rank_vector[cand].pagerank - init_red_pagerank > target_node.pagerank) {
                    target_node.node_id = cand;
                    target_node.pagerank = rank_vector[cand].pagerank;
                }
            }
            
            // Add best node to source node.
            g.add_edge(src_node, target_node.node_id);
            new_edge.source = src_node;
            new_edge.destination = target_node.node_id;
            new_edges.push_back(new_edge);
            // Get pagerank.
            rank_vector = algs.get_pagerank(C, eps, max_iter);
            // Get Red pagerank.
            red_pgrnk = g.get_pagerank_per_community(rank_vector)[1];
            // Renew Impacts.
            // Renew 1 edge impact.
            if ((red_pgrnk - init_red_pagerank > s_impact_1[src_node]) && (t_node == 1)) {
                s_impact_1[src_node] = red_pgrnk - init_red_pagerank;
            }
            if ((red_pgrnk - init_red_pagerank > s_impact_10[src_node]) && (t_node < 10)) {
                s_impact_10[src_node] = red_pgrnk - init_red_pagerank;
            }
            if (red_pgrnk - init_red_pagerank > s_impact_max[src_node]) {
                s_impact_max[src_node] = red_pgrnk - init_red_pagerank;
            }
        }
    }
    // Remove Edges.
    for (std::vector<edge>::iterator i = new_edges.begin(); i < new_edges.end(); i++) {
            g.remove_edge(i->source, i->destination);
        }
    // Clean edges.
    new_edges.clear();
    // Save impacts.
    save_impact("s1", s_impact_1);
    save_impact("s10", s_impact_10);
    save_impact("smax", s_impact_max);    
}

//
void Edge_addition::targets_stats(const double C, const double eps, const int max_iter) {
    // Declare Variables.
    pagerank_v rank_vector, obj_val;
    pagerank_s target_node;
    int src_node, s_out_degree;
    int nnodes = g.get_num_nodes();
    edge new_edge;
    std::vector<edge> new_edges;
    std::vector<int> neighbors;
    std::vector<double> t_impact(nnodes, 0);
    double red_pgrnk, init_red_pagerank;
    // Get Impact for destination nodes.
    // For each source node.
    for (int s_node = 0; s_node < n_source; s_node++) {
        src_node =source_nodes[s_node];
        std::cout << "s node: " << src_node << "\n";
        // Clean log vectors.
        std::fill(t_impact.begin(), t_impact.end(), 0);
        // Get pagerank.
        rank_vector = algs.get_pagerank();
        // Get red pagerank.
        init_red_pagerank = g.get_pagerank_per_community(rank_vector)[1];
        // Get objective values for all nodes.
        obj_val = get_objective_val(src_node, C, eps, max_iter);
        // Get out degree for source node.
        s_out_degree = g.get_out_degree(src_node);
        // Remove neighbors of source node from "finding the
        // best" procedure. Do that by setting their objective value to -2.
        neighbors = g.get_out_neighbors(src_node);
        for (int nei = 0; nei < s_out_degree; nei++) { 
            obj_val[neighbors[nei]].pagerank = -2;
        }
        // Remove self from "finding the best procedure".
        // Do that by setting its objective value to -2.
        obj_val[src_node].pagerank = -2;
        // Find best edge to add.
        target_node.node_id = -2;
        target_node.pagerank = -2;
        // For each edge.
        for (int t_node = 0; t_node < n_target; t_node++) {
            // Search all nodes.
            for (int cand = 0; cand < nnodes; cand++) {
                // If there is better, Renew node information.
                if (obj_val[cand].pagerank > target_node.pagerank) {
                    target_node.node_id = cand;
                    target_node.pagerank = obj_val[cand].pagerank;
                }
            }
            // Add best node to source node.
            g.add_edge(src_node, target_node.node_id);
            new_edge.source = src_node;
            new_edge.destination = target_node.node_id;
            new_edges.push_back(new_edge);
            // Remove best node from next iteration.
            obj_val[target_node.node_id].pagerank = -2;
            target_node.pagerank = -2;
            // Get pagerank.
            rank_vector = algs.get_pagerank(C, eps, max_iter);
            // Get Red pagerank.
            red_pgrnk = g.get_pagerank_per_community(rank_vector)[1];
            // Renew Impacts.
            t_impact[target_node.node_id] = red_pgrnk - init_red_pagerank;
            // Remove edge.
            g.remove_edge(new_edge.source, new_edge.destination);
        }
        save_impact("target_s_" + std::to_string(src_node) , t_impact);
    }
    save_edge_list(new_edges);
}

// -------------------------------------------------------------------- Help Functions -------------------------------------------------------------------------.
// Get source nodes.
std::vector<int> Edge_addition::get_source_nodes(int n, const double C, const double eps, const int max_iter) {
    if (s_criterion == source_criterion::RANDOM) {
        return get_source_nodes_random();
    } else if (s_criterion == source_criterion::CRITERION_ONE) {
        return get_source_nodes_one();
    } else {
        std::cout << "Not supported source selection criterion!\n";
        exit(0);
    }
}

std::vector<int> Edge_addition::get_source_nodes_one(int n, const double C, const double eps, const int max_iter) {
    // Declare local variables.
    pagerank_v rank_vector, temp_s_nodes;
    std::vector<int> s_nodes;
    int src_node;

    // Get Pagerank.
    rank_vector = algs.get_pagerank(C, eps, max_iter);
    // Sort pagerank in descentding order.
    algs.sort_pagerank_vector(rank_vector);
    // Resize top_source_vector to 2*n. Keep top 2*n.
    temp_s_nodes.resize(2*n);
    for (int i = 0; i < 2*n; i++) {
        temp_s_nodes[i] = rank_vector[i];
    }
    // Get Blue personilized pagerank.
    rank_vector = algs.get_blue_abs_prob(C, eps, max_iter);
    // Change top source pagerank to Blue personilized.
    for (int i = 0; i < 2*n; i++) {
        src_node = temp_s_nodes[i].node_id;
        temp_s_nodes[i].pagerank = rank_vector[src_node].pagerank;
    }
    // Sort top nodes by Blue pagerank.
    algs.sort_pagerank_vector(temp_s_nodes);
    // Keep n top source nodes by this ranking.
    temp_s_nodes.resize(n);
    // Convert to return.
    for (int i = 0; i < n; i++) {
        s_nodes[i] = temp_s_nodes[i].node_id;
    }

    return s_nodes;
}

std::vector<int> Edge_addition::get_source_nodes_random(int n, const double C, const double eps, const int max_iter) {
    std::vector<int> s_nodes;
    int s_node;
    bool is_source;

    // Init seed.
    srand(time(NULL));
    // Get random source nodes.
    for (int i = 0; i < n_source; i++) {
        do {
            // Get random int from 0 to nnodes - 1.
            s_node = (rand() % nnodes);
            // Check if already exists.
            if (std::find(source_nodes.begin(), source_nodes.end(), s_node) != source_nodes.end()) {
                is_source = true;
            } else {
                is_source = false;
            }
        } while (is_source);
        // Add node to sources.
        s_nodes.push_back(s_node);
    }

    return s_nodes;
}

// Get target nodes.
std::vector<int> Edge_addition::get_target_nodes(int s_node, int no_targets) {
    if (t_criterion == target_criterion::RANDOM) {
        return get_target_node_random(s_node, no_targets);
    } else if (t_criterion == target_criterion::PREDICTION) {
        return get_target_node_pred(s_node,no_targets);
    } else {
        std::cout << "Not supported target selection criterion!\n";
        exit(0);
    }
}

std::vector<int> Edge_addition::get_target_nodes_random(int s_node, int no_targets) {
    std::vector<int> neighbors, all_nodes, no_neighbors;
    int no_nodes = g.get_num_nodes();

    // Init all_nodes.
    for (int i = 0; i < no_nodes; i++) {
        all_nodes[i] = i;
    }
    // Get neighbors of source node.
    neighbors = g.get_out_neighbors(s_node);
    // Sort vectors for difference.
    std::sort(neighbors.begin(), neighbors.end());
    // Get difference.
    std::set_difference(all_nodes.begin(), all_nodes.end(), neighbors.begin(), neighbors.end(), std::back_inserter(no_neighbors));
    // Suffle random.
    std::random_shuffle(no_neighbors.begin(), no_neighbors.end());
    if (no_neighbors.size() < no_targets) {
        std::cout << "No valide number of target for the source!\n";
        exit(0);
    }
    // Keep only no_targets.
    no_neighbors.resize(no_targets);

    return no_neighbors;
}

std::vector<int> Edge_addition::get_target_nodes_pred(int s_node, int no_targets) {
    pagerank_v t_nodes;
    std::vector<int> s_neighbors;
    pagerank_t cand;
    // Get objective value for all nodes.
    pagerank_v obj_values = get_objective_val(s_node);
    // Remove from comparison neighbors and source by setting
    // their value to -1.
    obj_values[s_node].pagerank = -1;
    s_neighbors = g.get_out_neighbors(s_node);
    for (auto it = s_neighbors.begin(); it < s_neighbors.end(); it++) {
        obj_values[*it].pagerank = -1;
    }
    // Get no_edges bests.
    for (int i = 0; i < no_targets; i++) {
        cand.node_id = -1;
        cand.pagerank = -1;
        // Search for the best.
        for (auto it = obj_values.begin(); it < obj_values.end(); it++) {
            if (it -> pagerank > cand.pagerank) {
                cand.node_id = it -> node_id;
                cand.pagerank = it -> pagerank;
            }
        }
        // Add best to target nodes.
        t_nodes.push_back(cand);
        // Remove best from competition.
        obj_values[cand.node_id].pagerank = -1;
    }
    
    return t_nodes;
}

// Get random edges.
std::vector<edge> Edge_addition::get_edges(int no_edges) {
    if (e_criterion == edge_criterion::RANDOM) {
        return get_edges_random(no_edges);
    } else if (e_criterion == edge_criterion::CRITERION_ONE) {
        return get_edges_one(no_edges);
    } else {
        std::cout << "Edge criterion not supported!\n";
        exit(0);
    }
}

std::vector<edge> Edge_addition::get_edges_random(int no_edges) {
    std::vector<edge> new_edges;
    edge new_edge;
    int no_valide_edges, j;

    j = 0;
    for (int i = 0; i < no_edges; i++) {
        // Get random source from 0 to nnodes - 1.
        new_edge.source = get_source_nodes(1)[0];
        no_valide_edges = get_valide_no_edges(new_edge.source);
        if (no_valide_edges > 0) {
            // Get random target.
            new_edge.destination = get_target_nodes_random(new_edge.source, 1);
            new_edges.push_back(new_edge);
        } else {
            i--;
        }
        j++;
        if (j > 3 * no_edges) {
            std::cout << "3 x number of edges tries without result!\n";
            exit(0);
        }
    }
    
    return new_edges;
}

std::vector<edge> Edge_addition::get_edges_one(int no_edges) {
    
}

// Remove new edges.
void Edge_addition::remove_new_edges(std::vector<edge> &new_edges) {
    for (auto it new_edges.begin(); it < new_edges.end(); it++) {
        g.remove_edge(it -> source, it -> destination);
    }
    new_edges.clear();
}

// Get Predictions.
pagerank_v Edge_addition::get_objective_val(int s_node, const double C, const double eps, const int max_iter) {
    // Declare local variables.
    pagerank_v objective_val, rank_vector, red_absorbing_probs, source_absorbing_probs;
    std::vector<int> neighbors;
    double red_pagerank, nominator_const, denominator_const, obj_nominator, obj_denominator;
    int s_out_degree, neighbor;
    const int nnodes = g.get_num_nodes();
    objective_val.resize(nnodes);

    // Get source out degree.
    s_out_degree = g.get_out_degree(s_node);
    // Run pagerank.
    rank_vector = algs.get_pagerank(C, eps, max_iter);
    // Get red pagerank.
    red_pagerank = g.get_pagerank_per_community(rank_vector)[1];
    // Run absoring to Red.
    red_absorbing_probs = algs.get_red_abs_prob(C, eps, max_iter);
    // Run absorbing to source.
    source_absorbing_probs = algs.get_node_abs_prob(s_node, C, eps, max_iter);
    // Get source neighbors.
    neighbors = g.get_out_neighbors(s_node);
    // Get average Red pagerank of neighbors for nominator.
    nominator_const = 0;
    if (s_out_degree > 0) {
        for (int nei = 0; nei < s_out_degree; nei++) {
            neighbor = neighbors[nei];
            nominator_const += red_absorbing_probs[neighbor].pagerank;
        }
        nominator_const *= (1 / (float)s_out_degree);
    } else {
        for (int nei = 0; nei < nnodes; nei++) {
            neighbor = nei;
            nominator_const += red_absorbing_probs[neighbor].pagerank;
        }
        nominator_const *= (1 / (float)nnodes);
    }
    // Get average Source pagerank of neighbors for denominator.
    denominator_const = 0;
    if (s_out_degree > 0) {
        for (int nei = 0; nei < s_out_degree; nei++) {
            neighbor = neighbors[nei];
            denominator_const += source_absorbing_probs[neighbor].pagerank;
        }
        denominator_const *= (1 / (float)s_out_degree);
    } else {
        for (int nei = 0; nei < nnodes; nei++) {
            neighbor = nei;
            denominator_const += source_absorbing_probs[neighbor].pagerank;
        }
        denominator_const *= (1 / (float)nnodes);
    }
    // Calculate the Quantity. Not just the important part but
    // all so as to have a sanity check.
    // For all nodes.
    for (int t_node = 0; t_node < nnodes; t_node++) {
        // Calculate nominator.
        obj_nominator = red_absorbing_probs[t_node].pagerank - nominator_const;
        obj_nominator *= ((1 - jump_prob) / jump_prob);
        // Calculate denominator.
        obj_denominator = source_absorbing_probs[t_node].pagerank - denominator_const;
        obj_denominator *= ((1 - jump_prob) / jump_prob);
        obj_denominator = s_out_degree + 1 - obj_denominator;
        objective_val[t_node].node_id = t_node;
        objective_val[t_node].pagerank = red_pagerank + rank_vector[s_node].pagerank * (obj_nominator / obj_denominator);
        // Theory check print.
        if (obj_denominator < 0) std::cout << "!!!NEGATIVE DENOMINATOR!!!\n";
    }

    return objective_val;
}

double Edge_addition::get_gen_objective_val(double init_red_pagerank, double init_source_pagerank, pagerank_v init_red_abs_prob, pagerank_v init_src_abs_prob,
            std::vector<int> init_src_nei, std::vector<edge> new_edges)
{
    // Declare local variables.
    double nominator_const, denominator_const, temp_const, objective_val;
    int neighbor;
    int s_out_degree = init_src_nei.size();
    int n_new_edges = new_edges.size();
    int nnodes = g.get_num_nodes();

    // Probably useless.
    if (n_new_edges <= 0) {
        std::cout << "No new edges, Unexpected behaviour\t";
        temp_const = 0;
    }

    // Get average Red pagerank of initial neighbors for nominator.
    nominator_const = 0;
    if (s_out_degree > 0) {
        for (int nei = 0; nei < s_out_degree; nei++) {
            neighbor = init_src_nei[nei];
            nominator_const += init_red_abs_prob[neighbor].pagerank;
        }
        nominator_const *= (1 / (float)s_out_degree);
    } else {
        for (int nei = 0; nei < nnodes; nei++) {
            neighbor = nei;
            nominator_const += init_red_abs_prob[neighbor].pagerank;
        }
        nominator_const *= (1 / (float)nnodes);
    }
    // Get average Red Pagerank of new neighbors.
    for (int nei = 0; nei < n_new_edges; nei++) {
        neighbor = new_edges[nei].destination;
        temp_const += init_red_abs_prob[neighbor].pagerank;
    }
    temp_const *= (1 / (float)n_new_edges);
    nominator_const = temp_const - nominator_const;
    // Get average Source pagerank of neighbors for denominator.
    denominator_const = 0;
    if (s_out_degree > 0) {
        for (int nei = 0; nei < s_out_degree; nei++) {
            neighbor = init_src_nei[nei];
            denominator_const += init_src_abs_prob[neighbor].pagerank;
        }
        denominator_const *= (1 / (float)s_out_degree);
    } else {
        for (int nei = 0; nei < nnodes; nei++) {
            neighbor = nei;
            denominator_const += init_src_abs_prob[neighbor].pagerank;
        }
        denominator_const *= (1 / (float)nnodes);
    }
    // Get average Source pagerank of new neighbors.
    temp_const = 0;
    for (int nei = 0; nei < n_new_edges; nei++) {
        neighbor = new_edges[nei].destination;
        temp_const += init_src_abs_prob[neighbor].pagerank;
    }
    temp_const *= (1 / (float)n_new_edges);
    denominator_const = temp_const - denominator_const;
    // Calculate the Quantity. Not just the important part but
    // all so as to have a sanity check.
    nominator_const *= ((1 - jump_prob) / jump_prob);
    denominator_const *= ((1 - jump_prob) / jump_prob);
    denominator_const = ((s_out_degree + n_new_edges) / (float)n_new_edges) - denominator_const;
    objective_val = init_red_pagerank + init_source_pagerank * (nominator_const / denominator_const);
    // Theory check print.
    if (denominator_const < 0) std::cout << "!!!NEGATIVE DENOMINATOR!!!\n";

    return objective_val;
}

// Get valide edges.
int Edge_addition::get_valide_no_edges(int s_node) {
    int max_edges = (g.get_num_nodes() - 1) - g.get_out_degree(s_node);

    return std::min(n_target, max_edges);
}

// Save vectors.
void Edge_addition::save_vector(std::string file_name, pagerank_v &s_vector) {
    // Declare local variables.
    int n = s_vector.size();

    // Open log file.
    std::ofstream log_file(file_name);

    // Write logs to file.
    log_file << "Edge\tValue\n";
    for (int i = 0; i < n; i++) {
        log_file << s_vector[i].node_id << "\t" << s_vector[i].pagerank << std::endl;
    }

    // Close file.
    log_file.close();
}

void Edge_addition::save_vector(std::string file_name, std::vector<int> &s_vector) {
    // Declare Variables
    int n = s_vector.size();  

    std::ofstream log_file(file_name);
    // Write nodes.
    for (int i = 0; i < n; i++) {
        log_file << s_vector[i] << "\n";
    }
    // Close file.
    log_file.close();
}

void Edge_addition::save_vector(std::string file_name, std::vector<double> &s_vector) {
    // Declare Variables
    int n = s_vector.size();  

    std::ofstream log_file(file_name);
    // Write nodes.
    for (int i = 0; i < n; i++) {
        log_file << s_vector[i] << "\n";
    }
    // Close file.
    log_file.close();
}

void Edge_addition::save_vector(std::string file_name, std::vector<edge> &s_vector) {
    std::ofstream edge_file(file_name);
    int n = s_vector.size();
    for (int i = 0; i < n; i++) {
        edge_file << s_vector[i].source << "\t" << s_vector[i].destination << "\n";
    }
    edge_file.close();
}

void Edge_addition::save_vector(std::string file_name, std::vector<step_log> &s_vector) {
    // Declare local variables.
    int n = s_vector.size();

    // Open log file.
    std::ofstream log_file(file_name);

    // Write logs to file.
    log_file << "Edge\tPagerank\tPrediction\tSum_Prediction\n";
    for (int i = 0; i < n; i++) {
        log_file << i << "\t" << s_vector[i].red_pagerank << "\t" << s_vector[i].red_pagerank_prediction << "\t" << s_vector[i].red_pagerank_generalized_prediction << std::endl;
    }

    // Close file.
    log_file.close();
}

void Edge_addition::add_log_point(std::vector<step_log> &log_vec, double red_pagerank, double prediction, double gen_prediction) {
    step_log log_point;
    log_point.red_pagerank = red_pagerank;
    log_point.red_pagerank_prediction = prediction;
    log_point.red_pagerank_generalized_prediction = gen_prediction;
    log_vec.push_back(log_point);
}