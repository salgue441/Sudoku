/**
 * @file main.cpp
 * @author Carlos Salguero
 * @brief Main file for the project
 * @version 0.1
 * @date 2022-12-02
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <array>

#include "Sudoku.h"

int main()
{
    std::array<int, 81> puzzle;
    std::array<int, 81> origin;

    Sudoku sudoku;

    sudoku.generate_sudoku(puzzle, 1);
    sudoku.copy_puzzle(puzzle, origin);

    system("cls");

    std::cout << sudoku.print_puzzle(puzzle, false) << std::endl;

    char run;
    std::cout << "Solve puzzle (y/n): ";
    std::cin >> run;

    if (run == 'y' || run == 'Y')
        sudoku.solve_sudoku(puzzle, true);

    sudoku.user_input(puzzle);

    return 0;
}