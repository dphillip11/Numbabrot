import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd



# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

def cashC():
    cashC = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    cashC = cashC[0]["cash"]
    cashC = usd(cashC)
    return cashC


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    # Show portfolio of stocks
    db.execute("DELETE from holdings WHERE qty = '0'")
    holdings = db.execute("SELECT * FROM holdings WHERE userid = ?", session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    cash = cash[0]["cash"]
    prices = {}
    totals = {}
    names = {}
    gtotal = 0
    for entry in holdings:
        quote = lookup(entry["symbol"])
        totals[quote["symbol"]] = usd(entry["qty"] * quote["price"])
        gtotal += entry["qty"] * quote["price"]
        prices[quote["symbol"]] = usd(quote["price"])
        names[quote["symbol"]] = quote["name"]
    gtotal = usd(gtotal + cash)
    cash = usd(cash)
    session["cashC"]=cashC()
    return render_template(
        "index.html",
        holdings=holdings,
        prices=prices,
        totals=totals,
        names=names,
        cash=cash,
        gtotal=gtotal,
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        quote = lookup(symbol)
        # convert number to integer
        try:
            number = int(request.form.get("shares"))
        except:
            message = "invalid number"
            flash(message)
            return render_template("buy.html"), 400
        if number < 1:
            message = "invalid number"
            flash(message)
            return render_template("buy.html"), 400

        try:
            price = float(quote["price"])
        except:
            message = "invalid symbol"
            flash(message)
            return render_template("buy.html", quote=quote), 400

        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = float(cash[0]["cash"])
        if (number * price) > cash:
            message = "Insufficient funds, current balance: " + usd(cash)
            flash(message)
            return redirect(request.referrer), 400

        # deduct price from cash
        cash = float(cash - (number * price))
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, session["user_id"])

        # update purchase history
        db.execute(
            "INSERT INTO orders (userid, symbol, price, qty) VALUES(?,?,?,?)",
            session["user_id"],
            symbol,
            price,
            number,
        )

        # update holdings
        currentQty = db.execute(
            "SELECT qty FROM holdings WHERE userid = ? and symbol =?",
            session["user_id"],
            symbol,
        )
        try:
            currentQty = currentQty[0]["qty"]
        except:
            currentQty = 0
        currentQty += number
        # check for entries in database
        count = db.execute(
            "SELECT COUNT(*) FROM holdings WHERE userid = ? and symbol =?",
            session["user_id"],
            symbol,
        )
        count = count[0]["COUNT(*)"]
        if count > 0:
            db.execute(
                "UPDATE holdings SET qty = ? WHERE userid = ? and symbol =?",
                currentQty,
                session["user_id"],
                symbol,
            )
        else:
            db.execute(
                "INSERT INTO holdings (userid, symbol, qty) VALUES(?,?,?)",
                session["user_id"],
                symbol,
                number,
            )

        # inform customer
        message = "Bought " + str(number) + " " + symbol + " at " + usd(price)
        flash(message)
        session["cashC"]=cashC()
        return redirect(request.referrer)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    orders = db.execute(
        "SELECT symbol, qty, price, datetime FROM orders WHERE userid = ?",
        session["user_id"],
    )
    print(orders)
    return render_template("history.html", orders=orders)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        session["username"] = request.form.get("username")

        # Redirect user to home page
        session["cashC"]=cashC()
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    # if user has requested a quote with postdata
    if request.method == "POST":
        symbol = request.form.get("symbol")
        quote = lookup(symbol)
        if not quote:
            message = "invalid symbol"
            return render_template("quote.html", message=message), 400
        message = quote["symbol"] + ": " + quote["name"] + " " + usd(quote["price"])
        return render_template("quote.html", message=message)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/search")
@login_required
def search():
        symbol = request.args.get("q")
        n = request.args.get("n")
        if not n:
            n=1
        n=int(n)
        quote = lookup(symbol)
        if not quote:
            return render_template("search.html", quote="0", n="0")

        total = usd(n * quote['price'])
        price = usd(quote['price'])

        print(quote)
        return render_template("search.html", quote=quote , total=total, price=price)


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Ensure username was submitted
        if not username:
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not password:
            return apology("must provide password", 400)

        # Check password matches confirmation
        elif password != confirmation:
            return apology("passwords must match", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        # Ensure username doesn't exist
        if len(rows) > 0:
            return apology("username already in use", 400)

        # add user to database
        db.execute(
            "INSERT INTO users (username, hash) VALUES(?,?)",
            username,
            generate_password_hash(password),
        )

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    symbols = []
    holdings = db.execute(
        "SELECT DISTINCT symbol FROM holdings WHERE userid = ?", session["user_id"]
    )
    for element in holdings:
        symbols.append(element["symbol"])

    if request.method == "GET":
        return render_template("sell.html", symbols=symbols)
    else:
        symbol = request.form.get("symbol")
        number = int(request.form.get("shares"))
        qty = db.execute(
            "SELECT SUM(qty) FROM holdings WHERE userid = ? and symbol = ?",
            session["user_id"],
            symbol,
        )
        qty = qty[0]["SUM(qty)"]

        if symbol not in symbols:
            return apology("symbol error")
        if number > int(qty):
            message = "Not available to sell"
            flash(message)
            return redirect(request.referrer), 400

        quote = lookup(symbol)
        price = quote["price"]

        # update holdings
        currentQty = db.execute(
            "SELECT qty FROM holdings WHERE userid = ? and symbol =?",
            session["user_id"],
            symbol,
        )
        currentQty = currentQty[0]["qty"] - number
        db.execute(
            "UPDATE holdings SET qty = ? WHERE userid = ? and symbol =?",
            currentQty,
            session["user_id"],
            symbol,
        )
        db.execute("DELETE from holdings WHERE qty = '0'")

        # update purchase history
        db.execute(
            "INSERT INTO orders (userid, symbol, price, qty) VALUES(?,?,?,?)",
            session["user_id"],
            symbol,
            price,
            (number * -1),
        )

        # add sale to cash

        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = cash[0]["cash"]
        cash = cash + (number * price)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, session["user_id"])
        message = "Sold " + str(number) + " " + symbol + " at " + usd(price)
        flash(message)
        session["cashC"]=cashC()
        return redirect(request.referrer)
