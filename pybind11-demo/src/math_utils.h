#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <vector>
#include <string>

namespace mylib {

struct Result {
    double value;
    std::string description;
};

class Calculator {
public:
    Calculator() = default;
    
    double add(double a, double b);
    double subtract(double a, double b);
    double multiply(double a, double b);
    double divide(double a, double b);
    
    Result compute_stats(const std::vector<double>& data);
    
    static std::string version();
};

} // namespace mylib

#endif // MATH_UTILS_H
