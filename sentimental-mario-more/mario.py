from cs50 import get_int

# gets the height
height = get_int("Height: ")

# check if the height is in the acceptable range
while height < 1 or height > 8:
    # if it is not on the right range, reprompt again and again
    height = get_int("Height: ")

# main loop to print every line
for index in range(height):
  # prints the space
    for space in range(height - index - 1):
        print(" ", end="")
    # prints the first half of the pyramid
    for hash in range(index + 1):
        print("#", end="")
    # prints the space between each side of the pyramid
    print("  ", end="")

    # prints the second half of hashes
    for hash2 in range(index + 1):
        print("#", end="")
    # print a new line
    print()