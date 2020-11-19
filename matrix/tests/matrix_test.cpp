#include <gtest/gtest.h>

#include <vector>
#include "matrix.h"

template <typename T>
std::vector<T> matrixToVector(alg::Matrix<T> &matrix)
{
    std::vector<T> v(matrix.nrows() * matrix.ncols());
    auto data = matrix.data(); 
    for(size_t i = 0; i < matrix.nrows(); i++)
        for(size_t j = 0; j < matrix.ncols(); j++)
            v[i * matrix.ncols() + j] = data[i][j];
    return v;
}

const int INIT_VAL = 10;
const int NROWS = 3;
const int NCOLS = 4;

TEST(Matrix, initialization)
{
    {
    alg::Matrix<int> matrix(NROWS, NCOLS, INIT_VAL);
    std::vector<int> expected(NROWS * NCOLS, INIT_VAL);
    auto vec = matrixToVector(matrix);
    
    EXPECT_TRUE(matrix.nrows() == NROWS);
    EXPECT_TRUE(matrix.ncols() == NCOLS);
    EXPECT_TRUE(vec == expected);
    }
    { 
    alg::Matrix<int> sq(NROWS);
    std::vector<int> expected(NROWS * NROWS);
    auto vec = matrixToVector(sq);
    
    EXPECT_TRUE(sq.nrows() == NROWS);
    EXPECT_TRUE(sq.ncols() == NROWS);
    EXPECT_TRUE(vec == expected);

    }
    
    {
    alg::Matrix<int> null(NROWS, NCOLS);
    std::vector<int> expected(NROWS * NCOLS);
    auto vec = matrixToVector(null);

    EXPECT_TRUE(null.nrows() == NROWS);
    EXPECT_TRUE(null.ncols() == NCOLS);
    EXPECT_TRUE(vec == expected);
    }

    {
    alg::Matrix<int> matrix1(NROWS, NCOLS, INIT_VAL);
    alg::Matrix<int> matrix2(matrix1);
    
    EXPECT_TRUE(matrix2.nrows() == NROWS);
    EXPECT_TRUE(matrix2.ncols() == NCOLS);
    alg::Matrix<int> matrix3(NROWS, NCOLS);
    matrix3 = matrix2;

    auto vec1 = matrixToVector(matrix1);
    auto vec2 = matrixToVector(matrix2);
    auto vec3 = matrixToVector(matrix3);

    EXPECT_TRUE(vec1 == vec2);
    EXPECT_TRUE(vec2 == vec3);
    }

    {
    alg::Matrix<int> matrix = alg::Matrix<int>::identity(NROWS);
    std::vector<int> expected = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    auto vec = matrixToVector(matrix);

    EXPECT_TRUE(vec == expected);
    }

    {
    std::vector<int> expected(NROWS * NCOLS, INIT_VAL);
    alg::Matrix<int> matrix(NROWS, NCOLS, expected.begin(), expected.end());
    auto vec = matrixToVector(matrix);
    
    EXPECT_TRUE(matrix.nrows() == NROWS);
    EXPECT_TRUE(matrix.ncols() == NCOLS);
    EXPECT_TRUE(vec == expected);
   
    }
}

//TODO
TEST(Matrix, operators)
{
    std::vector<int> init = { 1, 2, 3, 4, 5, 6 };
    alg::Matrix<int> matrix(2, 3, init.begin(), init.end());

    std::vector<int> vec;
    for(size_t i = 0; i < matrix.nrows(); i++)
        for(size_t j = 0; j < matrix.ncols(); j++)
            vec.push_back(matrix[i][j]);

    EXPECT_TRUE(vec == init);
}

TEST(Matrix, swap)
{
    std::vector<int> init = { 1, 2, 3, 4, 5, 6 };
    std::vector<int> expected = { 4, 5, 6, 1, 2, 3 };
    alg::Matrix<int> matrix(2, 3, init.begin(), init.end());
    matrix.swapRows(0, 1);
    auto vec = matrixToVector(matrix);
    
    EXPECT_TRUE(vec == expected);

}

TEST(Matrix, equal)
{
    std::vector<int> init = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    alg::Matrix<int> matrix1(3, 3, init.begin(), init.end());
    alg::Matrix<int> matrix2(matrix1);

    EXPECT_TRUE(matrix1.equal(matrix2));
    EXPECT_TRUE(matrix1 == matrix2);
}

struct d_equal_to
{
    const double EPS = 1e-6;
    bool operator() (double x, double y) const
    {   
        return (x - y) < EPS;
    }
};

TEST(Matrix, determinant)
{
    {
    std::vector<int> init = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    alg::Matrix<int> matrix(3, 3, init.begin(), init.end());

    EXPECT_EQ(determinant(matrix), 0);
    }

    {
    std::vector<double> v = {1, 2, 3, 9, 5, 6, 7, 8, 9};
    alg::Matrix<double> m(3, 3, v.begin(), v.end());

    EXPECT_DOUBLE_EQ(determinant(m), 30);
    }

    {
    auto ident = alg::Matrix<int>::identity(5); 
    EXPECT_DOUBLE_EQ(determinant(ident), 1);

    ident.swapRows(0, 1);
    EXPECT_DOUBLE_EQ(determinant(ident), 1);

    }
    std::vector<double> v2 = {0, 2, 3, 9, 5, 6, 7, 8, 9};
    alg::Matrix<double> m1(3, 3, v2.begin(), v2.end());
    
    EXPECT_DOUBLE_EQ(determinant(m1), 33);
    m1.swapRows(0, 2);
    auto d = alg::determinant<double, d_equal_to>(m1);
    EXPECT_DOUBLE_EQ(d, 33);
}

