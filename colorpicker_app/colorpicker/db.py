import os
from datetime import date
from datetime import datetime

import sqlite3

DATABASE_NAME = os.environ["DATABASE_NAME"]


def create_tables():
    tables = [
        """CREATE TABLE IF NOT EXISTS movimientos(
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                fecha VARCHAR(10) NOT NULL,
                hora VARCHAR(12) NOT NULL, 
                from_moneda VARCHAR(5) NOT NULL,
                from_cantidad DECIMAL NOT NULL,
				to_moneda VARCHAR(5) NOT NULL,
                to_cantidad DECIMAL NOT NULL
            )
            """
    ]
    db = get_db()
    cursor = db.cursor()
    for table in tables:
        cursor.execute(table)


def create_db():
    conn = sqlite3.connect(DATABASE_NAME)
    print(f"Base de datos {DATABASE_NAME} ha sido creada!")
    return conn


def get_db():
    # https://docs.python.org/3/library/sqlite3.html#sqlite3.connect
    conn = sqlite3.connect(f"file:{DATABASE_NAME}?mode=rw", uri=True)
    conn.row_factory = sqlite3.Row
    return conn


def ultimo_id():
    db = get_db()
    cursor = db.cursor()
    # statement = """SELECT last_insert_rowid() AS "id" """

    statement = """SELECT seq AS "id" FROM sqlite_sequence WHERE name="movimientos" """
    cursor.execute(statement)
    return cursor.fetchone()["id"]


def insertar_movimiento(from_moneda, from_cantidad, to_moneda, to_cantidad):
    db = get_db()
    cursor = db.cursor()
    fecha = date.today()
    hora = datetime.now().strftime("%H:%M:%S")

    statement = (
        "INSERT INTO movimientos(fecha, hora, from_moneda, from_cantidad,"
        "to_moneda, to_cantidad) VALUES (?, ?, ?, ?, ?, ?)"
    )
    cursor.execute(statement, [fecha, hora, from_moneda, from_cantidad, to_moneda, to_cantidad])
    db.commit()
    return True


def get_todos_movimientos():
    db = get_db()
    cursor = db.cursor()
    statement = "SELECT * FROM movimientos ORDER BY fecha DESC ,hora DESC "
    cursor.execute(statement)
    return cursor.fetchall()


def get_movimiento_by_id(id_):
    db = get_db()
    cursor = db.cursor()
    statement = "SELECT * FROM movimientos WHERE id = ?"
    cursor.execute(statement, [id_])
    return cursor.fetchall()


def get_saldo(moneda):
    """El saldo de una sola moneda"""
    db = get_db()
    cursor = db.cursor()

    # https://stackoverflow.com/questions/13122334/can-ifnull-be-used-with-select-statements-for-a-sum

    statement1 = f"""SELECT IFNULL(SUM(from_cantidad), 0.0) * ( -1 ) AS "Saldo"
        FROM   movimientos
        WHERE  from_moneda = ? """

    statement2 = f"""SELECT IFNULL(SUM(to_cantidad), 0.0) AS "Saldo"
        FROM   movimientos
        WHERE  to_moneda = ? """

    statement = f"""SELECT Sum(saldo) As saldo
        FROM   ({statement1} UNION {statement2}) AS "C"; """

    cursor.execute(statement, [moneda, moneda])
    return cursor.fetchone()["saldo"]


def total_euros_invertidos():
    db = get_db()
    cursor = db.cursor()
    statement = """SELECT IFNULL(SUM(from_cantidad), 0.0) AS "total_invertido" FROM movimientos WHERE from_moneda = "EUR" """
    cursor.execute(statement)
    return cursor.fetchone()["total_invertido"]


def total_euros_comprados():
    db = get_db()
    cursor = db.cursor()
    statement = """SELECT IFNULL(SUM(to_cantidad), 0.0) AS "total_comprado" FROM movimientos WHERE to_moneda = "EUR" """
    cursor.execute(statement)
    return cursor.fetchone()["total_comprado"]
