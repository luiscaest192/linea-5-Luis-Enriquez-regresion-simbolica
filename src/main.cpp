#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "Node.hpp"
#include "Generator.hpp"

// Estructura para nuestros datos (X, Y)
struct Point {
    double x; // Coordenada horizontal
    double y; /// Coordenada vertical
};

// Estructura para ordenar a la poblacion
struct Individual {
    std::unique_ptr<Node> tree;
    double fitness;
};

// --- OPERADOR DE MUTACIÓN ---
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

// --- OPERADOR DE CRUCE (Crossover) ---

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

// --- FUNCIÓN DE FITNESS (MSE) ---
double calculateMSE(const std::unique_ptr<Node>& tree, const std::vector<Point>& data) {
    double error_sum = 0.0;
    for (const auto& point : data) {
        double prediction = tree->evaluate(point.x);
        double diff = prediction - point.y;
        error_sum += diff * diff;
    }
    return error_sum / data.size();
}

// --- OBTENCIÓN DE DATOS ---
// Función para cargar datos desde un archivo CSV
std::vector<Point> cargarDatos(std::string filename) {
    std::vector<Point> dataset;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string x_str, y_str;
        if (std::getline(ss, x_str, ',') && std::getline(ss, y_str, ',')) {
            dataset.push_back({std::stod(x_str), std::stod(y_str)});
        }
    }
    return dataset;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: ./regresion_simbolica <archivo.csv>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::vector<Point> dataset = cargarDatos(filename);

    std::cout << "--- Motor de Regresion Simbolica (Algoritmo Genetico) ---\n\n";

    /* 1. Datos de entrenamiento ficticios: y = 2x
    std::vector<Point> dataset;
    for (int i = 1; i <= 5; ++i) {
        dataset.push_back({(double)i, (double)(2 * i)});
    }*/

    std::random_device rd;
    std::mt19937 gen(rd());

    // 2. Hiperparametros del Algoritmo
    const int POPSIZE = 100;        // 100 ecuaciones compitiendo
    const int GENERATIONS = 50;     // 50 ciclos de evolucion
    const double MUTATION_RATE = 0.1; // 10% de probabilidad de mutacion
    const int ELITISM = 10;         // Salvamos a los 10 mejores cada generacion

    // 3. Crear la poblacion inicial
    std::vector<Individual> population;
    for (int i = 0; i < POPSIZE; ++i) {
        population.push_back({generateRandomTree(3, gen), 0.0});
    }
    // Abrimos el archivo para guardar la evolucion
    std::ofstream outFile("datos_evolucion.json");
    outFile << "[\n"; // Iniciamos un arreglo JSON

    // --- EL BUCLE GENERACIONAL ---
    for (int g = 0; g < GENERATIONS; ++g) {
        // A. Evaluar el fitness (MSE) de toda la poblacion
        for (auto& ind : population) {
            ind.fitness = calculateMSE(ind.tree, dataset);
        }

        // B. Ordenar de mejor a peor (menor MSE es mejor)
        std::sort(population.begin(), population.end(), 
            [](const Individual& a, const Individual& b) {
                return a.fitness < b.fitness;
            });

        // Imprimir al mejor de la generacion actual
        std::cout << "Generacion " << g 
                  << " | Mejor MSE: " << population[0].fitness 
                  << " | f(x) = " << population[0].tree->toString() << "\n";

        // Escribimos aquí el JSON
        outFile << "  {\n";
        outFile << "    \"generacion\": " << g << ",\n";
        outFile << "    \"mse\": " << population[0].fitness << ",\n";
        outFile << "    \"ecuacion\": \"" << population[0].tree->toString() << "\"\n";
        
        // Si el MSE es casi 0, esta será la última iteración, así que no ponemos coma
        if (g < GENERATIONS - 1 && population[0].fitness >= 0.001) {
            outFile << "  },\n"; 
        } else {
            outFile << "  }\n"; 
        }

        // Condicion de parada: Si encontramos la respuesta exacta (MSE cercano a 0)
        if (population[0].fitness < 0.001) {
            std::cout << "\n✅ Solucion encontrada en la generacion " << g << "!\n";
            break;
        }

        // C. Crear la siguiente generacion
        std::vector<Individual> new_population;

        // Elitismo: Pasar a los mejores directamente
        for (int i = 0; i < ELITISM; ++i) {
            new_population.push_back({population[i].tree->clone(), 0.0});
        }

        // D. Llenar el resto de la poblacion con Cruce y Mutacion
        while (new_population.size() < POPSIZE) {
            // Seleccion por Torneo (simplificada): Elegir padres aleatorios de la mejor mitad
            std::uniform_int_distribution<> parentDist(0, POPSIZE / 2);
            auto p1 = population[parentDist(gen)].tree->clone();
            auto p2 = population[parentDist(gen)].tree->clone();

            // Aplicar Cruce
            crossover(p1, p2, gen);

            // Aplicar Mutacion
            mutate(p1, MUTATION_RATE, 3, gen);
            mutate(p2, MUTATION_RATE, 3, gen);

            // Añadir los hijos a la nueva poblacion
            new_population.push_back({std::move(p1), 0.0});
            if (new_population.size() < POPSIZE) {
                new_population.push_back({std::move(p2), 0.0});
            }
        }

        // Reemplazar la poblacion vieja con la nueva
        population = std::move(new_population);
    }
    // Cerramos el archivo JSON, al salir del bucle
    outFile << "\n]\n";
    outFile.close();

    return 0;
}