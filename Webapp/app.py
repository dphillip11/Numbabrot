from flask import Flask, render_template, request, session
from flask_session import Session
from helpers import mandelbrot, initialise, changeColor, zoom, randomColor, runNumbabrot
import cv2



# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)


@app.route("/", methods=['GET'])
def index():
    x = request.args.get("x")
    y = request.args.get("y")
    if not x:
        initialise()
        mandelbrot()
    else:
        zoom(int(x),int(y))
        if session['alt']==1:
            runNumbabrot()
        else:
            mandelbrot()
    return render_template("index.html")

@app.route("/PILCV")
def pilcv():
    mandelbrot()
    return render_template("index.html")

@app.route("/color")
def color():
    changeColor()
    mandelbrot()
    return render_template("index.html")

@app.route("/randomise")
def randomise():
    randomColor()   
    runNumbabrot()
    return render_template("index.html")
    
@app.route("/quality", methods=['GET', 'POST'])
def quality():
    v = request.args.get("down")
    if not v:
        session['quality'] *= 1.5
    else:
        session['quality'] /= 1.5
    if session['alt']==1:
        runNumbabrot()
    else:
        mandelbrot()
    return render_template("index.html")

@app.route("/alt")
def alt():
    runNumbabrot()    
    return render_template("index.html")
