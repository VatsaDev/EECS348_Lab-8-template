// /matrix.cpp:
#include "matrix.hpp"
#include <vector>
#include <stdexcept> // For std::out_of_range, std::invalid_argument
#include <iostream>  // For std::cout, std::endl
#include <iomanip>   // For std::setw
#include <utility>   // For std::swap

// --- Helper Functions ---

// Private helper to check if indices are within bounds
void Matrix::check_bounds(std::size_t r, std::size_t c) const {
    if (r >= size_ || c >= size_) {
        throw std::out_of_range("Matrix indices out of range");
    }
}

// --- Constructors ---

// Constructor: Initialize an empty NxN matrix (with zeros)
Matrix::Matrix(std::size_t N) : size_(N) {
    if (N == 0) {
        // Handle case of 0x0 matrix if needed, or throw
        // For now, just create empty data
        return;
    }
    // Resize outer vector
    data_.resize(size_);
    // Resize each inner vector and initialize with 0
    for (std::size_t i = 0; i < size_; ++i) {
        data_[i].resize(size_, 0);
    }
}

// Constructor: Initialize from a vector of vectors
Matrix::Matrix(std::vector<std::vector<int>> nums) {
    if (nums.empty()) {
        size_ = 0;
        return; // Empty matrix
    }

    size_ = nums.size();
    // Validate if it's a square matrix
    for (const auto& row : nums) {
        if (row.size() != size_) {
            throw std::invalid_argument("Input vector must represent a square matrix.");
        }
    }
    // Deep copy the data
    data_ = nums;
}

// --- Operators ---

// Operator+: Add two matrices
Matrix Matrix::operator+(const Matrix &rhs) const {
    if (size_ != rhs.size_) {
        throw std::invalid_argument("Matrices must have the same dimensions for addition.");
    }

    Matrix result(size_); // Create a result matrix of the same size
    for (std::size_t i = 0; i < size_; ++i) {
        for (std::size_t j = 0; j < size_; ++j) {
            result.data_[i][j] = this->data_[i][j] + rhs.data_[i][j];
        }
    }
    return result;
}

// Operator*: Multiply two matrices
Matrix Matrix::operator*(const Matrix &rhs) const {
    if (size_ != rhs.size_) {
        throw std::invalid_argument("Matrices must have the same dimensions for multiplication.");
    }

    Matrix result(size_); // Result matrix initialized to zeros
    for (std::size_t i = 0; i < size_; ++i) {
        for (std::size_t j = 0; j < size_; ++j) {
            int sum = 0;
            for (std::size_t k = 0; k < size_; ++k) {
                sum += this->data_[i][k] * rhs.data_[k][j];
            }
            result.data_[i][j] = sum;
        }
    }
    return result;
}

// --- Accessors and Mutators ---

// set_value: Update the element at (i, j) - Task 7 requirement (partially)
void Matrix::set_value(std::size_t i, std::size_t j, int n) {
    check_bounds(i, j); // Use helper for bounds check
    data_[i][j] = n;
}

// get_value: Retrieve the element at (i, j)
int Matrix::get_value(std::size_t i, std::size_t j) const {
    check_bounds(i, j); // Use helper for bounds check
    return data_[i][j];
}

// get_size: Return the size N of the matrix
std::size_t Matrix::get_size() const {
    return size_;
}

// --- Operations ---

// sum_diagonal_major: Sum of the main diagonal (top-left to bottom-right) - Task 4
int Matrix::sum_diagonal_major() const {
    int sum = 0;
    for (std::size_t i = 0; i < size_; ++i) {
        sum += data_[i][i];
    }
    return sum;
}

// sum_diagonal_minor: Sum of the secondary diagonal (top-right to bottom-left) - Task 4
int Matrix::sum_diagonal_minor() const {
    int sum = 0;
    for (std::size_t i = 0; i < size_; ++i) {
        sum += data_[i][size_ - 1 - i];
    }
    return sum;
}

// swap_rows: Swap two rows - Task 5
void Matrix::swap_rows(std::size_t r1, std::size_t r2) {
    if (r1 >= size_ || r2 >= size_) {
        throw std::out_of_range("Row index out of range for swap_rows");
    }
    if (r1 == r2) return; // No-op if rows are the same
    std::swap(data_[r1], data_[r2]);
}

// swap_cols: Swap two columns - Task 6
void Matrix::swap_cols(std::size_t c1, std::size_t c2) {
    if (c1 >= size_ || c2 >= size_) {
        throw std::out_of_range("Column index out of range for swap_cols");
    }
    if (c1 == c2) return; // No-op if columns are the same
    for (std::size_t i = 0; i < size_; ++i) {
        std::swap(data_[i][c1], data_[i][c2]);
    }
}

// --- Utility ---

// print_matrix: Print the matrix with formatting - Task 1 requirement (partially)
void Matrix::print_matrix() const {
    // Basic fixed-width printing. A more robust solution might calculate
    // the maximum width needed, but this is often sufficient.
    const int field_width = 5; // Adjust as needed

    if (size_ == 0) {
        std::cout << "[ Empty Matrix ]" << std::endl;
        return;
    }

    for (std::size_t i = 0; i < size_; ++i) {
        for (std::size_t j = 0; j < size_; ++j) {
            std::cout << std::setw(field_width) << data_[i][j];
        }
        std::cout << std::endl;
    }
}
