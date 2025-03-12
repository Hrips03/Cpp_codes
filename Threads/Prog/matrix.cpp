#include "matrix.hpp"

using matrix = MatrixNamespace::Matrix;

int main()
{
    matrix mat1 = MatrixNamespace::inputMatrix();
    matrix mat2 = MatrixNamespace::inputMatrix();

    matrix matResult(mat1.rows(), mat1.cols());
    try
    {
        MatrixNamespace::addMatrices(mat1, mat2, matResult);
        MatrixNamespace::printMatrix(matResult);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << '\n';
    }

    return 0;
}
