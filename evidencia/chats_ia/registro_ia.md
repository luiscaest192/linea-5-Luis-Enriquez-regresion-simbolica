# Registro de Uso de Inteligencia Artificial

**Herramienta utilizada:** Gemini (Google)
**Propósito:** Asistencia en diseño arquitectónico, resolución de problemas de gestión de memoria en C++ y estructuración del pipeline de despliegue.
**Link donde se orquestó el proyecto:** https://gemini.google.com/share/686bb3eb4997
**Link donde se le pidió una explicación sobre cada línea de código:**  https://gemini.google.com/share/4d62b00d5b92

A continuación se detallan las interacciones clave donde la IA aportó valor técnico significativo al desarrollo del Motor de Regresión Simbólica. Se adjuntan los logs de las conversaciones en esta misma carpeta.

| Usos Clave de la IA | Problema / Consulta Técnica | Aporte de la IA | Decisión del Desarrollador |
| :--- | :--- | :--- | :--- |
| Transicion del Lenguaje | Reestructuración del proyecto de Mojo a C++. | Generación de la estructura del `Makefile` y adaptación de la sintaxis del motor de inferencia matemática. | Se optó por consolidar el motor en C++17 para garantizar compatibilidad con herramientas de compilación. |
| Operadores memoria | Fugas de memoria al realizar el cruce (Crossover) y mutación de Árboles de Sintaxis Abstracta. | Sugerencia de implementar un método `clone()` de copia profunda y el uso de `std::swap` para intercambiar ramas de forma segura. | Se implementó la solución sugerida, asegurando el cumplimiento de las normativas de alto rendimiento al evitar *memory leaks* durante las iteraciones generacionales. |
| Arquitectura hibrida | Interconexión entre el binario de C++ y una interfaz gráfica en entorno WSL. | Propuesta de arquitectura desacoplada utilizando Flask (Python) como puente y JSON como formato de intercambio de datos. | Se adoptó la arquitectura propuesta para evitar penalizaciones de rendimiento en el motor matemático al intentar renderizar gráficos nativos en C++. |

---
**Declaración de Integridad Académica:** La lógica de negocio, la selección de hiperparámetros, la depuración final y las decisiones arquitectónicas del sistema fueron validadas y dirigidas íntegramente por el autor del proyecto. La IA se utilizó estrictamente como un asistente de desarrollo (Pair Programming) y consulta técnica.