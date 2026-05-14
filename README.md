# Motor Evolutivo de Regresión Simbólica

**Autor:** Luis Enriquez
**Proyecto:** Línea 5 - Programación Matemática y Alto Rendimiento

## Descripción
Este proyecto implementa un motor de regresión simbólica impulsado por algoritmos genéticos. Su objetivo es descubrir la ecuación matemática exacta que describe un conjunto de datos (puntos $x, y$) sin asumir ninguna estructura o forma funcional previa.

El sistema utiliza una **Arquitectura Híbrida**:
- **Backend de Alto Rendimiento (C++17):** Se encarga de la generación, evaluación (MSE), cruce y mutación de Árboles de Sintaxis Abstracta (AST) de forma optimizada mediante gestión de memoria con punteros inteligentes.
- **Frontend y Orquestación (Python/Flask + JS):** Un servidor ligero que interactúa con el binario de C++, enviando los datasets de entrenamiento mediante archivos `.csv` y renderizando la evolución del aprendizaje a través de una interfaz gráfica moderna.

Para más detalles sobre las decisiones de diseño y el desacoplamiento de estas capas, consulta [docs/arquitectura.md](docs/arquitectura.md).

## Requisitos del Entorno
Este proyecto está diseñado para ejecutarse en un entorno Linux (nativo o mediante WSL en Windows).
* Compilador de C++ compatible con C++17 (`g++`, `make`)
* Python 3.x
* Librerías de Python: `Flask`

## Configuración Inicial

1. **Clonar el repositorio:**
   ```bash
   git clone [https://github.com/luisca192/linea5-regresion-simbolica.git](https://github.com/luisca192/linea5-regresion-simbolica.git)
   cd linea5-regresion-simbolica