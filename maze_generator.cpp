#include <iostream>

enum Cell {
    C_EMPTY,
    C_PATH,
    C_BLOCKED
};

Cell **build_maze(int num_rows, int num_cols);
void fill_maze(Cell **pptr_maze);

int num_rows;
int num_cols;

int main() {
    num_rows = 5;
    num_cols = 5;
    Cell **pptr_maze = build_maze(num_rows, num_cols);
    fill_maze(pptr_maze);

    std::cout << std::endl;
    return 0;
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
