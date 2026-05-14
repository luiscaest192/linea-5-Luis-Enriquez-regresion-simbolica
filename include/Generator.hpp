#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <memory>
#include <random>
#include "Node.hpp" // Necesitamos saber qué es un Node

// Declaración de la función (sin el código interno)
// Nota: Solo ponemos el valor por defecto (= 0) aquí en el .hpp
std::unique_ptr<Node> generateRandomTree(int maxDepth, std::mt19937& gen, int currentDepth = 0);

#endif