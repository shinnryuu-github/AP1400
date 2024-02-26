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
}