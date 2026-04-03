from __future__ import annotations

import sqlite3
from flask import Flask, Response, request

app = Flask(__name__)
DB_NAME = "sensor_data.db"


def init_db() -> None:
    conn = sqlite3.connect(DB_NAME)
    cur = conn.cursor()
    cur.execute("""
        CREATE TABLE IF NOT EXISTS measurements (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            x REAL NOT NULL,
            y REAL NOT NULL
        )
    """)
    conn.commit()
    conn.close()


def add_measurement(x: float, y: float) -> None:
    conn = sqlite3.connect(DB_NAME)
    cur = conn.cursor()
    cur.execute("INSERT INTO measurements (x, y) VALUES (?, ?)", (x, y))
    conn.commit()
    conn.close()


def get_measurements() -> list[tuple[float, float]]:
    conn = sqlite3.connect(DB_NAME)
    cur = conn.cursor()
    cur.execute("SELECT x, y FROM measurements ORDER BY id")
    rows = cur.fetchall()
    conn.close()
    return [(float(x), float(y)) for x, y in rows]


def delete_measurements() -> None:
    conn = sqlite3.connect(DB_NAME)
    cur = conn.cursor()
    cur.execute("DELETE FROM measurements")
    conn.commit()
    conn.close()


def solve_3x3(matrix: list[list[float]], vector: list[float]) -> list[float]:
    a = [row[:] for row in matrix]
    b = vector[:]
    n = 3

    for i in range(n):
        pivot = i
        for r in range(i + 1, n):
            if abs(a[r][i]) > abs(a[pivot][i]):
                pivot = r

        if abs(a[pivot][i]) < 1e-12:
            raise ValueError("Singuliere matrix")

        a[i], a[pivot] = a[pivot], a[i]
        b[i], b[pivot] = b[pivot], b[i]

        pivot_value = a[i][i]
        for j in range(i, n):
            a[i][j] /= pivot_value
        b[i] /= pivot_value

        for r in range(n):
            if r != i:
                factor = a[r][i]
                for j in range(i, n):
                    a[r][j] -= factor * a[i][j]
                b[r] -= factor * b[i]

    return b


def quadratic_regression(points: list[tuple[float, float]]) -> tuple[float, float, float]:
    n = len(points)

    sum_x = sum(x for x, _ in points)
    sum_x2 = sum(x * x for x, _ in points)
    sum_x3 = sum(x * x * x for x, _ in points)
    sum_x4 = sum(x * x * x * x for x, _ in points)

    sum_y = sum(y for _, y in points)
    sum_xy = sum(x * y for x, y in points)
    sum_x2y = sum((x * x) * y for x, y in points)

    matrix = [
        [n,      sum_x,  sum_x2],
        [sum_x,  sum_x2, sum_x3],
        [sum_x2, sum_x3, sum_x4],
    ]
    vector = [sum_y, sum_xy, sum_x2y]

    b0, b1, b2 = solve_3x3(matrix, vector)
    return b0, b1, b2


def calculate_r2(points: list[tuple[float, float]], b0: float, b1: float, b2: float) -> float:
    y_values = [y for _, y in points]
    y_avg = sum(y_values) / len(y_values)

    ss_res = 0.0
    ss_tot = 0.0

    for x, y in points:
        y_hat = b0 + b1 * x + b2 * x * x
        ss_res += (y - y_hat) ** 2
        ss_tot += (y - y_avg) ** 2

    if abs(ss_tot) < 1e-12:
        return 1.0

    return 1.0 - (ss_res / ss_tot)


@app.route("/data", methods=["POST"])
def post_data() -> Response:
    body = request.get_data(as_text=True).strip()
    parts = body.split()

    if len(parts) != 2:
        return Response("fout", status=400, mimetype="text/plain")

    try:
        x = float(parts[0])
        y = float(parts[1])
    except ValueError:
        return Response("fout", status=400, mimetype="text/plain")

    add_measurement(x, y)
    return Response("ok", status=201, mimetype="text/plain")


@app.route("/statistics", methods=["GET"])
def get_statistics() -> Response:
    points = get_measurements()

    if len(points) < 3:
        return Response("fout", status=400, mimetype="text/plain")

    try:
        b0, b1, b2 = quadratic_regression(points)
        r2 = calculate_r2(points, b0, b1, b2)
    except ValueError:
        return Response("fout", status=400, mimetype="text/plain")

    result = f"{b0:.1f} {b1:.1f} {b2:.1f} {r2:.1f}"
    return Response(result, status=200, mimetype="text/plain")


@app.route("/statistics", methods=["DELETE"])
def clear_statistics() -> Response:
    delete_measurements()
    return Response("ok", status=201, mimetype="text/plain")


if __name__ == "__main__":
    init_db()
    app.run(host="0.0.0.0", port=80, debug=False)