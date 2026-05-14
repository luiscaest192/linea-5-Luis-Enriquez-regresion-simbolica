#include "Node.hpp"
#include <cmath>

// Implementación de los métodos de la clase Node
// ----------------------------------------------

// Implementación del método evaluate() para calcular el valor de la expresión dada una x

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

// NUEVO: Implementación del método toString() para imprimir la ecuación

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

// NUEVO: Implementación del método clone() para poder reproducir árboles
std::unique_ptr<Node> Node::clone() const {
    // Creamos una copia exacta del nodo actual
    auto copy = std::make_unique<Node>(this->type);
    copy->value = this->value;
    
    // Clonamos recursivamente a todos los hijos
    for (const auto& child : this->children) {
        copy->children.push_back(child->clone());
    }
    return copy;
}