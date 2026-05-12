Motor de Regresión Simbólica en Mojo (Línea 5)
Este proyecto desarrolla un motor de Regresión Simbólica basado en Programación Genética, diseñado para encontrar funciones matemáticas que ajusten conjuntos de datos complejos de forma automatizada. A diferencia de los métodos de regresión clásicos, este sistema no asume una forma funcional previa, sino que la "evoluciona" mediante metaheurísticas de optimización.

📊 Especificaciones de la Línea
    Línea de Especialización: Línea 5 - Programación Matemática y Alto Rendimiento.
    Lenguaje Principal: C++17
    Técnicas Utilizadas: Algoritmos Evolutivos, Optimización de memoria y Paralelismo de hilos.

🧠 Descripción Técnica
    El motor representa las ecuaciones como árboles de sintaxis abstracta (AST). El proceso de optimización busca minimizar una función de pérdida (fitness), generalmente el Error Cuadrático Medio (MSE):
        $$ MSE = \frac{1}{n} \sum_{i=1}^{n} (y_i - \hat{f}(x_i))^2 $$
    Donde $\hat{f}$ es la función candidata generada por el algoritmo genético. Gracias a Mojo, el proceso de evaluación de miles de candidatos contra el set de datos se acelera mediante:
        SIMD (Single Instruction, Multiple Data): Vectorización de las operaciones matemáticas en el hardware.
        Multithreading: Evaluación paralela de la población en múltiples núcleos del CPU.

🛠️ Stack Tecnológico
    Lenguaje: C++.
    Compilador: GCC o CLang.
    Gestión de Memoria: Uso de std::unique_ptr para evitar fugas de memoria.
    Asistencia de IA: Cursor y GitHub Copilot para la generación estratégica de código.
    Entorno: VS Code con extensión de C++.

📂 Estructura del Proyecto
    Siguiendo los requerimientos del curso :
    src/: Código fuente en C++.
    docs/: Contiene el roadmap.md y la arquitectura.md.
    evidencia/: Capturas de cursos completados y fragmentos de chats con IA.
    demo/: Video demostrativo del motor funcionando.

🚀 Instalación y Ejecución
    Instalar Modular CLI: Sigue las instrucciones en modular.com.
    Clonar el repositorio: git clone https://github.com/tu-usuario/linea-5-regresion-simbolica.git.
    Ejecutar: 