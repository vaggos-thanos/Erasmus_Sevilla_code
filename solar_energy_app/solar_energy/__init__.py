from flask import Flask


app = Flask(__name__, instance_relative_config=True)
# app.config["JSON_SORT_KEYS"] = False
# app.config.from_object("config")
