#include <iostream>

enum Cell {
    C_EMPTY,
    C_PATH,
    C_BLOCKED
};

Cell **build_maze(int num_rows, int num_cols);

int main() {
    int num_rows = 5;
    int num_cols = 5;
    Cell **pptr_maze = build_maze(num_rows, num_cols);

    std::cout << std::endl;
    return 0;
}

Cell **build_maze(int num_rows, int num_cols) {
    Cell **pptr_maze = new Cell*[num_rows];
    for (int row = 0; row < num_rows; row++) {
        pptr_maze[row] = new Cell[num_cols];
    }
    return pptr_maze;
}
