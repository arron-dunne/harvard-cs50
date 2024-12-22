# Determine credit card validity using Luhn's algoirthm

import cs50
import re

# Get the user to input card number
while True:
    number = cs50.get_string("Number: ")

    # Check number is valid format
    if number.isnumeric():
        break

l = len(number)

# Apply Luhn's algorithm
sum = 0

# Multiply every other digit by 2, and add together
for i in range(l-1, 0, -2):
    product = str(int(number[i-1]) * 2)
    for digit in product:
        sum += int(digit)

# Add the other digits
for i in range(l, 0, -2):
    sum += int(number[i-1])

# Check last number is zero
if re.search('0$', str(sum)):

    # Check if amex
    if l == 15 and re.match('3[47]', number):
        print('AMEX')

    # Check if mastercard
    elif l == 16 and re.match('5[1-5]', number):
        print('MASTERCARD')

    # Check if visa
    elif (l == 13 or l == 16) and re.match('4', number):
        print('VISA')

    else:
        print('INVALID')

else:
    print('INVALID')
