#include "Node.hpp"
#include <random>

// Instanciamos el generador de números aleatorios (Mersenne Twister)
static std::random_device rd;
static std::mt19937 gen(rd());

std::unique_ptr<Node> generateRandomTree(int maxDepth, int currentDepth = 0) {
    std::uniform_real_distribution<double> probDist(0.0, 1.0);
    double p = probDist(gen);

    // Condición de parada: Si llegamos a la profundidad máxima, forzamos un terminal
    if (currentDepth >= maxDepth) {
        if (p < 0.5) {
            return std::make_unique<Node>(OpType::VAR_X);
        } else {
            std::uniform_real_distribution<double> constDist(-10.0, 10.0);
            return std::make_unique<Node>(constDist(gen)); // Constante entre -10 y 10
        }
    }

    // Si no estamos en la profundidad máxima, elegimos operación o terminal
    // 70% de probabilidad de ser una operación, 30% de ser terminal
    if (p < 0.7) {
        std::uniform_int_distribution<> opDist(0, 1); // 0: SUM, 1: MUL
        OpType op = static_cast<OpType>(opDist(gen));
        
        auto node = std::make_unique<Node>(op);
        // Llamada recursiva para generar los hijos
        node->children.push_back(generateRandomTree(maxDepth, currentDepth + 1));
        node->children.push_back(generateRandomTree(maxDepth, currentDepth + 1));
        return node;
    } else {
        if (probDist(gen) < 0.5) {
            return std::make_unique<Node>(OpType::VAR_X);
        } else {
            std::uniform_real_distribution<double> constDist(-10.0, 10.0);
            return std::make_unique<Node>(constDist(gen));
        }
    }
}