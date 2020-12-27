#include <iostream>

char **build_maze(int num_rows, int num_cols);

int main() {
    int num_rows = 5;
    int num_cols = 5;
    char **pptr_maze = build_maze(num_rows, num_cols);

    std::cout << std::endl;
    return 0;
}

char **build_maze(int num_rows, int num_cols) {
    char **pptr_maze = new char*[num_rows];
    for (int row = 0; row < num_rows; row++) {
        pptr_maze[row] = new char[num_cols];
    }
    return pptr_maze;
}
