import re

from flask import Flask, render_template, request, redirect, session
from cs50 import SQL
# from flask_mail import Mail, Message
from flask_session import Session


app=Flask(__name__,template_folder='./templates',static_folder='./static')

# # mail server
# # https://support.google.com/accounts/answer/6010255
# app.config["MAIL_DEFAULT_SENDER"] = os.environ["MAIL_DEFAULT_SENDER"]
# app.config["MAIL_PASSWORD"] = os.environ["MAIL_PASSWORD"]
# app.config["MAIL_PORT"] = 587
# app.config["MAIL_SERVER"] = "smtp.gmail.com"
# app.config["MAIL_USE_TLS"] = True
# app.config["MAIL_USERNAME"] = os.environ["MAIL_USERNAME"]
# mail = Mail(app)

app.config["SESSION_PERMANENT"]=False
app.config["SESSION_TYPE"]= "filesystem"
Session(app)


db =SQL("sqlite:///registrants.db")

SPORTS =[
    "football",
    "basketball",
    "hockey",
    "chess"]

@app.route("/")
def index():
    if not session.get("name"):
        return redirect("/login")
    return render_template("index.html", SPORTS = SPORTS)

@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        session["name"] = request.form.get("name")
        return redirect("/")
    return render_template("login.html")


@app.route("/register", methods=["POST"])
def register():
    # validate
    name = request.form.get("name")
    sport = request.form.get("sport")
    # email = request.form.get("email")
    # if not name or not email:
    #     return render_template("failure.html", message="Missing Name")
    if not sport:
        return render_template("failure.html", message="Missing Sport")
    if not sport in SPORTS:
        return render_template("failure.html", message="Invalid Sport")

    else:
        # remember
        db.execute("INSERT INTO registrants (name, sport) VALUES(?,?)", name, sport)
        # message = Message("You are registered!", recipients=[email])
        # mail.send(message)

        #confirm
        return redirect("/registrants")

@app.route("/registrants")
def registrants():
    registrants = db.execute("SELECT * FROM registrants")
    return render_template("success.html", registrants=registrants)

@app.route("/deregister", methods=["POST"])
def deregister():
    id =request.form.get("id")
    if id:
        db.execute("DELETE FROM registrants WHERE id = ?", id)
    return redirect("/registrants")

@app.route("/logout")
def logout():
    session["name"] = None
    return redirect("/")
