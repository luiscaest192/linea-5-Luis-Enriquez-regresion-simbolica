#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <memory>
#include <string>

enum class OpType { SUM, MUL, VAR_X, CONSTANT };

class Node {
public:
    OpType type;
    double value;
    std::vector<std::unique_ptr<Node>> children;

    // Constructor para constantes
    Node(double val) : type(OpType::CONSTANT), value(val) {}
    
    // Constructor para operaciones o variables
    Node(OpType t) : type(t), value(0.0) {}

    double evaluate(double x) const;
    
    // NUEVO: Para imprimir la ecuación
    double evaluate(double x) const;
    std::string toString() const; // NUEVO: Para imprimir la ecuación

};

#endif