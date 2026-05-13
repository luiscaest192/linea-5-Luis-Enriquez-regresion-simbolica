import subprocess
from flask import Flask, render_template, send_file
import os

app = Flask(__name__)

# Ruta principal: Sirve la interfaz gráfica
@app.route('/')
def index():
    return render_template('index.html')

# Ruta de datos: Envía el JSON generado por C++
@app.route('/datos')
def get_datos():
    # Nos aseguramos de enviar el archivo generado por tu motor
    json_path = os.path.join(os.path.dirname(__file__), 'datos_evolucion.json')
    if os.path.exists(json_path):
        return send_file(json_path, mimetype='application/json')
    else:
        return {"error": "Archivo no encontrado. Ejecuta tu binario de C++ primero."}, 404

if __name__ == '__main__':
    # Ejecutamos el servidor en el puerto 5000
    app.run(debug=True, host='0.0.0.0', port=5000)

# NUEVO: Ruta para subir archivos CSV desde la interfaz

@app.route('/upload', methods=['POST'])
def upload_file():
    if 'file' not in request.files:
        return "No hay archivo", 400
    
    file = request.files['file']
    filepath = os.path.join("uploads", file.filename)
    os.makedirs("uploads", exist_ok=True)
    file.save(filepath)

    # Ejecutamos el motor de C++ con el nuevo archivo
    try:
        # Llama al binario compilado pasando el path del archivo
        subprocess.run(["./regresion_simbolica", filepath], check=True)
        return jsonify({"status": "success", "message": "Procesamiento completado"})
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500