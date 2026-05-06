#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class Node {
    private:
        int id;
        int h;
        vector<int> ady;

    public:
        Node() {}

        Node(int _id, int _h) {
            id = _id;
            h = _h;
        }

        int get_id() {
            return id;
        }

        int get_h() {
            return h;
        }

        vector<int> get_ady() {
            return ady;
        }

        void insert_ady(int n) {
            ady.push_back(n);
        }

        // [ id, h(n)=h ]
        // ( a_1, a_2, ..., a_3 )
        void print_node() {
            unsigned  i = 0;
            cerr << "[ " << id << ", h(n)=" << h << " ]" << endl;
            cerr << "( "; 
            for (int n : ady) {
                cerr << n;
                if (i != ady.size() - 1) {
                    cerr << ", ";
                }
                i++;
            }
            cerr << " )" << endl;
        }
};

class Edge {
    private:
        int x;
        int y;
        int cost;
    
    public:
        Edge() {}

        Edge(int _x, int _y, int _cost) {
            x = _x;
            y = _y;
            cost = _cost;
        }

        int get_x() {
            return x;
        }

        int get_y() {
            return y;
        }

        int get_cost() {
            return cost;
        }

        // [ x->y=cost ]
        void print_edge() {
            cerr << "[ " << x << "->" << y << "=" << cost << " ]" << endl; 
        }
};

struct State{
    int parent_node;
    int actual_node;
    int current_cost;
    int f;
};

int start_node;
int goal_node;
vector<Node> nodes;
vector<Edge> edges;
vector<State> expanded_nodes;
vector<State>  unexplored_nodes;
set<int> visited;

Node search_node(int id) {
    Node found;
    for (Node n : nodes) {
        if (id == n.get_id()) {
            found = n;
        }
    }
    return found;
}

vector<Edge> search_edge(int x, int y) {
    vector<Edge> found;
    for (Edge e : edges) {
        if ((x == e.get_x() && y == e.get_y()) || 
            (x == e.get_y() && y == e.get_x())) {
                
            found.push_back(e);
        }
    }
    return found;
}

State search_state(int id) {
    State found;
    for (State s : expanded_nodes) {
        if (id == s.actual_node) {
            found = s;
        }
    }
    return found;
}

State search_unexplored_node(int id) {
    State found;
    for (State s : unexplored_nodes) {
        if (id == s.actual_node) {
            found = s;
        }
    }
    return found;
}

int search_unexplored_node_index(int id) {
    int index = -1;
    int i = 0;
    for (State s : unexplored_nodes) {
        if (id == s.actual_node) {
            index = i;
        }
        i++;
    }
    return index;
}

void print_expanded_nodes() {
    cerr << "EXPANDED NODES" << endl;
    for (State s : expanded_nodes) {
        cerr << s.parent_node << " " << s.actual_node << " ";
        cerr << s.current_cost << " " << s.f << endl;
    }
}

void print_unexplored_nodes() {
    cerr << "UNEXPLORED NODES" << endl;
    for (State s : unexplored_nodes) {
        cerr << s.parent_node << " " << s.actual_node << " ";
        cerr << s.current_cost << " " << s.f << endl;
    }
}

void a_star() {
    State current_state = unexplored_nodes[0]; // Starting node
    bool first_iteration = true;

    while (!unexplored_nodes.empty()) {
        print_unexplored_nodes();

        Node best_node;
        int best_f = INT32_MAX;

        // Find node to expand
        for (State s : unexplored_nodes) {
            int g = 0;

            if (!first_iteration) {
                int lowest_cost = INT32_MAX;

                for (Edge e : search_edge(s.parent_node, s.actual_node)) {
                    if (e.get_cost() < lowest_cost) {
                        lowest_cost = e.get_cost();
                    }
                }
                g = search_state(s.parent_node).current_cost + lowest_cost;
            }

            int f = g + search_node(s.actual_node).get_h();

            if (f < best_f || (f == best_f && s.actual_node < best_node.get_id())) {

                best_f = f;
                best_node = search_node(s.actual_node);
                current_state.parent_node = s.parent_node;
                current_state.current_cost = s.current_cost;
                current_state.f = f;
            }
            current_state.actual_node = best_node.get_id();
        }

        Node target = search_node(current_state.actual_node);

        if (target.get_id() == goal_node) {
            expanded_nodes.push_back(current_state);
            print_expanded_nodes();
            break;
        }

        // Remove the node that is expanded from the list
        int index = search_unexplored_node_index(target.get_id());

        cerr << "Remove node: " << target.get_id() << " Remove index: " << index << endl;

        if (index != -1) {
            unexplored_nodes.erase(unexplored_nodes.begin() + index);
        }

        if (!visited.insert(target.get_id()).second) {
            continue;
        }

        // Add the adyacents from the current node to the
        // unexplored set if it isn't there yet or
        // update its cost
        for (int a : target.get_ady()) {
            bool found = false;
            int i = 0;

            if (a != current_state.parent_node) {
                for (State s : unexplored_nodes) {
                    if (s.actual_node == a) {
                        found = true;
                        int lowest_cost = INT32_MAX;

                        for (Edge e : search_edge(current_state.actual_node, a)) {
                            if (e.get_cost() < lowest_cost) {
                                lowest_cost = e.get_cost();
                            }
                        }

                        int cost = current_state.current_cost + lowest_cost;
                        int f = cost + search_node(a).get_h();

                        cerr << "new cost: " << a  << " " << cost << endl;

                        if (cost < unexplored_nodes[i].current_cost) {
                            unexplored_nodes[i].current_cost = cost;
                            unexplored_nodes[i].f = f;
                            unexplored_nodes[i].parent_node = current_state.actual_node;
                        }
                    }
                    i++;  
                }
                if (!found) {
                    State new_state;
                    new_state.parent_node = target.get_id();
                    new_state.actual_node = a;
                    int lowest_cost = INT32_MAX;

                    for (Edge e : search_edge(new_state.parent_node, new_state.actual_node)) {
                        if (e.get_cost() < lowest_cost) {
                            lowest_cost = e.get_cost();
                        }
                    }
                    new_state.current_cost = current_state.current_cost + lowest_cost;
                    new_state.f = 
                        new_state.current_cost +
                        search_node(new_state.actual_node).get_h();
                    unexplored_nodes.push_back(new_state);
                }
            }
        }
        expanded_nodes.push_back(current_state);
        print_expanded_nodes();
        first_iteration = false;
    }
}

void solve() {
    Node start = search_node(start_node);
    State s;
    s.parent_node = -1;
    s.actual_node = start.get_id();
    s.current_cost = 0;
    s.f = start.get_h();
    unexplored_nodes.push_back(s);
    a_star();
}

int main() {
    int number_nodes, number_edges;

    cin >> number_nodes >> number_edges >> start_node >> goal_node;
    cin.ignore();

    for (int i = 0; i < number_nodes; i++) {
        int h;
        cin >> h;
        cin.ignore();

        Node n(i, h);
        nodes.push_back(n);
    }

    for (int i = 0; i < number_edges; i++) {
        int x, y, c;

        cin >> x >> y >> c;
        cin.ignore();

        Edge e(x, y, c);
        edges.push_back(e);

        int j = 0;
        for (Node n : nodes) {
            if (n.get_id() == x) {
                nodes[j].insert_ady(y);
            }
            if (n.get_id() == y) {
                nodes[j].insert_ady(x);
            }
            j++;
        }
    }

    cerr << "PRINTING NODES" << endl;
    for (Node n : nodes) {
        n.print_node();
        cerr << endl;
    }

    solve();

    cerr << "EXPANDED NODES" << endl;
    for (State s : expanded_nodes) {
        cerr << s.parent_node << " " << s.actual_node << " " << s.current_cost << " " << s.f << endl;
    }
    cerr << endl;

    cerr << "SOLUTION" << endl;
    for (State s : expanded_nodes) {
        cout << s.actual_node << " " << s.f << endl;
    }
}
