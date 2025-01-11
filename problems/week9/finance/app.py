import os

from cs50 import SQL
from flask import Flask, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

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


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
@login_required
def index():

    # Get users cash
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

    # Get users shares in each company
    shares = db.execute("SELECT symbol, SUM(shares) FROM transactions WHERE user_id = ? GROUP BY symbol", session["user_id"])

    # Create data dictionary
    data = []

    value = float(cash)

    for company in shares:

        company_data = {}
        company_lookup = lookup(company["symbol"])
        company_data["name"] = company_lookup["name"]
        company_data["symbol"] = company_lookup["symbol"]
        company_data["price"] = company_lookup["price"]
        company_data["shares"] = company["SUM(shares)"]
        company_data["value"] = float(company_data["shares"]) * float(company_data["price"])

        value += company_data["value"]

        data.append(company_data)

    return render_template("index.html", cash=cash, value=value, data=data)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)

        # Ensure shares was submitted
        if not request.form.get("shares"):
            return apology("must provide shares", 400)

        # Check shares is positive integer
        if not request.form.get("shares").isdigit() or float(request.form.get("shares")) == 0:
            return apology("shares must be a positive integer", 400)

        # Get stock data for symbol
        symbol = request.form.get("symbol").replace(" ", "")
        stock = lookup(symbol)

        # Check symbol is valid
        if stock == None:
            return apology("symbol is not valid", 400)

        # Get users cash
        result = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

        # Check user has enough cash to buy stock
        if float(stock["price"]) * float(request.form.get("shares")) > float(result[0]["cash"]):
            return apology("not enough cash", 400)

        # Add transaction to database
        db.execute("INSERT INTO transactions (user_id, symbol, price, shares, datetime) VALUES (?, ?, ?, ?, ?)",
                   session["user_id"], stock["symbol"], stock["price"], float(request.form.get("shares")), datetime.now().strftime("%m/%d/%Y, %H:%M:%S"))

        # Update users cash in database
        newCash = float(result[0]["cash"]) - (float(stock["price"]) * float(request.form.get("shares")))
        db.execute("UPDATE users SET cash = ? WHERE id = ?", newCash, session["user_id"])

        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Get all users transactions
    result = db.execute("SELECT * FROM transactions WHERE user_id = ?", session["user_id"])

    data = []

    for tran in result:
        tran_data = {}
        tran_data["symbol"] = tran["symbol"]
        tran_data["price"] = tran["price"]
        tran_data["shares"] = abs(tran["shares"])
        tran_data["datetime"] = tran["datetime"]

        if tran["shares"] < 0:
            tran_data["buysell"] = 'sell'
        else:
            tran_data["buysell"] = 'buy'

        data.append(tran_data)

    return render_template("history.html", data=data)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
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
    """Get stock quote."""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)

        # Get stock data for symbol
        stock = lookup(request.form.get("symbol"))

        # Check symbol is valid
        if stock == None:
            return apology("symbol is not valid", 400)

        return render_template("quoted.html", name=stock["name"], price=stock["price"], symbol=stock["symbol"])

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        if not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure confirmation was submitted
        if not request.form.get("confirmation"):
            return apology("must provide password confirmation", 400)

        # Check username is unique
        results = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        if len(results) != 0:
            return apology("username is already taken", 400)

        # Check passwords match
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords did not match", 400)

        # Add new user to database
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)",
                   request.form.get("username"), generate_password_hash(request.form.get("password")))

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Get user selected symbol
        symbol = request.form.get("symbol").replace(" ", "")

        # Ensure shares was submitted
        if not request.form.get("shares"):
            return apology("must provide shares", 400)

        # Check shares is positive integer
        if float(request.form.get("shares")) <= 0:
            return apology("shares must be positive", 400)

        # Check user has that many stocks
        owned = db.execute("SELECT SUM(shares) FROM transactions WHERE user_id = ? AND symbol = ?",
                           session["user_id"], symbol)[0]["SUM(shares)"]

        if float(owned) < float(request.form.get("shares")):
            return apology("not enough shares owned", 400)

        # Get stock info
        stock = lookup(symbol)

        # Get users cash
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

        # Add transaction for sell (sell is negative shares in the transaction table)
        db.execute("INSERT INTO transactions (user_id, symbol, price, shares, datetime) VALUES (?, ?, ?, ?, ?)",
                   session["user_id"], stock["symbol"], stock["price"], -float(request.form.get("shares")), datetime.now().strftime("%m/%d/%Y, %H:%M:%S"))

        # Update users cash in database
        newCash = float(cash) + (float(stock["price"]) * float(request.form.get("shares")))
        db.execute("UPDATE users SET cash = ? WHERE id = ?", newCash, session["user_id"])

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:

        # Get a list of companies the user has stocks of
        owned = db.execute("SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol", session["user_id"])

        return render_template("sell.html", owned=owned)
