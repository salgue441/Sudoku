/**
 * @file Sudoku.cpp
 * @author Carlos Salguero
 * @brief Implementation of Sudoku Class
 * @version 0.1
 * @date 2022-12-02
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "Sudoku.h"

// Access Methods
/**
 * @brief
 * Gets the empty value of the sudoku puzzle
 * @return const int
 */
const int Sudoku::get_empty_value() const
{
    return empty_value;
}

/**
 * @brief
 * Gets the size of the sudoku puzzle
 * @return const int
 */
const int Sudoku::get_grid_size() const
{
    return size;
}

/**
 * @brief
 * Gets the number of solutions of the sudoku puzzle
 * @return const int
 */
const int Sudoku::get_solutions() const
{
    return number_of_solutions;
}

/**
 * @brief
 * Gets the values of the sudoku puzzle
 * @return std::array<int, 9>
 */
std::array<int, 9> Sudoku::get_values() const
{
    return values;
}

// Functions
/**
 * @brief
 * Generates a sudoku puzzle.
 * @param puzzle The puzzle to be generated
 * @param difficulty The difficulty of the puzzle
 * @return void
 * @complexity O(n^2)
 */
void Sudoku::generate_sudoku(std::array<int, 81> &puzzle,
                             std::optional<int> difficulty)
{
    // Fill the puzzle with empty values
    std::fill(puzzle.begin(), puzzle.end(), empty_value);

    // Fill the puzzle with random values
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            int value = rand() % 9 + 1;

            while (!is_valid(puzzle, i, j, value))
                value = rand() % 9 + 1;

            puzzle[i * size + j] = value;
        }
    }

    // Remove values from the puzzle
    int number_of_cells = size * size;
    int number_of_cells_to_remove = number_of_cells - difficulty.value();

    for (int i = 0; i < number_of_cells_to_remove; i++)
    {
        int row = rand() % size;
        int col = rand() % size;

        while (puzzle[row * size + col] == empty_value)
        {
            row = rand() % size;
            col = rand() % size;
        }

        puzzle[row * size + col] = empty_value;
    }
}

/**
 * @brief
 * Sets the cursor position. Prevents the terminal from flickering
 * when animating the solution.
 * @param x X position
 * @param y Y position
 * @return void
 * @complexity O(1)
 */
void Sudoku::set_cursor(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/**
 * @brief
 * Sleeps the program for a given amount of time.
 * @param ms Time in milliseconds
 * @return void
 * @complexity O(1)
 */
void Sudoku::sleep(const int ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

/**
 * @brief
 * Copies a puzzle to another puzzle.
 * @param puzzle Puzzle to copy from
 * @param copy Puzzle to copy to
 * @return void
 * @complexity O(n)
 */
void Sudoku::copy_puzzle(std::array<int, 81> &puzzle, std::array<int, 81> &copy)
{
    for (auto const &i : puzzle)
        for (auto const &j : puzzle)
            copy[i * 9 + j] = puzzle[i * 9 + j];
}

/**
 * @brief
 * Allows the user to solve the puzzle.
 * @param puzzle The puzzle to be solved
 * @return void
 * @complexity O(n^2)
 */
void Sudoku::user_input(std::array<int, 81> &puzzle)
{
    int row, col, value;

    std::cout << "Enter row: ";
    std::cin >> row;

    std::cout << "Enter col: ";
    std::cin >> col;

    std::cout << "Enter value: ";
    std::cin >> value;

    puzzle[row * 9 + col] = value;
}

/**
 * @brief
 * Checks if a value is valid in a given position.
 * @param puzzle Puzzle to check
 * @param row Row to check
 * @param col Column to check
 * @param value Value to check
 * @return true If the value is valid
 * @return false If the value is not valid
 * @complexity O(1)
 */
bool Sudoku::is_valid(std::array<int, 81> &puzzle, int row, int col, int value)
{
    for (auto const &i : puzzle)
        if (puzzle[row * 9 + i] == value || puzzle[i * 9 + col] == value)
            return false;

    auto row_start = (row / 3) * 3;
    auto col_start = (col / 3) * 3;

    for (auto const &i : puzzle)
        for (auto const &j : puzzle)
            if (puzzle[(row_start + i) * 9 + col_start + j] == value)
                return false;

    return true;
}

/**
 * @brief
 * Checks if the puzzle has an empty value.
 * @param puzzle puzzle to check
 * @param row row to check
 * @param col column to check
 * @return true if the puzzle has an empty cell
 * @return false if the puzzle does not have an empty cell
 * @complexity O(n^2)
 */
bool Sudoku::has_empty_cell(std::array<int, 81> &puzzle, int &row, int &col)
{
    for (auto const &i : puzzle)
        for (auto const &j : puzzle)
            if (puzzle[i * 9 + j] == empty_value)
            {
                row = i;
                col = j;
                return true;
            }

    return false;
}

/**
 * @brief
 * Fills the puzzle with valid values.
 * @param puzzle Puzzle to fill
 * @return true If the puzzle is filled
 * @return false If the puzzle is not filled
 * @note This function is recursive.
 * @complexity O(n^2)
 */
bool Sudoku::fill_puzzle(std::array<int, 81> &puzzle)
{
    int row, col;

    if (!has_empty_cell(puzzle, row, col))
        return true;

    for (auto const &i : puzzle)
    {
        if (is_valid(puzzle, row, col, i))
        {
            puzzle[row * 9 + col] = i;

            if (fill_puzzle(puzzle))
                return true;

            puzzle[row * 9 + col] = empty_value;
        }
    }

    return false;
}

/**
 * @brief
 * Solves the sudoku puzzle using backtracking algorithm.
 * @param puzzle Puzzle to solve
 * @return true If the puzzle is solved
 * @return false If the puzzle is not solved
 * @note This function is recursive.
 * @complexity O(9^(n*n))
 */
bool Sudoku::solve_sudoku(std::array<int, 81> &puzzle,
                          std::optional<bool> visualize)
{
    int row, col;

    if (!has_empty_cell(puzzle, row, col))
    {
        number_of_solutions++;
        return true;
    }

    for (auto const &i : puzzle)
    {
        if (is_valid(puzzle, row, col, i))
        {
            puzzle[row * 9 + col] = i;

            if (visualize.value_or(false))
            {
                set_cursor(0, 0);
                print_puzzle(puzzle);
                sleep(10);
            }

            if (solve_sudoku(puzzle, visualize))
                return true;

            puzzle[row * 9 + col] = empty_value;
        }
    }

    return false;
}

/**
 * @brief
 * Prints the puzzle to the console.
 * @param puzzle Puzzle to print
 * @return void
 * @complexity O(n^2)
 */
std::string Sudoku::print_puzzle(std::array<int, 81> &puzzle,
                                 std::optional<bool> clear)
{
    std::stringstream ss;

    if (clear.value_or(false))
        system("cls");

    for (auto const &i : puzzle)
    {
        if (i % 9 == 0)
            ss << std::endl;

        if (puzzle[i] == empty_value)
            ss << "  ";
        else
            ss << puzzle[i] << " ";

        if ((i + 1) % 3 == 0)
            ss << " ";
    }

    ss << std::endl;

    return ss.str();
}