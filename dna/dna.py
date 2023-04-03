import csv
import sys


def main():

    # checking the right usage of the program
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")

    # opens the files that will be read
    dbFile = open("./" + sys.argv[1])
    dnaSequences = open("./" + sys.argv[2])

    # reads the file
    dbReader = csv.DictReader(dbFile)
    strs = dbReader.fieldnames[1:]

    dnaData = dnaSequences.read()
    dnaSequences.close()

    # get the strs and store in dnaAuth
    dnaAuth = {}
    for str in strs:
        dnaAuth[str] = get_strs(str, dnaData)

    # compase if the str matches the file in database given
    for row in dbReader:
        if compare(strs, dnaAuth, row):
            print("" + row['name'])
            dbFile.close()
            return
    # if no match, closes and print out no match
    print("No Match")
    dbFile.close()


# get the str
def get_strs(str, dna):
    sum = 0
    # get the str and store in dnaAuth as a return, it puts te amount of str sequences found in the dna
    while str*(sum + 1) in dna:
        sum += 1
    return sum

# make the match between the file of dna sequences and the database with people


def compare(strs, dnaAuth, row):
    for str in strs:
        if dnaAuth[str] != int(row[str]):
            return False
    return True


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
