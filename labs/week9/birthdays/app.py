from cs50 import SQL
from flask import Flask, redirect, render_template, request

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# The root URL for the application
# When a GET request is made, show a table with all the birthdays stored in the database, and also
# a form where new birthdays can be added
# When a POST request is made, add the new birthday data into the database and update the page
@app.route("/", methods=["GET", "POST"])
def index():

    if request.method == "POST":

        # Get the data from form
        name = request.form.get("name")
        day = request.form.get("day")
        month = request.form.get("month")

        # Insert data in database
        db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", name, month, day)

        return redirect("/")

    else:

        # Get data from database
        birthdays = db.execute("SELECT * FROM birthdays")

        # Render page with birthdays
        return render_template("index.html", birthdays=birthdays)
