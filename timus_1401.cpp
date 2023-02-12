#include <iostream>
#include <tgmath.h>

/*
 *  QUARTERS:
 *  _________
 *  | 1 | 0 |
 *  _________
 *  | 3 | 2 |
 *  _________
 *
 */


int fill_figure(int table[512][512], int quarter_length, int missing_quarter, int figure_number, int col, int row) {
    if (quarter_length == 1) {
        table[row][col] = figure_number;
        table[row][col + 1] = figure_number;
        table[row + 1][col] = figure_number;
        table[row + 1][col + 1] = figure_number;
        switch (missing_quarter) {
            case 0: {
                table[row][col + 1] = 0;
                break;
            }
            case 1: {
                table[row][col] = 0;
                break;
            }
            case 2: {
                table[row + 1][col + 1] = 0;
                break;
            }
            case 3: {
                table[row + 1][col] = 0;
                break;
            }
            default: {
                return -1;
            }
        }
        return figure_number + 1;
    } else {
        int next = figure_number;
        int less_quarter_length = quarter_length / 2;
        switch (missing_quarter) {
            case 0 : {
                next = fill_figure(table, less_quarter_length, 2, next, col, row);
                next = fill_figure(table, less_quarter_length, 0, next, col, row + quarter_length);
                next = fill_figure(table, less_quarter_length, 1, next, col + quarter_length, row + quarter_length);
                next = fill_figure(table, less_quarter_length, 0, next, col + less_quarter_length, row + less_quarter_length);
                break;
            }
            case 1 : {
                next = fill_figure(table, less_quarter_length, 0, next, col, row + quarter_length);
                next = fill_figure(table, less_quarter_length, 1, next, col + quarter_length, row + quarter_length);
                next = fill_figure(table, less_quarter_length, 3, next, col + quarter_length, row);
                next = fill_figure(table, less_quarter_length, 1, next, col + less_quarter_length, row + less_quarter_length);
                break;
            }
            case 2 : {
                next = fill_figure(table, less_quarter_length, 2, next, col, row);
                next = fill_figure(table, less_quarter_length, 0, next, col, row + quarter_length);
                next = fill_figure(table, less_quarter_length, 3, next, col + quarter_length, row);
                next = fill_figure(table, less_quarter_length, 2, next, col + less_quarter_length, row + less_quarter_length);
                break;
            }
            case 3 : {
                next = fill_figure(table, less_quarter_length, 2, next, col, row);
                next = fill_figure(table, less_quarter_length, 3, next, col + quarter_length, row);
                next = fill_figure(table, less_quarter_length, 1, next, col + quarter_length, row + quarter_length);
                next = fill_figure(table, less_quarter_length, 3, next, col + less_quarter_length, row + less_quarter_length);
                break;
            }
            default: {
                return -1;
            }
        }
        return next;
    }
}

void fill_square(int table[512][512] , int square_side, int missing_x, int missing_y, int begin) {
    int square_x_coord = 0;
    int square_y_coord = 0;
    for (int i = square_side / 2; i >= 1; i /= 2) {
        int missing_quarter = 0;
        if (missing_x < square_x_coord + i) {
            missing_quarter++;
        }
        if (missing_y >= square_y_coord + i) {
            missing_quarter += 2;
        }
        begin = fill_figure(table, i, missing_quarter, begin, square_x_coord, square_y_coord);
        if (missing_x >= square_x_coord + i) {
            square_x_coord += i;
        }
        if (missing_y >= square_y_coord + i) {
            square_y_coord += i;
        }
    }
}

void print_square(int table[512][512], int square_size) {
    for (int i = 0; i < square_size; i++) {
        for (int j = 0; j < square_size; j++) {
            std::cout << table[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main(void) {
    int n;
    std::cin >> n;
    int size = pow(2, n);
    int table[512][512];
    int row, col;
    std::cin >> row >> col;
    row--;
    col--;
    fill_square(table, size, col, row, 1);
    print_square(table, size);
    return 0;
}
