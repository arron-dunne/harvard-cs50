# Print mario pyramids with a height given by user

import cs50

# Get height between 1 and 8
while True:

    n = cs50.get_int("Height: ")

    if n > 0 and n <= 8:
        break

# Print each row with the correct number of hashes
for i in range(n):
    row = " " * (n - i - 1)
    row += "#" * (i + 1)
    row += "  "
    row += "#" * (i + 1)

    print(row)

    row = ""
