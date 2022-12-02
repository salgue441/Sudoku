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
#include <iostream>
#include <sstream>
#include <math.h>
#include <algorithm>
#include <random>
#include <array>
#include <chrono>
#include <stdlib.h>
#include <time.h>
#include <optional>
#include <thread>
#include <Windows.h>

class Sudoku
{
public:
    // Constructor
    Sudoku() = default;

    // Destructor
    ~Sudoku() = default;

    // Access Methods
    const int get_empty_value() const;
    const int get_grid_size() const;
    const int get_solutions() const;

    std::array<int, 9> get_values() const;

    // Functionss
    void generate_sudoku(std::array<int, 81> &,
                         std::optional<int> difficulty = 1);
    void set_cursor(int, int);
    void sleep(const int);
    void copy_puzzle(std::array<int, 81> &, std::array<int, 81> &);
    void user_input(std::array<int, 81> &);

    bool is_valid(std::array<int, 81> &, int, int, int);
    bool has_empty_cell(std::array<int, 81> &, int &, int &);
    bool fill_puzzle(std::array<int, 81> &);
    bool solve_sudoku(std::array<int, 81> &,
                      std::optional<bool> visualize = false);

    std::string print_puzzle(std::array<int, 81> &,
                             std::optional<bool> clear = true);

private:
    const int empty_value = 0;
    const int size = 9;
    int number_of_solutions = 1;

    std::array<int, 9> values{1, 2, 3, 4, 5, 6, 7, 8, 9};

    // Private functions
};

#endif //! SUDOKU_H