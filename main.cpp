// /main.cpp:
#include "matrix.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept> // For catching exceptions

// Helper function to read one matrix from the file stream
bool read_matrix_data(std::ifstream& infile, std::size_t N, std::vector<std::vector<int>>& data) {
    data.resize(N, std::vector<int>(N));
    for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            if (!(infile >> data[i][j])) {
                std::cerr << "Error: Could not read element at [" << i << "][" << j << "] or end of file reached prematurely." << std::endl;
                return false;
            }
        }
    }
    return true;
}

int main() {
    std::string filename;
    std::cout << "Enter the input filename: ";
    std::cin >> filename;

    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error: Could not open file '" << filename << "'" << std::endl;
        return 1;
    }

    std::size_t N;
    // 1. Read size N
    if (!(infile >> N)) {
        std::cerr << "Error: Could not read matrix size N from file." << std::endl;
        return 1;
    }
     if (N == 0) {
        std::cerr << "Error: Matrix size N must be a positive integer." << std::endl;
        return 1;
    }

    std::cout << "Matrix size N = " << N << std::endl << std::endl;

    std::vector<std::vector<int>> data1, data2;

    // Read data for the first matrix
    if (!read_matrix_data(infile, N, data1)) {
         std::cerr << "Error reading data for Matrix 1." << std::endl;
        return 1;
    }

    // Read data for the second matrix
    if (!read_matrix_data(infile, N, data2)) {
        std::cerr << "Error reading data for Matrix 2." << std::endl;
        return 1;
    }

    infile.close(); // Close the file as we've read everything needed

    try {
        // Create Matrix objects
        Matrix matrix1(data1);
        Matrix matrix2(data2);

        // Task 1: Print the matrices
        std::cout << "Matrix 1:" << std::endl;
        matrix1.print_matrix();
        std::cout << std::endl;

        std::cout << "Matrix 2:" << std::endl;
        matrix2.print_matrix();
        std::cout << std::endl;

        // Task 2: Add two matrices and display the result
        std::cout << "Matrix Sum (Matrix 1 + Matrix 2):" << std::endl;
        Matrix sum = matrix1 + matrix2;
        sum.print_matrix();
        std::cout << std::endl;

        // Task 3: Multiply two matrices and display the result
        std::cout << "Matrix Product (Matrix 1 * Matrix 2):" << std::endl;
        Matrix product = matrix1 * matrix2;
        product.print_matrix();
        std::cout << std::endl;

        // Task 4: Get the sum of matrix diagonal elements
        std::cout << "Diagonal Sums for Matrix 1:" << std::endl;
        std::cout << "  Major Diagonal Sum: " << matrix1.sum_diagonal_major() << std::endl;
        std::cout << "  Minor Diagonal Sum: " << matrix1.sum_diagonal_minor() << std::endl;
        std::cout << std::endl;

        std::cout << "Diagonal Sums for Matrix 2:" << std::endl;
        std::cout << "  Major Diagonal Sum: " << matrix2.sum_diagonal_major() << std::endl;
        std::cout << "  Minor Diagonal Sum: " << matrix2.sum_diagonal_minor() << std::endl;
        std::cout << std::endl;

        // Task 5: Swap matrix rows (Demonstration with rows 0 and 1 if possible)
        if (N >= 2) {
            std::cout << "Swapping rows 0 and 1 of Matrix 1:" << std::endl;
            Matrix temp_m1_row_swap = matrix1; // Work on a copy
            temp_m1_row_swap.swap_rows(0, 1);
            temp_m1_row_swap.print_matrix();
            std::cout << std::endl;
        } else {
            std::cout << "Matrix size < 2, skipping row swap demonstration." << std::endl << std::endl;
        }

        // Task 6: Swap matrix columns (Demonstration with cols 0 and 1 if possible)
         if (N >= 2) {
            std::cout << "Swapping columns 0 and 1 of Matrix 2:" << std::endl;
            Matrix temp_m2_col_swap = matrix2; // Work on a copy
            temp_m2_col_swap.swap_cols(0, 1);
            temp_m2_col_swap.print_matrix();
            std::cout << std::endl;
        } else {
             std::cout << "Matrix size < 2, skipping column swap demonstration." << std::endl << std::endl;
        }

        // Task 7: Update matrix element (Demonstration with element [0][0] if possible)
         if (N >= 1) {
            std::cout << "Updating element [0][0] of Matrix 1 to 99:" << std::endl;
            Matrix temp_m1_update = matrix1; // Work on a copy
            temp_m1_update.set_value(0, 0, 99);
            temp_m1_update.print_matrix();
            std::cout << std::endl;
        } else {
             std::cout << "Matrix size < 1, skipping element update demonstration." << std::endl << std::endl;
        }


    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0; // Success
}
