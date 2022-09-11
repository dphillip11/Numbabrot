import csv
import sys


def main():

    # Check for command-line usage

    if len(sys.argv) != 3:
        print("dna.py database.csv sequences.csv")
        return

    # Read database file into a variable
    with open(sys.argv[1], "r") as dbfile:
        # csv.reader() seems to return a pointer, the [] and deref * form a list of dictionaries from the csv file
        database = [*csv.DictReader(dbfile)]

    # second instance to start at beginning
    with open(sys.argv[1], "r") as dbfile:
        reader = csv.reader(dbfile)
        # next gives first lines/  headers
        subsequences = next(reader)

    # Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as seqfile:
        reader = csv.reader(seqfile)
        for row in reader:
            sequence = row[0]

    # Find longest match of each STR in DNA sequence
    for dict in database:
        match = 1
        for subsequence in subsequences:
            try:
                if(longest_match(sequence, subsequence)) != int(dict[subsequence]):
                    match = 0
                    break
            except:
                continue
        if match == 1:
            print(dict["name"])
            break
    if match == 0:
        print("No match")


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
