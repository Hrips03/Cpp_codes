#include <iostream>
#include <vector>
#include <thread>
#include <stdexcept>
#include <string>

namespace InputHandling
{
    bool isPositiveNumber(const std::string &s)
    {
        if (s.empty())
            return false;

        for (char ch : s)
            if (ch < '0' || ch > '9') 
                return false;

        return s != "0"; 
    }

    size_t getPositiveNumber(const std::string &prompt)
    {
        std::string input;
        size_t number;

        do
        {
            std::cout << prompt;
            std::cin >> input;

            if (isPositiveNumber(input))
            {
                number = std::stoul(input); 
                return number;
            }
            std::cout << "Invalid input. Please enter a positive number.\n";

        } while (true);
    }
}

namespace MatrixNamespace
{
    class Matrix
    {
    public:
        using matrix = std::vector<std::vector<int>>;

        Matrix(size_t rows, size_t cols, int init_value = 0)
        {
            mat.resize(rows, std::vector<int>(cols, init_value));
        }

        size_t rows() const { return mat.size(); }
        size_t cols() const { return mat.empty() ? 0 : mat[0].size(); }

        std::vector<int> &operator[](size_t row) { return mat[row]; }
        const std::vector<int> &operator[](size_t row) const { return mat[row]; }

        static void sumRow(const Matrix &mat1, const Matrix &mat2, Matrix &result, size_t row)
        {
            for (size_t col = 0; col < mat1.cols(); ++col)
                result[row][col] = mat1[row][col] + mat2[row][col];
        }

    private:
        matrix mat;
    };

    void addMatrices(const Matrix &mat1, const Matrix &mat2, Matrix &result)
    {
        if (mat1.rows() != mat2.rows() || mat1.cols() != mat2.cols())
            throw std::invalid_argument("Matrices must have the same dimensions");

        std::vector<std::thread> threads;

        for (size_t i = 0; i < mat1.rows(); ++i)
            threads.push_back(std::thread(&MatrixNamespace::Matrix::sumRow, std::ref(mat1), std::ref(mat2), std::ref(result), i));

        for (auto &th : threads)
            th.join();
    }

    void printMatrix(const Matrix &matrix)
    {
        std::cout << "Result matrix:\n";
        for (size_t i = 0; i < matrix.rows(); ++i)
        {
            for (size_t j = 0; j < matrix.cols(); ++j)
                std::cout << matrix[i][j] << " ";

            std::cout << '\n';
        }
    }

    Matrix inputMatrix()
    {
        std::cout << "Please input dimension of matrix.\n";
        size_t row = InputHandling::getPositiveNumber("Rows: ");
        size_t col = InputHandling::getPositiveNumber("Cols: ");

        Matrix mat(row, col);

        std::cout << "Input a matrix:\n";
        for (size_t i = 0; i < row; i++)
        {
            for (size_t j = 0; j < col; j++)
                std::cin >> mat[i][j];
        }
        return mat;
    }
}