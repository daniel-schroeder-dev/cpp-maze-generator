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

void fill_maze();
void display_maze();
void generate_start_position();
void generate_path();
void calculate_next_position(Direction path_direction);
void blot_position();

Direction get_random_direction();
bool is_valid_direction(Direction path_direction);
Cell **build_maze();
char get_cell_char(Cell cell);

int num_rows;
int num_cols;
int num_moves = 3;

Cell **pptr_maze;
PathBuilder path_builder;

int main() {
    srand(time(NULL));
    num_rows = 5;
    num_cols = 5;
    pptr_maze = build_maze();
    fill_maze();
    generate_start_position();
    display_maze();
    generate_path();
    display_maze();

    std::cout << std::endl;
    return 0;
}

void blot_position() {
    pptr_maze[path_builder.row][path_builder.col] = C_PATH;
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
    while (num_moves > 0) {
        path_direction = get_random_direction();
        while (!is_valid_direction(path_direction)) {
            path_direction = get_random_direction();
        }
        calculate_next_position(path_direction);
        blot_position();
        num_moves--;
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
            return '@';
            break;
        case C_END:
            return '$';
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

void fill_maze() {
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
