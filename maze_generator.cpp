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

Cell **build_maze();
char get_cell_char(Cell cell);

int num_rows;
int num_cols;

Cell **pptr_maze;

int main() {
    srand(time(NULL));
    num_rows = 5;
    num_cols = 5;
    pptr_maze = build_maze();
    fill_maze();
    generate_start_position();
    display_maze();

    std::cout << std::endl;
    return 0;
}

void generate_start_position() {
    int start_row = rand() % num_rows;
    int start_col = rand() % num_rows;
    pptr_maze[start_row][start_col] = C_START;
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
