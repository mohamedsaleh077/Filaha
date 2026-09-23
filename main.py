from flask import Flask, request, jsonify
# from ai import get_ai_respond
# import asyncio
from embd import get_value, get_soil_data
import threading
import os

app = Flask(__name__)

if os.environ.get("WERKZEUG_RUN_MAIN") == "true" or not app.debug:
    serial_thread = threading.Thread(target=get_soil_data, daemon=True)
    serial_thread.start()


@app.route("/")
def hello_world():
    return "<h1>Hello, World!</h1>"

@app.post("/ai")
def ai_req():
    data = request.get_json()

    input = data.get("msg")

    if not data:
        return jsonify({"error": "Missing JSON payload"}), 400

    output = asyncio.run(get_ai_respond(input))

    return jsonify({
        "res" : output
    })

@app.get("/sensor")
def get_Sen():
    data = get_value()
    return jsonify({
        "tmp": data[0],
        "hmd": data[1],
        "wet": data[2]
    })


