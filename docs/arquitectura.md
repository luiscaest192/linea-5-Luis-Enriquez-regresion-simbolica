```mermaid
graph TD
    A[Motor C++: Algoritmo Genético] -->|Genera| B(Archivo: datos_evolucion.json)
    B --> C{Servidor Flask: Python}
    C -->|Sirve Datos| D[Frontend: Interfaz Web]
    D -->|Visualiza| E[Gráficas de Evolución y Ecuaciones]