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
```Bash
   git clone [https://github.com/luiscaest192/linea-5-Luis-Enriquez-regresion-simbolica](https://github.com/luiscaest192/linea-5-Luis-Enriquez-regresion-simbolica)
   cd linea-5-Luis-Enriquez-regresion-simbolica
```

2. **Crear y activar el entorno virtual de Python:**
```bash
   python3 -m venv venv
   source venv/bin/activate
   ```
3. **Instalar dependenciass del servidor web:**
```Bash
   pip install Flask
   ```
## Cómo ejecutar el proyecto (Uso Local)
Todo el flujo de compilación y ejecucuón está automatizado. Con el entorno virtual activado simplemente ejecuta:
   ```Bash
   make web
   ```
Este comando:
1. Compilará el motor de C++ si hay cambios en el código fuente.
2. Levantará el servidor Flask.
3. Expondrá la interfaz gráfica en ```http://127.0.0.1:5000```

**Uso de la Interfaz:**
Al abrir la URL en el navegador, podrás cargar un archivo ```.csv``` (sin encabezados, formato ```x,y```). El motor procesará los datos y la página renderizará automáticamente la curva del Error Cuadrático Medio y la mejor ecuación encontrada.

## Exposición Pública (Túnel)
Si se requiere acceder a la interfaz desde una red externa (por ejemplo, para demostraciones en vivo), se recomienda el uso de Ngrok.

Con el proyecto corriendo (```make web``` en la Terminal 1), abre una nueva terminal y ejecuta:
```Bash
ngrok http 5000
```

Ngrok generará una URL pública segura (```https://...ngrok-free.app```) que reenviará las peticiones al motor local.

## Estructura del Repositorio
* ```src/``` e ```include/```: Código fuente del motor genético en C++.

* ```templates/```: Interfaz web (HTML/JS con Chart.js).

* ```app.py```: Servidor orquestador en Flask.

* ```Makefile```: Scripts de automatización de compilación y despliegue.

* ```docs/```: Documentación de arquitectura.

* ```evidencia/chats_ia/```: Registros de transparencia sobre el uso de asistencia de IA en el desarrollo.

**Integridad Académica**
El registro del proceso de desarrollo, justificación de decisiones y el uso asistido de Inteligencia Artificial como herramienta de Pair Programming se encuentra debidamente documentado en evidencia/chats_ia/registro_ia.md.