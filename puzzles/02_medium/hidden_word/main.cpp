#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

struct Node {
    int id; // id = (row * 100) + column
    char elem;
    int row;
    int column;
};

void DFS(Node node, map<int, bool> visited, char* grid, int h, int w, 
    string word, int index, vector<Node> &solution, int direction,
    bool &solution_found) {
    
    char next = word[index];

    if (!solution_found && node.elem == next) {
        visited[node.id] = true;

        bool correct_dir = direction == 1 || direction == -1;

        if (node.column <= w - 1 && correct_dir && !solution_found) {
            // 1 right
            solution.push_back(node);
            int row = node.row;
            int column = node.column + 1;

            int id = row * 100 + column;

            if (!visited[id]) {
                char elem = *((grid + row * h) + column);

                Node new_node = {id, elem, row, column};

                DFS(new_node, visited, grid, h, w, word,
                    index + 1, solution, 1, solution_found);

                if (solution.size() == word.size()) {
                    solution_found = true;
                } else {
                    index = 0;
                    solution.clear();
                }
            }
        }

        correct_dir = direction == 2 || direction == -1;

        if (node.row <= h - 1 && node.column <= w - 1 && correct_dir && !solution_found) {
            // 2 right/down
            solution.push_back(node);
            int row = node.row + 1;
            int column = node.column + 1;

            int id = row * 100 + column;

            if (!visited[id]) {
                char elem = *((grid + row * h) + column);

                Node new_node = {id, elem, row, column};

                DFS(new_node, visited, grid, h, w, word,
                    index + 1, solution, 2, solution_found);
                
                if (solution.size() == word.size()) {
                    solution_found = true;
                } else {
                    index = 0;
                    solution.clear();
                }
            }
        }
        
        correct_dir = direction == 3 || direction == -1;

        if (node.row <= h - 1 && correct_dir && !solution_found) {
            // 3 down
            solution.push_back(node);
            int row = node.row + 1;
            int column = node.column;

            int id = row * 100 + column;

            if (!visited[id]) {
                char elem = *((grid + row * h) + column);

                Node new_node = {id, elem, row, column};

                DFS(new_node, visited, grid, h, w, word,
                    index + 1, solution, 3, solution_found);

                if (solution.size() == word.size()) {
                    solution_found = true;
                } else {
                    index = 0;
                    solution.clear();
                }
            }
        }

        correct_dir = direction == 4 || direction == -1;

        if (node.row <= h - 1 && node.column >= 0 && correct_dir && !solution_found) {
            // 4 left/down
            solution.push_back(node);
            int row = node.row + 1;
            int column = node.column - 1;

            int id = row * 100 + column;

            if (!visited[id]) {
                char elem = *((grid + row * h) + column);

                Node new_node = {id, elem, row, column};

                DFS(new_node, visited, grid, h, w, word,
                    index + 1, solution, 4, solution_found);

                if (solution.size() == word.size()) {
                    solution_found = true;
                } else {
                    index = 0;
                    solution.clear();
                }
            }
        }

        correct_dir = direction == 5 || direction == -1;

        if (node.column >= 0 && correct_dir && !solution_found) {
            // 5 left
            solution.push_back(node);
            int row = node.row;
            int column = node.column - 1;

            int id = row * 100 + column;

            if (!visited[id]) {
                char elem = *((grid + row * h) + column);

                Node new_node = {id, elem, row, column};

                DFS(new_node, visited, grid, h, w, word,
                    index + 1, solution, 5, solution_found);

                if (solution.size() == word.size()) {
                    solution_found = true;
                } else {
                    index = 0;
                    solution.clear();
                }
            }
        }

        correct_dir = direction == 6 || direction == -1;

        if (node.row >= 0 && node.column >= 0 && correct_dir && !solution_found) {
            // 6 left/up
            solution.push_back(node);
            int row = node.row - 1;
            int column = node.column - 1;

            int id = row * 100 + column;

            if (!visited[id]) {
                char elem = *((grid + row * h) + column);

                Node new_node = {id, elem, row, column};

                DFS(new_node, visited, grid, h, w, word,
                    index + 1, solution, 6, solution_found);

                if (solution.size() == word.size()) {
                    solution_found = true;
                } else {
                    index = 0;
                    solution.clear();
                }
            }
        }

        correct_dir = direction == 7 || direction == -1;

        if (node.row >= 0 && correct_dir && !solution_found) {
            // 7 up
            solution.push_back(node);
            int row = node.row - 1;
            int column = node.column;

            int id = row * 100 + column;

            if (!visited[id]) {
                char elem = *((grid + row * h) + column);

                Node new_node = {id, elem, row, column};

                DFS(new_node, visited, grid, h, w, word,
                    index + 1, solution, 7, solution_found);

                if (solution.size() >= word.size()) {
                    solution_found = true;
                } else {
                    index = 0;
                    solution.clear();
                }
            }
        }

        correct_dir = direction == 8 || direction == -1;

        if (node.row >= 0 && node.column <= w - 1 && correct_dir && !solution_found) {
            // 8 right/up
            solution.push_back(node);
            int row = node.row - 1;
            int column = node.column + 1;

            int id = row * 100 + column;

            if (!visited[id]) {
                char elem = *((grid + row * h) + column);

                Node new_node = {id, elem, row, column};

                DFS(new_node, visited, grid, h, w, word,
                    index + 1, solution, 8, solution_found);

                if (solution.size() == word.size()) {
                    solution_found = true;
                } else {
                    index = 0;
                    solution.clear();
                }
            }
        }
    }
}

void solve(char* grid, int h, int w, string word, vector<char> &solution_grid) {
    vector<Node> solution;
    bool solution_found = false;

    for (int i = 0; i < h && !solution_found; i++) {
        for (int j = 0; j < w && !solution_found; j++) {
            int id = i * 100 + j;
            Node root {id, *((grid + i * h) + j), i, j};
            map<int, bool> visited;

            solution.clear();

            DFS(root, visited, grid, h, w, word, 0,
                solution, -1, solution_found);
        }
    }

    for (Node n : solution) {
        solution_grid[n.row * h + n.column] = ' ';
    }
}

int main() {
    int n;
    cin >> n;
    cin.ignore();

    string list_of_words[n];

    for (int i = 0; i < n; i++) {
        string word;
        cin >> word;
        cin.ignore();
        list_of_words[i] = word;
    }

    for (string s : list_of_words) {
        cerr << s << endl;
    }

    int h, w;
    cin >> h >> w;
    cin.ignore();

    char grid[h][w];

    for (int i = 0; i < h; i++) {
        string row;
        cin >> row;
        cin.ignore();

        for (int j = 0; j < w; j++) {
            grid[i][j] = row[j];
        }
    }

    vector<char> solution_grid;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            solution_grid.push_back(grid[i][j]);
        }
    }

    for (string s : list_of_words) {
        solve((char*)grid, h, w, s, solution_grid);
    }

    for (char c : solution_grid) {
        if (c != ' ') {
            cout << c;
        }
    }
}