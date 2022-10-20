from flask import render_template
from flask import request

from flask import Flask

import serial
import time


app = Flask(__name__)

serial_port = serial.Serial("/dev/ttyACM0", baudrate=9600)
time.sleep(3)


@app.route("/")
def index():
    return render_template("index.html")


@app.route("/send_color_code", methods=["POST", "GET"])
def result():
    if request.method == "POST":
        color_code = request.form["color"]
        serial_port.write(color_code.encode())
        return render_template("index.html")


app.run(host="localhost", port=5001)

# @app.route("/", methods=["POST"])
# def init():
#     return "Estoy funcionando"

#     return render_template("index.html")


# @app.route("/api/v1/movimientos", methods=["GET"])
# def movimientos():
#     try:
#         movimientos = get_todos_movimientos()
#     except Error:
#         return (
#             jsonify(
#                 {
#                     "status": "fail",
#                     "mensaje": "Ha habido un problema en la conexión a la base de datos",
#                 }
#             ),
#             400,
#         )

#     json_response = {"status": "success", "data": [dict(row) for row in movimientos]}
#     return jsonify(json_response)


# @app.route("/api/v1/movimiento", methods=["POST"])
# def grabar_movimiento():
#     nuevo_movimiento = request.get_json()
#     json_response = {}
#     from_moneda = nuevo_movimiento["from_moneda"]
#     to_moneda = nuevo_movimiento["to_moneda"]
#     ok = False
#     id_ = -1

#     if from_moneda == to_moneda:
#         json_response = {
#             "status": "fail",
#             "mensaje": "Las monedas deben ser diferentes.",
#         }
#         return jsonify(json_response), 400
#     try:
#         if from_moneda != "EUR":
#             saldo = get_saldo(from_moneda)
#             if saldo is None:
#                 saldo = 0.0
#             if float(nuevo_movimiento["from_cantidad"]) <= saldo:
#                 ok = insertar_movimiento(**nuevo_movimiento)
#             else:
#                 json_response = {"status": "fail", "mensaje": "Saldo insuficiente"}
#         else:  # EUR
#             ok = insertar_movimiento(**nuevo_movimiento)

#         if ok:
#             id_ = ultimo_id()
#             json_response = {
#                 "status": "success",
#                 "id": id_,
#                 "monedas": [from_moneda, to_moneda],
#             }
#             return jsonify(json_response), 201
#         else:
#             return jsonify(json_response), 200
#     # Esta es la excepción padre, cuidado! captura todos los errores
#     except BaseException as e:
#         traceback.print_exc()
#         return (
#             jsonify(
#                 {
#                     "status": "fail",
#                     "mensaje": "Ha ocurrido un error.",
#                 }
#             ),
#             400,
#         )
