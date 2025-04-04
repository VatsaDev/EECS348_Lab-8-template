// /matrix.hpp:
#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <cstdint>
#include <vector>
#include <iostream> // Added for print_matrix (can also be added in .cpp)
#include <stdexcept> // Added for exceptions
#include <iomanip>   // Added for std::setw

class Matrix {
public:
    // Constructors
    Matrix(std::size_t N); // Initialize NxN matrix (e.g., with zeros)
    Matrix(std::vector<std::vector<int>> nums); // Initialize from vector of vectors

    // Operators
    Matrix operator+(const Matrix &rhs) const;
    Matrix operator*(const Matrix &rhs) const;

    // Accessors and Mutators
    void set_value(std::size_t i, std::size_t j, int n); // Task 7
    int get_value(std::size_t i, std::size_t j) const;
    std::size_t get_size() const; // Use std::size_t consistently

    // Operations
    int sum_diagonal_major() const; // Task 4 (Main diagonal)
    int sum_diagonal_minor() const; // Task 4 (Secondary diagonal)
    void swap_rows(std::size_t r1, std::size_t r2); // Task 5
    void swap_cols(std::size_t c1, std::size_t c2); // Task 6

    // Utility
    void print_matrix() const; // Task 1 (Helper)

private:
    std::size_t size_; // Store the size N
    std::vector<std::vector<int>> data_; // Store the matrix elements

    // Helper for bounds checking
    void check_bounds(std::size_t r, std::size_t c) const;
};

#endif // __MATRIX_HPP__
