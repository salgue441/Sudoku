/**
 * @file Sudoku.h
 * @author Carlos Salguero
 * @brief Declaration of Sudoku Class
 * @version 0.1
 * @date 2022-12-02
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef SUDOKU_H
#define SUDOKU_H

#include <string>
#include <math.h>
#include <algorithm>
#include <random>
#include <array>
#include <chrono>
#include <stdlib.h>
#include <time.h>
#include <optional>
#include <Windows.h>

class Sudoku
{
public:
    // Constructor
    Sudoku() = default;

    // Destructor
    ~Sudoku() = default;

    // Access Methods
    // Functionss
    void generate_sudokue(std::array<int, 81> &,
                          std::optional<int> difficulty = 1);
    void set_cursor(int, int);
    void sleep(const int);
    void print_puzzle(std::array<int, 81> &, std::optional<bool> clear = true);
    void copy_puzzle(std::array<int, 81> &, std::array<int, 81> &);

    bool is_valid(std::array<int, 81> &, int, int, int);
    bool has_empty_cell(std::array<int, 81> &);
    bool fill_puzzle(std::array<int, 81> &);
    bool solve_sudoku(std::array<int, 81> &,
                      std::optional<bool> visualize = false);

private:
    const int empty_value = 0;
    const int size = 9;
    int number_of_solutions = 1;

    std::array<int, 9> values{1, 2, 3, 4, 5, 6, 7, 8, 9};
};

#endif //! SUDOKU_H