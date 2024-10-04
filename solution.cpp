#include <iostream>
#include <vector>
#include <set>

// input format
// n_vertexes, m_edges // list of m edges below
// a b // edge a<->b // and so on

struct Edge {
Edge(int a, int b, int next_edge) : a(a), b(b), next_edge(next_edge) {}
int a, b, next_edge;
};

struct klateman_vest_algo {
klateman_vest_algo() { // initialize graph
    std::cin >> n >> m;
    edges.reserve(2 * m); // a -> b and b -> a
    heads.resize(n, -1);
    degrees.resize(n, 0);
    best_vertex = -1;
    for (int i = 0; i < 2 * m; i += 2) {
        int a, b;
        std::cin >> a >> b;
        // --a; --b;

        edges.push_back(Edge(a, b, heads[a]));
        heads[a] = i;

        edges.push_back(Edge(b, a, heads[b]));
        heads[b] = i + 1;

        if (++(degrees[a]) > 3) best_vertex = a;
        if (++(degrees[b]) > 3) best_vertex = b;
    }
    tree_degrees.resize(n, 0);
}

void select_base_tree() { // create F_0
    if (best_vertex != -1) {
        for (int i = heads[best_vertex]; i != -1; i = edges[i].next_edge) {
            taken_edges.insert(i);
            taken_vertexes.insert(edges[i].b);
            cur_leafs.insert(edges[i].b);
        }
        taken_vertexes.insert(best_vertex);
    } else {
        int s = 0;
        for (int i = heads[s]; i != -1; i = edges[i].next_edge) {
            taken_edges.insert(i);
            taken_vertexes.insert(edges[i].b);
            cur_leafs.insert(edges[i].b);
        }
        taken_vertexes.insert(s);

        int dead_vertex = -1;
        for (int i = heads[s]; i != -1; i = edges[i].next_edge) {
            bool is_dead_vertex = true;
            for (int j = heads[edges[i].b]; j != -1; j = edges[j].next_edge) {
                if (taken_vertexes.count(edges[j].b) == 0) {
                    is_dead_vertex = false;
                    break;
                }
            }
            if (is_dead_vertex) {
                dead_vertex = edges[i].b;
                break;
            }
        }
        if (dead_vertex != -1) return;
        // otherwise there are no dead vertexes. let's get all neighbors of edges[heads[s]].b
        int s_neighbor = edges[heads[s]].b;
        cur_leafs.erase(s_neighbor);
        for (int i = heads[s_neighbor]; i != -1; i = edges[i].next_edge) {
            if (taken_vertexes.count(edges[i].b) == 0) {
                taken_edges.insert(i);
                taken_vertexes.insert(edges[i].b);
                cur_leafs.insert(edges[i].b);
            }
        }
    }
}

bool have_s1() {
    bool succes = false;
    for (auto v : taken_vertexes) {
        if (cur_leafs.count(v) == 0) {
            for (int i = heads[v]; i != -1; i = edges[i].next_edge) {
                if (taken_vertexes.count(edges[i].b) == 0) {
                    taken_edges.insert(i);
                    taken_vertexes.insert(edges[i].b);
                    cur_leafs.insert(edges[i].b);

                    succes = true;
                    goto done;
                }
            }
        }
    }
done:
    return succes;
}

bool have_s2() {
    std::vector<int> ys(2, -1);
    std::vector<int> ys_edges(2, -1);

    int j = 0;
    bool succes = false;
    int leaf_removed;
    for (auto leaf : cur_leafs) {
        leaf_removed = leaf;
        ys[0] = ys[1] = -1;
        ys_edges[0] = ys_edges[1] = -1;
        j = 0;
        for (int i = heads[leaf]; i != -1; i = edges[i].next_edge) {
            if (taken_vertexes.count(edges[i].b) == 0) {
                ys[j] = edges[i].b;
                ys_edges[j] = i;
                if ((++j) == 2) {
                    succes = true;
                    goto done;
                }
            }
        }
    }
done:
    if (succes) {
        taken_vertexes.insert(ys[0]);
        taken_vertexes.insert(ys[1]);

        taken_edges.insert(ys_edges[0]);
        taken_edges.insert(ys_edges[1]);

        cur_leafs.erase(leaf_removed);
        cur_leafs.insert(ys[0]);
        cur_leafs.insert(ys[1]);
    }
    return succes;
}

bool have_s3() {
    std::vector<int> ys(2, -1);
    std::vector<int> ys_edges(2, -1);

    int j = 0;
    bool succes = false;
    int y;
    int y_edge;
    int leaf_removed;
    for (auto leaf : cur_leafs) {
        leaf_removed = leaf;
        for (int i = heads[leaf]; i != -1; i = edges[i].next_edge) {
            y = edges[i].b;
            y_edge = i;
            if (taken_vertexes.count(y) == 0) {
                ys[0] = ys[1] = -1;
                ys_edges[0] = ys_edges[1] = -1;
                j = 0;
                for (int k = heads[y]; k != -1; k = edges[k].next_edge) {
                    if (taken_vertexes.count(edges[k].b) == 0) {
                        ys[j] = edges[k].b;
                        ys_edges[j] = k;
                        if ((++j) == 2) {
                            succes = true;
                            goto done;
                        }
                    }
                }
            }
        }
    }
done:
    if (succes) {
        taken_vertexes.insert(y);
        taken_vertexes.insert(ys[0]);
        taken_vertexes.insert(ys[1]);

        taken_edges.insert(y_edge);
        taken_edges.insert(ys_edges[0]);
        taken_edges.insert(ys_edges[1]);

        cur_leafs.erase(leaf_removed);
        cur_leafs.insert(ys[0]);
        cur_leafs.insert(ys[1]);
    }
    return succes;
}

bool have_s4() {
    for (auto leaf : cur_leafs) {
        for (int i = heads[leaf]; i != -1; i = edges[i].next_edge) {
            if (taken_vertexes.count(edges[i].b) == 0) {
                taken_vertexes.insert(edges[i].b);
                taken_edges.insert(i);
                cur_leafs.erase(leaf);
                cur_leafs.insert(edges[i].b);
                return true;
            }
        }
    }
    return false;
}

void do_step() { // try do s1, s2, s3, s4
    if (have_s1()) {
        return;
    } else if (have_s2()) {
        return;
    } else if (have_s3()) {
        return;
    } else if (have_s4()) {
        return;
    }
}

void select_tree() {
    while (taken_vertexes.size() < n) do_step();
}

void print_result() {
    for (auto edge_index : taken_edges) {
        tree_degrees[edges[edge_index].a]++;
        tree_degrees[edges[edge_index].b]++;
    }
    int leafs_count = 0;
    for (auto degree : tree_degrees) {
        if (degree == 1) {
            leafs_count++;
        }
    }
    std::cout << leafs_count;
}


int n, m;
std::vector<Edge> edges; // list of edges
std::vector<int> heads; // first edge for vertexes
std::vector<int> degrees; // degrees for vertexes
int best_vertex; // vertex with 4 degree (for base tree)

std::set<int> taken_edges; // list of edges, taken to tree
std::set<int> taken_vertexes;
std::set<int> cur_leafs;

std::vector<int> tree_degrees; // degrees for vertexes of taken tree
};

int main() {
	klateman_vest_algo solution;
    solution.select_base_tree();
    solution.select_tree();
    solution.print_result();

    return 0;
}