import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
import datetime
import math

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


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]
    # gets data to insert in the main page
    transactions = db.execute(
        "SELECT symbol, SUM(shares) AS shares, price FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)
    # gets the cash in db
    cash_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    cash = cash_db[0]["cash"]

    return render_template("index.html", database=transactions, cash=cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")

    else:
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # checks for symbol
        if not symbol:
            return apology("Missing Symbol")

        stock = lookup(symbol.upper())

        if stock == None:
            return apology("symbol Does Not Exist")

        if int(shares) < 0:
            return apology("Share Not Allowed")

        # value got from the transaction
        transactionValue = int(shares) * float(stock["price"])
        user_id = session["user_id"]

        # get the cash from user
        user_cash_db = db.execute("SELECT cash FROM users WHERE id = :id", id=user_id)
        user_cash = user_cash_db[0]["cash"]

        # check if there is money enough to buy stocks
        if int(user_cash) < transactionValue:
            return apology("Not Enough Money")

        # if has money enough, does the math to discount the purchase
        updateCash = user_cash - transactionValue

        # update the users money
        db.execute("UPDATE users SET cash = ? WHERE id = ?", format(updateCash, '.2f'), user_id)

        date = datetime.datetime.now()

        # insert updated data
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, date) VALUES (?, ?, ?, ?, ?)",
                   user_id, stock["symbol"], shares, stock["price"], date)

        flash("Bought!")

        # redirects to main page
        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # gets user id by session
    user_id = session["user_id"]

    # get the transactions history
    transactions = db.execute("SELECT * FROM transactions WHERE user_id = :id", id=user_id)
    return render_template("history.html", transactions=transactions)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

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
    if request.method == "GET":
        return render_template('quote.html')

    else:
        symbol = request.form.get("symbol")

        # symbols check
        if not symbol:
            return apology("Must provide a symbol")

        stock = lookup(symbol.upper())
        if stock == None:
            return apology("Symbol must exist")

        # render with data
        return render_template("quoted.html", name=stock["name"], price=format(stock["price"], '.2f'), symbol=stock["symbol"])


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "GET":
        return render_template('register.html')

    else:
        # get input values
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # check the inputs
        if not username:
            return apology('You must provide an username')
        if not password:
            return apology('You must provide a password')
        if not confirmation:
            return apology('You must provide a password confirmation')

        # check if password matches the second input for password confirmation
        if password != confirmation:
            return apology('Your password does not match')

        # checks inside the db if the username already exists
        rows = db.execute('SELECT username FROM users WHERE username = ?;', username)
        if len(rows) == 1:
            return apology('Your username is already taken')

        # function to generate a crypto password
        hash = generate_password_hash(password)

        # new user inserted
        newUser = db.execute('INSERT INTO users (username, hash) VALUES (?, ?);', username, hash)

        session['user_id'] = newUser

        # goes to main page
        return redirect('/')


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        # gets id by session
        user_id = session["user_id"]

        # gets symbols
        symbols_user = db.execute(
            "SELECT symbol FROM transactions WHERE user_id = :id GROUP BY symbol HAVING SUM(shares) > 0", id=user_id)

        # render selling page
        return render_template("sell.html", symbols=[row["symbol"] for row in symbols_user])

    else:
        # get input values
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # check input values
        if not symbol:
            return apology("Missing Symbol")

        stock = lookup(symbol.upper())

        # check stock and shares
        if stock == None:
            return apology("symbol Does Not Exist")

        if int(shares) < 0:
            return apology("Share Not Allowed")

        # gets the math of the transaction done
        transactionValue = int(shares) * float(stock["price"])
        user_id = session["user_id"]

        # get the user cash from db
        user_cash_db = db.execute("SELECT cash FROM users WHERE id = :id", id=user_id)
        user_cash = user_cash_db[0]["cash"]

        # get the shares that user has
        ownedShares = db.execute(
            "SELECT shares FROM transactions WHERE user_id=:id AND symbol = :symbol GROUP BY symbol", id=user_id, symbol=symbol)
        shrs = ownedShares[0]["shares"]

        # if the user has shares enough, then the user can sell it
        if int(shares) > shrs:
            return apology("You do not have this amount of shares to sell")

        updateCash = user_cash + transactionValue

        # updates the cash with the sold share
        db.execute("UPDATE users SET cash = ? WHERE id = ?", round(updateCash, 2), user_id)

        date = datetime.datetime.now()

        # insert new data into db
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, date) VALUES (?, ?, ?, ?, ?)",
                   user_id, stock["symbol"], (-1)*shares, stock["price"], date)

        # SOLD!
        flash("Sold!")

        # redirects to homepage
        return redirect("/")