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
// --- PILAR 3: Operador de Mutación ---
void mutate(std::unique_ptr<Node>& node, double mutationRate, int maxDepth, std::mt19937& gen) {
    std::uniform_real_distribution<double> probDist(0.0, 1.0);

    // Si la probabilidad acierta, podamos esta rama y hacemos crecer una nueva
    if (probDist(gen) < mutationRate) {
        node = generateRandomTree(maxDepth, gen, 0); 
        return; // Retornamos porque la nueva rama ya es aleatoria
    }

    // Si este nodo no mutó, intentamos mutar a sus hijos de forma recursiva
    for (auto& child : node->children) {
        mutate(child, mutationRate, maxDepth, gen);
    }
}

// --- PILAR 3.5: Operador de Cruce (Crossover) ---

// Función auxiliar para recolectar referencias a todos los unique_ptr del árbol
void collectNodeRefs(std::unique_ptr<Node>& node, std::vector<std::unique_ptr<Node>*>& refs) {
    refs.push_back(&node); // Guardamos la referencia al puntero actual
    for (auto& child : node->children) {
        collectNodeRefs(child, refs); // Recolección recursiva
    }
}

// Función principal de Cruce
void crossover(std::unique_ptr<Node>& parent1, std::unique_ptr<Node>& parent2, std::mt19937& gen) {
    std::vector<std::unique_ptr<Node>*> refs1;
    std::vector<std::unique_ptr<Node>*> refs2;
    
    // Recolectamos todos los nodos de ambos padres
    collectNodeRefs(parent1, refs1);
    collectNodeRefs(parent2, refs2);
    
    // Si alguno está vacío (no debería pasar), abortamos el cruce
    if (refs1.empty() || refs2.empty()) return;
    
    // Elegimos un índice al azar para cada padre
    std::uniform_int_distribution<> dist1(0, refs1.size() - 1);
    std::uniform_int_distribution<> dist2(0, refs2.size() - 1);
    
    auto* swapNode1 = refs1[dist1(gen)];
    auto* swapNode2 = refs2[dist2(gen)];
    
    // La magia de C++ moderno: intercambiamos la memoria de los subárboles directamente
    std::swap(*swapNode1, *swapNode2);
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

    std::cout << "--- Prueba de Cruce (Crossover) ---\n";
    
    // Generamos dos padres aleatorios
    auto padre1 = generateRandomTree(2, gen);
    auto padre2 = generateRandomTree(2, gen);
    
    std::cout << "Padre 1 (Original): f(x) = " << padre1->toString() << "\n";
    std::cout << "Padre 2 (Original): f(x) = " << padre2->toString() << "\n\n";

    // Clonamos para no perder la referencia original en la impresión
    auto hijo1 = padre1->clone();
    auto hijo2 = padre2->clone();

    // Aplicamos el cruce
    crossover(hijo1, hijo2, gen);

    std::cout << "Hijo 1 (Tras cruce): f(x) = " << hijo1->toString() << "\n";
    std::cout << "Hijo 2 (Tras cruce): f(x) = " << hijo2->toString() << "\n\n";

    return 0;
}