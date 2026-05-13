import os
import subprocess
from flask import Flask, render_template, send_file, request, jsonify

app = Flask(__name__)

# Ruta principal: Sirve la interfaz grafica
@app.route('/')
def index():
    return render_template('index.html')

# Ruta de datos: Envia el JSON generado por C++ a la web
@app.route('/datos')
def get_datos():
    json_path = os.path.join(os.path.dirname(__file__), 'datos_evolucion.json')
    if os.path.exists(json_path):
        return send_file(json_path, mimetype='application/json')
    else:
        return jsonify({"error": "Archivo JSON no encontrado."}), 404

# Ruta de subida: Recibe el CSV de la web y ejecuta tu motor C++
@app.route('/upload', methods=['POST'])
def upload_file():
    # Validaciones de seguridad
    if 'file' not in request.files:
        return jsonify({"status": "error", "message": "No hay archivo"}), 400
    
    file = request.files['file']
    if file.filename == '':
        return jsonify({"status": "error", "message": "Ningun archivo seleccionado"}), 400

    # Crear carpeta 'uploads' si no existe y guardar el archivo
    os.makedirs("uploads", exist_ok=True)
    filepath = os.path.join("uploads", file.filename)
    file.save(filepath)

    # Ejecutar el binario de C++ con el archivo subido
    try:
        # Llama a tu programa C++ y le pasa la ruta del CSV
        subprocess.run(["./regresion_simbolica", filepath], check=True)
        return jsonify({"status": "success", "message": "Procesamiento completado"})
    except subprocess.CalledProcessError as e:
        # Esto atrapa si C++ crashea o da error
        return jsonify({"status": "error", "message": "El motor C++ falló al procesar los datos."}), 500
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5000)