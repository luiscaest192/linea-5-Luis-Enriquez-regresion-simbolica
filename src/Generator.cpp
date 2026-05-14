#include "Generator.hpp"
#include "Node.hpp"

// Aquí va la implementación completa que antes tenías en el main.
// Nota: Ya no ponemos "= 0" en currentDepth porque ya se definió en el .hpp
std::unique_ptr<Node> generateRandomTree(int maxDepth, std::mt19937& gen, int currentDepth) {
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