#include <iostream>
#include <vector>

using namespace std;

class Cell {
    private:
        int row;
        int col;
        char content;
    public:
        Cell() {
            this->row = -1;
            this->col = -1;
            this->content = ' ';
        }

        Cell(int row, int col, char content) {
            this->row = row;
            this->col = col;
            this->content = content;
        }

        int get_row() {
            return this->row;
        }

        int get_col() {
            return this->col;
        }

        char get_content() {
            return this->content;
        }

        void set_row(int row) {
            this->row = row;
        }

        void set_col(int col) {
            this->col = col;
        }

        void set_content(char content) {
            this->content = content;
        }
};

vector<vector<Cell>> map;

enum Direction {
    SOUTH,
    EAST,
    NORTH,
    WEST
};

struct Blunder {
    Cell position;
    Direction direction = SOUTH;
    bool inverter = false;
    bool breaker = false;
    bool loop = false;

    void print_position() {
        cerr << "Blunder's position: ";
        cerr << position.get_row() << " " << position.get_col() << endl; 
    }

} blunder;

vector<string> actions;

void print_map() {
    cerr << "--- BEGIN ---" << endl;
    for (vector<Cell> v : map) {
        for (Cell c : v) {
            cerr << c.get_content();
        }
        cerr << endl;
    }
    cerr << "--- END ---" << endl;
}

void get_starting_position() {
    for (vector v : map) {
        for (Cell c : v) {
            if (c.get_content() == '@') {
                blunder.position = c;
            }
        }
    }
}

void update(int row, int col) {
    blunder.position.set_row(row);
    blunder.position.set_col(col);
    blunder.position.set_content(map[row][col].get_content());
}

void change_direction() {
    Direction direction;
    int next_row, next_col;
    Cell c;

    if (!blunder.inverter) {
        // South
        direction = SOUTH;
        next_row = blunder.position.get_row() + 1;
        next_col = blunder.position.get_col();

        c = map[next_row][next_col];

        while (c.get_content() == '#' || c.get_content() == 'X') {
            if (direction == SOUTH) {
                // East
                next_row = blunder.position.get_row();
                next_col = blunder.position.get_col() + 1;
                direction = EAST;
            } else if (direction == EAST) {
                // North
                next_row = blunder.position.get_row() - 1;
                next_col = blunder.position.get_col();
                direction = NORTH;
            } else if (direction == NORTH) {
                // West
                next_row = blunder.position.get_row();
                next_col = blunder.position.get_col() - 1;
                direction = SOUTH;
            }
            c = map[next_row][next_col];
        }
    } else {
        // West
        direction = WEST;
        next_row = blunder.position.get_row();
        next_col = blunder.position.get_col() - 1;

        c = map[next_row][next_col];

        while (c.get_content() == '#' || c.get_content() == 'X') {
            if (direction == WEST) {
                // North
                next_row = blunder.position.get_row() - 1;
                next_col = blunder.position.get_col();
                direction = NORTH;
            } else if (direction == NORTH) {
                // East
                next_row = blunder.position.get_row();
                next_col = blunder.position.get_col() + 1;
                direction = EAST;
            } else if (direction == EAST) {
                // South
                next_row = blunder.position.get_row() + 1;
                next_col = blunder.position.get_col();
                direction = WEST;
            }
            c = map[next_row][next_col];
        }
    }
    blunder.direction = direction;
    update(next_row, next_col);
}

void path_modifier(char c) {
    switch (c) {
        case 'S': {
            blunder.direction = SOUTH;
            break;
        }
        case 'E': {
            blunder.direction = EAST;
            break;
        }
        case 'N': {
            blunder.direction = NORTH;
            break;
        } case 'W': {
            blunder.direction = WEST;
            break;
        }
        default:
            cerr << "Error in switch" << endl;
            break;
    }
}

void destroy(int row, int column) {
    cerr << "Destroy: " << row << " " << column << endl; 
    map[row][column].set_content(' ');
}

void next_position() {
    int next_row = 0;
    int next_col = 0;

    switch (blunder.direction) {
        case SOUTH: {
            next_row = blunder.position.get_row() + 1;
            next_col = blunder.position.get_col();
            break;
        }
        case EAST: {
            next_row = blunder.position.get_row();
            next_col = blunder.position.get_col() + 1;
            break;
        }
        case NORTH: {
            next_row = blunder.position.get_row() - 1;
            next_col = blunder.position.get_col();
            break;
        }
        case WEST: {
            next_row = blunder.position.get_row();
            next_col = blunder.position.get_col() - 1;
            break;
        }
        default: {
            cerr << "Error in switch" << endl;
            break;
        }
    }

    Cell cell = map[next_row][next_col];
    char c = cell.get_content();

    if (c == '#' || c == 'X' && !blunder.breaker) {
        change_direction();
    } else if (c == 'X' && blunder.breaker) {
        destroy(next_row, next_col);
        update(next_row, next_col);
    } else {
        update(next_row, next_col);
    }
}

void move() {
    switch (blunder.direction) {
        case SOUTH: {
            actions.push_back("SOUTH");
            break;
        }
        case EAST: {
            actions.push_back("EAST");
            break;
        }
        case NORTH: {
            actions.push_back("NORTH");
            break;
        }
        case WEST: {
            actions.push_back("WEST");
            break;
        }
        default: {
            cerr << "Error in switch" << endl;
        }
    }
}

void teleport(Cell from) {
    int row = from.get_row();
    int col = from.get_col();
    bool exit = false;

    for (vector v : map) {
        for (Cell c : v) {
            if (c.get_content() == 'T' &&
                (c.get_row() != row || c.get_col() != col)) {
                update(c.get_row(), c.get_col());
                exit = true;
            }
            if (exit) {
                break;
            }
        }
        if (exit) {
            break;
        }
    }
}

bool is_dead() {
    return blunder.position.get_content() == '$';
}

int main() {
    int l, c;
    cin >> l >> c;
    cin.ignore();

    for (int i = 0; i < l; i++) {
        string row;
        getline(cin, row);
        vector<Cell> row_vector;
        for (int j = 0; j < c; j++) {
            Cell c(i, j, row[j]);
            row_vector.push_back(c);
        }
        map.push_back(row_vector);
    }

    get_starting_position();

    int turn = 1;

    while (!is_dead() && !blunder.loop) {
        Cell cell = map[blunder.position.get_row()][blunder.position.get_col()];
        char c = cell.get_content();

        if (c == 'S' || c == 'E' || c == 'N' || c == 'W') {
            path_modifier(c);
        }

        if (c == 'I') {
            if (!blunder.inverter) {
                blunder.inverter = true;
            } else {
                blunder.inverter = false;
            }
        }

        if (c == 'B') {
            if (!blunder.breaker) {
                blunder.breaker = true;
            } else {
                blunder.breaker = false;
            }
        }

        if (c == 'T') {
            teleport(cell);
        }

        if (turn == 1000) {
            blunder.loop = true;
        }
        
        next_position();
        move();
        turn++;
    }

    if (blunder.loop) {
        cout << "LOOP" << endl;
    } else {
        for (string s : actions) {
            cout << s << endl;
        }
    }
}