#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include "Node.hpp"

// Estructura para nuestros datos (X, Y)
struct Point {
    double x;
    double y;
};

// --- PILAR 1: Generador Aleatorio (simplificado para el main) ---
std::unique_ptr<Node> generateRandomTree(int maxDepth, std::mt19937& gen, int currentDepth = 0) {
    std::uniform_real_distribution<double> probDist(0.0, 1.0);
    double p = probDist(gen);

    if (currentDepth >= maxDepth || p >= 0.7) {
        if (probDist(gen) < 0.5) {
            return std::make_unique<Node>(OpType::VAR_X);
        } else {
            std::uniform_real_distribution<double> constDist(-5.0, 5.0);
            return std::make_unique<Node>(constDist(gen));
        }
    } else {
        std::uniform_int_distribution<> opDist(0, 1);
        OpType op = static_cast<OpType>(opDist(gen));
        auto node = std::make_unique<Node>(op);
        node->children.push_back(generateRandomTree(maxDepth, gen, currentDepth + 1));
        node->children.push_back(generateRandomTree(maxDepth, gen, currentDepth + 1));
        return node;
    }
}

// --- PILAR 2: Función de Fitness (MSE) ---
double calculateMSE(const std::unique_ptr<Node>& tree, const std::vector<Point>& data) {
    double error_sum = 0.0;
    for (const auto& point : data) {
        double prediction = tree->evaluate(point.x);
        double diff = prediction - point.y;
        error_sum += diff * diff;
    }
    return error_sum / data.size();
}

int main() {
    std::cout << "--- Motor de Regresión Simbólica en C++ ---\n\n";

    // 1. Crear datos de entrenamiento ficticios: y = 2x
    std::vector<Point> dataset;
    for (int i = 1; i <= 5; ++i) {
        dataset.push_back({(double)i, (double)(2 * i)});
    }

    std::cout << "Datos de entrenamiento (y = 2x):\n";
    for (const auto& p : dataset) {
        std::cout << "X: " << p.x << " -> Y real: " << p.y << "\n";
    }
    std::cout << "-------------------------------------------\n\n";

    // 2. Generar una población de 3 árboles aleatorios
    std::random_device rd;
    std::mt19937 gen(rd());

    std::cout << "Evaluando Poblacion Inicial (3 individuos):\n";
    for (int i = 0; i < 3; ++i) {
        auto randomTree = generateRandomTree(2, gen);
        std::string eq = randomTree->toString();
        double mse = calculateMSE(randomTree, dataset);
        
        std::cout << "Arbol " << i + 1 << ": f(x) = " << eq << "\n";
        std::cout << "Error Cuadratico Medio (MSE): " << mse << "\n\n";
    }

    return 0;
}