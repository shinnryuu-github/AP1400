#include "hw1.h"
#include <vector>
#include <random>
#include <iostream>
#include <iomanip>

using Matrix = std::vector<std::vector<double>>;

namespace algebra{
    Matrix zeros(size_t n, size_t m){
        Matrix res(n, std::vector<double>(m, 0.0));
        return res;
    } 

    Matrix ones(size_t n, size_t m){
        Matrix res(n, std::vector<double>(m, 1.0));
        return res;
    }

    Matrix random(size_t n, size_t m, double min, double max){
        if (min > max)
            throw std::logic_error("invalid random number");
        Matrix res(n, std::vector<double>(m));
        std::random_device rand;
        std::mt19937 gen(rand());
        std::uniform_real_distribution<double> dis(min, max);
        for (size_t i{0}; i < n; i++){
            for (size_t j{0}; j < m; j++){
                res[i][j] = dis(gen);
            }
        }
        return res;
    }

    void show(const Matrix& matrix){
        for (auto const vec: matrix){
            for (double const num : vec){
                std::cout << std::fixed << std::setprecision(3) << num << " ";
            }
            std::cout << "" << std::endl;
        }
    }

    Matrix multiply(const Matrix& matrix, double c){
        if (matrix.size() == 0) {
            return matrix;
        }
        Matrix res(matrix.size(), std::vector<double>(matrix[0].size()));
        for (size_t i{0}; i < matrix.size(); ++i){
            for (size_t j{0}; j < matrix[0].size(); ++j){
                res[i][j] = matrix[i][j] * c;
            }
        }
        return res;
    }

    Matrix multiply(const Matrix& matrix1, const Matrix& matrix2){
        if (matrix1.empty() || matrix2.empty())
            return Matrix{};
        if (matrix1[0].size() != matrix2.size())
            throw std::logic_error("invalid matrix");
        Matrix res(matrix1.size(), std::vector<double>(matrix2[0].size(), 0.0));
        for (size_t i{0}; i < res.size(); ++i){
            for (size_t j{0}; j < res[0].size(); ++j){
                res[i][j] = 0.0;
                for (size_t x{0}; x < matrix1[0].size(); ++x){
                    res[i][j] += matrix1[i][x] * matrix2[x][j];
                }
            }
        }
        return res;
    }

    Matrix sum(const Matrix& matrix, double c){
        if (matrix.empty()) 
            return Matrix{};
        Matrix res(matrix.size(), std::vector<double>(matrix[0].size()));
        for (size_t i{0}; i < res.size(); ++i){
            for (size_t j{0}; j < res[0].size(); ++j){
                res[i][j] = matrix[i][j] + c;
            }
        }
        return res;
    }

    Matrix sum(const Matrix& matrix1, const Matrix& matrix2){
        if (matrix1.empty() && matrix2.empty()) 
        return Matrix{};
        if (matrix1.empty() || matrix2.empty()) 
            throw std::logic_error("calculation error\n");
        if (matrix1.size() != matrix2.size() || matrix1[0].size() != matrix2[0].size())
            throw std::logic_error("dimessions error\n");
        Matrix res(matrix1.size(), std::vector<double>(matrix1[0].size()));
        for (size_t i{0}; i < res.size(); ++i){
            for (size_t j{0}; j < res[0].size(); ++j){
                res[i][j] += matrix1[i][j] + matrix2[i][j];
            }
        }
        return res;
    }

    Matrix transpose(const Matrix& matrix){
        if (matrix.empty())
            return Matrix{};
        Matrix res(matrix[0].size(), std::vector<double>(matrix.size()));
        for (size_t i{0}; i < res.size(); ++i){
            for (size_t j{0}; j < res[0].size(); ++j){
                res[i][j] = matrix[j][i];
            }
        }
        return res;
    }

    Matrix minor(const Matrix& matrix, size_t n, size_t m){
        Matrix res(matrix.size() - 1, std::vector<double>(matrix[0].size() - 1));
        int i{0}, j{0};
        for (size_t x{0}; x < matrix.size(); ++x){
            if (x != n){
                j = 0;
                for (size_t y{0}; y < matrix[0].size(); ++y){
                    if (y != m){
                        res[i][j++] = matrix[x][y];
                    }
                }
                i++;
            }
        }
        return res;
    }

    double power_of_minus_one(const int n){
        double res{1.0};
        for (int i{0}; i < n; ++i){
            res *= -1.0;
        }
        return res;
    }

    double determinant(const Matrix& matrix){
        if (matrix.empty())
            return 1;
        if (matrix.size() != matrix[0].size())
            throw std::logic_error("invalid input matrix");
        if (matrix.size() == 1)
            return matrix[0][0];
        double res = 0.0;
        for (size_t i{0}; i < matrix.size(); ++i){
            res += matrix[i][0] * power_of_minus_one(i) * determinant(minor(matrix, i, 0));
        }
        return res;
    }

    Matrix adjugate(const Matrix& matrix){
        Matrix res(matrix.size(), std::vector<double>(matrix[0].size()));
        for (size_t i{0}; i < res.size(); ++i){
            for (size_t j{0}; j < matrix[0].size(); ++j){
                res[i][j] = power_of_minus_one(i + j) * determinant(minor(matrix, i, j));
            }
        }
        return res;
    }

    Matrix inverse(const Matrix& matrix){
        if (matrix.empty())
            return Matrix{};
        if (matrix.size() != matrix[0].size())
            throw std::logic_error("invalid input matrix");
        double dlt = determinant(matrix);
        if (dlt == 0)
            throw std::logic_error("determinant value equals zero");
        return multiply(transpose(adjugate(matrix)), 1 / dlt);
    }

    Matrix concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis){
        if (axis == 0){
            if (matrix1[0].size() != matrix2[0].size())
                throw std::logic_error("invalid input");
            Matrix res(matrix1.size() + matrix2.size(), std::vector<double>(matrix1[0].size()));
            for (size_t i{0}; i < res.size(); ++i){
                for (size_t j{0}; j < res[0].size(); ++j){
                    if (i < matrix1.size())
                        res[i][j] = matrix1[i][j];
                    else
                        res[i][j] = matrix2[i - matrix1.size()][j];
                }
            }
            return res;
        }
        else if (axis == 1){
            if(matrix1.size() != matrix2.size())
                throw std::logic_error("invalid input");
            Matrix res(matrix1.size(), std::vector<double>(matrix1[0].size() + matrix2[0].size()));
            for (size_t i{0}; i < res.size(); ++i){
                for (size_t j{0}; j < res[0].size(); ++j){
                    if (j < matrix1[0].size())
                        res[i][j] = matrix1[i][j];
                    else
                        res[i][j] = matrix2[i][j - matrix1[0].size()];
                }
            }
            return res;
        }
        else
            throw std::logic_error("invalid axis");
        return zeros(1,1);
    }

    Matrix ero_swap(const Matrix& matrix, size_t r1, size_t r2){
        if (r1 < 0 || r2 >= matrix.size())
            throw std::logic_error("row out of range");
        Matrix res(matrix);
        std::vector<double> tmp(res[r1]);
        res[r1] = res[r2];
        res[r2] = tmp;
        return res;
    }

    Matrix ero_multiply(const Matrix& matrix, size_t r, double c){
        Matrix res(matrix);
        for (size_t i{0}; i < res[0].size(); ++i){
            res[r][i] *= c;
        }
        return res;
    }

    Matrix ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2){
        Matrix res(matrix);
        for (size_t i{0}; i < res[0].size(); ++i){
            res[r2][i] += res[r1][i] * c;
        }
        return res;
    }

    int upper_triangular_helper(Matrix& matrix, int col, int pre){
        if (pre >= matrix.size() - 1)
            return pre;
        if (matrix[pre][col] == 0){
            for (size_t i{pre}; i < matrix.size(); ++i){
                if (matrix[i][col] != 0){
                    matrix = ero_swap(matrix, pre, i);
                    break;
                }
            }
        }
        for (size_t i{pre + 1}; i < matrix.size(); ++i){
            if (matrix[i][col] != 0){
                matrix = ero_sum(matrix, pre, -matrix[i][col] / matrix[pre][col], i);
            }
        }
        if (col + 1 < matrix[0].size()){
            for (size_t i{pre + 1}; i < matrix.size(); ++i){
                if (matrix[i][col + 1] != 0){
                    pre++;
                    break;
                }
            }
        }
        return pre;
    }

    Matrix upper_triangular(const Matrix& matrix){
        if (matrix.empty())
            return Matrix{};
        if (matrix.size() != matrix[0].size())
            throw std::logic_error("invalid input matrix");
        Matrix res(matrix);
        int pre{0};
        for (size_t i{0}; i < res[0].size(); ++i){
            pre = upper_triangular_helper(res, i, pre);
        }
        return res;
    }
}