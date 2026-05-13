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