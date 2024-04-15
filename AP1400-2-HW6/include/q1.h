#ifndef Q1_H
#define Q1_H

#include <functional>
namespace q1 {

double gradient_descent(double init, double step, std::function<double(double)> f) {
    double x{init};
    double df{(f(x + 0.00001) - f(x)) / 0.00001};
    while (abs(df) > 0.00001) {
        x -= step * df;
        df = (f(x + 0.00001) - f(x)) / 0.00001;
    }
    return x;
}

template <class T, class F>
T gradient_descent(double init, double step){
    return gradient_descent(init, step, F());
}

}  // namespace q1

#endif //Q1_H