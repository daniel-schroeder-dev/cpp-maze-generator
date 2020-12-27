#include <iostream>
#include <cstdlib>
#include <ctime>

enum Cell {
    C_EMPTY,
    C_PATH,
    C_BLOCKED,
    C_START,
    C_END
};

enum Direction {
    D_UP,
    D_DOWN,
    D_LEFT,
    D_RIGHT
};

struct PathBuilder {
    int row;
    int col;
};

void fill_maze_with_empty_cells();
void display_maze();
void generate_start_position();
void generate_path();
void calculate_next_position(Direction path_direction);
void blot_position(bool set_end_cell);
void wall_empty_cells();

Direction get_random_direction();
bool is_valid_direction(Direction path_direction);
bool is_empty_cell(Direction path_direction);
bool on_edge_cell();
Cell **build_maze();
char get_cell_char(Cell cell);

int num_rows;
int num_cols;
int num_moves;

Cell **pptr_maze;
PathBuilder path_builder;

int main() {
    srand(time(NULL));
    /*
    *   These should be passed in at runtime!
    */
    num_rows = 5;
    num_cols = 5;
    num_moves = (num_rows * num_cols) / 3;
    pptr_maze = build_maze();

    fill_maze_with_empty_cells();
    generate_start_position();
    generate_path();
    wall_empty_cells();
    display_maze();

    std::cout << std::endl;
    return 0;
}

void wall_empty_cells() {
    for (int row = 0; row < num_rows; row++) {
        for (int col = 0; col < num_cols; col++) {
            if (pptr_maze[row][col] == C_EMPTY) {
                pptr_maze[row][col] = C_BLOCKED;
            }
        }
    }
}

bool on_edge_cell() {
    if (path_builder.col == 0) return true;
    else if (path_builder.col == num_cols - 1) return true;
    else if (path_builder.row == 0) return true;
    else if (path_builder.row == num_rows - 1) return true;
    return false;
}

bool is_empty_cell(Direction path_direction) {
    Cell next_cell = C_EMPTY;
    switch (path_direction) {
        case D_UP:
            next_cell = pptr_maze[path_builder.row-1][path_builder.col];
            break;
        case D_DOWN:
            next_cell = pptr_maze[path_builder.row+1][path_builder.col];
            break;
        case D_LEFT:
            next_cell = pptr_maze[path_builder.row][path_builder.col-1];
            break;
        case D_RIGHT:
            next_cell = pptr_maze[path_builder.row][path_builder.col+1];
            break;
    }
    return next_cell == C_EMPTY;
}

void blot_position(bool set_end_cell) {
    Cell cell = set_end_cell ? C_END : C_PATH;
    pptr_maze[path_builder.row][path_builder.col] = cell;
}

bool is_valid_direction(Direction path_direction) {
    switch (path_direction) {
        case D_UP:
            return path_builder.row - 1 >= 0;
            break;
        case D_DOWN:
            return path_builder.row + 1 < num_rows;
            break;
        case D_LEFT:
            return path_builder.col - 1 >= 0;
            break;
        case D_RIGHT:
            return path_builder.col + 1 < num_cols;
            break;
        default:
            return false;
    }
}

void calculate_next_position(Direction path_direction) {
    switch (path_direction) {
        case D_UP:
            path_builder.row -= 1;
            break;
        case D_DOWN:
            path_builder.row += 1;
            break;
        case D_LEFT:
            path_builder.col -= 1;
            break;
        case D_RIGHT:
            path_builder.col += 1;
            break;
    }
}

Direction get_random_direction() {
    switch (rand() % 4) {
        case 0:
            return D_UP;
            break;
        case 1:
            return D_DOWN;
            break;
        case 2:
            return D_LEFT;
            break;
        case 3:
            return D_RIGHT;
            break;
        default:
            return D_UP;
            break;
    }
}

void generate_path() {
    Direction path_direction;
    bool set_end_cell = false;
    int num_invalid_tries = 0;
    while (!set_end_cell) {
        path_direction = get_random_direction();
        while (!is_valid_direction(path_direction) || !is_empty_cell(path_direction)) {
            path_direction = get_random_direction();
            num_invalid_tries++;
            if (num_invalid_tries > 20) {
                fill_maze_with_empty_cells();
                generate_start_position();
                path_direction = get_random_direction();
                num_moves = (num_rows * num_cols) / 3;
            }
        }
        calculate_next_position(path_direction);
        if (num_moves < 0 && on_edge_cell()) {
            set_end_cell = true;
        }
        blot_position(set_end_cell);
        num_moves--;
        num_invalid_tries = 0;
    }
}

void generate_start_position() {
    int start_row = rand() % num_rows;
    int start_col = rand() % num_rows;
    pptr_maze[start_row][start_col] = C_START;
    path_builder.row = start_row;
    path_builder.col = start_col;
}

char get_cell_char(Cell cell) {
    switch (cell) {
        case C_EMPTY:
            return ' ';
            break;
        case C_PATH:
            return '+';
            break;
        case C_BLOCKED:
            return '#';
            break;
        case C_START:
            return 'S';
            break;
        case C_END:
            return 'E';
            break;
        default:
            return '!';
            break;
    }
}

void display_maze() {
    std::cout << "\n\n";
    for (int row = 0; row < num_rows; row++) {
        for (int col = 0; col < num_cols; col++) {
            std::cout << " | " << get_cell_char(pptr_maze[row][col]);
        }
        std::cout << " | \n";
    }
}

void fill_maze_with_empty_cells() {
    for (int row = 0; row < num_rows; row++) {
        for (int col = 0; col < num_cols; col++) {
            pptr_maze[row][col] = C_EMPTY;
        }
    }
}

Cell **build_maze() {
    Cell **pptr_maze = new Cell*[num_rows];
    for (int row = 0; row < num_rows; row++) {
        pptr_maze[row] = new Cell[num_cols];
    }
    return pptr_maze;
}
