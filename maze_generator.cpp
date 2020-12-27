#include <iostream>

enum Cell {
    C_EMPTY,
    C_PATH,
    C_BLOCKED,
    C_START,
    C_END
};

Cell **build_maze(int num_rows, int num_cols);
void fill_maze(Cell **pptr_maze);
void display_maze(Cell **pptr_maze);
char get_cell_char(Cell cell);

int num_rows;
int num_cols;

int main() {
    num_rows = 5;
    num_cols = 5;
    Cell **pptr_maze = build_maze(num_rows, num_cols);
    fill_maze(pptr_maze);
    display_maze(pptr_maze);

    std::cout << std::endl;
    return 0;
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

void display_maze(Cell **pptr_maze) {
    for (int row = 0; row < num_rows; row++) {
        for (int col = 0; col < num_cols; col++) {
            std::cout << " | " << get_cell_char(pptr_maze[row][col]);
        }
        std::cout << " | \n";
    }
}

void fill_maze(Cell **pptr_maze) {
    for (int row = 0; row < num_rows; row++) {
        for (int col = 0; col < num_cols; col++) {
            pptr_maze[row][col] = C_EMPTY;
        }
    }
}

Cell **build_maze(int num_rows, int num_cols) {
    Cell **pptr_maze = new Cell*[num_rows];
    for (int row = 0; row < num_rows; row++) {
        pptr_maze[row] = new Cell[num_cols];
    }
    return pptr_maze;
}
