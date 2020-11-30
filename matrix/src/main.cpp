
#include "matrix.h"

#include <vector>
#include <iostream>

alg::Matrix<double> inputMatrix(std::istream &in, std::ostream &out)
{
    size_t n = 0;
    in >> n;
    
    std::vector<double> input;
    input.reserve(n * n);
    for(size_t i = 0; i < n * n; ++i)
    {
        double elem = 0;
        in >> elem;
        input.push_back(elem);
    }
    alg::Matrix<double> matrix(n, n, input.begin(), input.end());
      
    return matrix;
}

int main()
{
    auto matrix = inputMatrix(std::cin, std::cout);   
    std::cout << determinant(matrix) << std::endl;
    return 0;
}
