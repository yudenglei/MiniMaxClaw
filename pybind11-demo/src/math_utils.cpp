#include "math_utils.h"
#include <stdexcept>
#include <cmath>
#include <sstream>
#include <iomanip>

namespace mylib {

double Calculator::add(double a, double b) {
    return a + b;
}

double Calculator::subtract(double a, double b) {
    return a - b;
}

double Calculator::multiply(double a, double b) {
    return a * b;
}

double Calculator::divide(double a, double b) {
    if (b == 0.0) {
        throw std::invalid_argument("Division by zero");
    }
    return a / b;
}

Result Calculator::compute_stats(const std::vector<double>& data) {
    if (data.empty()) {
        throw std::invalid_argument("Empty data set");
    }
    
    double sum = 0.0;
    double min_val = data[0];
    double max_val = data[0];
    
    for (const auto& d : data) {
        sum += d;
        min_val = std::min(min_val, d);
        max_val = std::max(max_val, d);
    }
    
    double mean = sum / data.size();
    
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << "mean=" << mean << ", min=" << min_val << ", max=" << max_val;
    
    return Result{mean, oss.str()};
}

std::string Calculator::version() {
    return "1.0.0";
}

} // namespace mylib
