#include <iostream>
#include "Node.hpp"

int main() {
    std::cout << "--- Motor de Regresión Simbólica en C++ ---" << std::endl;

    // Creamos f(x) = x * 5.0
    auto root = std::make_unique<Node>(OpType::MUL);
    root->children.push_back(std::make_unique<Node>(OpType::VAR_X));
    root->children.push_back(std::make_unique<Node>(5.0));

    double x_test = 10.0;
    std::cout << "Evaluando f(x) para x = " << x_test << std::endl;
    std::cout << "Resultado: " << root->evaluate(x_test) << std::endl;

    return 0;
} 
