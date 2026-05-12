#include "Node.hpp"
#include <cmath>

double Node::evaluate(double x) const {
    switch (this->type) {
        case OpType::CONSTANT: return value;
        case OpType::VAR_X:    return x;
        case OpType::SUM:      
            return children[0]->evaluate(x) + children[1]->evaluate(x);
        case OpType::MUL:      
            return children[0]->evaluate(x) * children[1]->evaluate(x);
        default: return 0.0;
    }
}

#include <string>

// NUEVO: Implementación de toString() para imprimir la ecuación

std::string Node::toString() const {
    switch (this->type) {
        case OpType::CONSTANT: 
            return std::to_string(value).substr(0, 4); // Acortamos los decimales
        case OpType::VAR_X:    
            return "x";
        case OpType::SUM:      
            return "(" + children[0]->toString() + " + " + children[1]->toString() + ")";
        case OpType::MUL:      
            return "(" + children[0]->toString() + " * " + children[1]->toString() + ")";
        default: 
            return "";
    }
}