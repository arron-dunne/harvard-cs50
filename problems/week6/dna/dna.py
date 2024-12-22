# Identify a person based on their dna

import csv
import sys

def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit('Usage: python dna.py DATABASE SEQUENCE')

    # Read database file into a variable
    db = []
    str_count = {}

    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)

        # Get STRs from header
        for i in range(1, len(reader.fieldnames)):
            str_count[reader.fieldnames[i]] = 0

        # Add dict to a the database in memory
        for row in reader:
            db.append(row)

    # Read DNA sequence file into a variable
    with open(sys.argv[2]) as file:
        dna = file.read()

    # Find longest match of each STR in DNA sequence
    for str in str_count:
        str_count[str] = longest_match(dna, str)

    # Check database for matching profiles
    for person in db:
        match = False

        # Check each STR matches
        for str in str_count:
            if int(person[str]) != str_count[str]:
                match = False
                break
            else:
                match = True

        # Print matching person
        if match:
            print(person['name'])
            return

    print('No match')

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
