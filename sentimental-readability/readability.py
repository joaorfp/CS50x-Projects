from cs50 import get_string
import re


def main():
    # get the text that will be evaluated
    string = get_string("Text: ")
    sentences = 0

    # indexes the text and find where it has end of sentences and count it up
    for index in range(len(string)):
        if string[index] == "!" or string[index] == "." or string[index] == "?":
            sentences += 1

    # gets the amount of words
    words = string.count(" ") + 1

    # gets the amount of letters by regex
    letters = len(re.findall("[a-zA-Z]", string))

    # arithmetic to get average of letters per 100 words
    L = letters / words * 100
    # arithmetic to get average of sentences per 100 words
    S = sentences / words * 100

    # Coleman-Liau Index
    coleman = round(0.0588 * L - 0.296 * S - 15.8)

    if coleman < 1:
        print("Before Grade 1")

    elif coleman >= 16:
        print("Grade 16+")

    else:
        print(f"Grade {int(coleman)}")


main()