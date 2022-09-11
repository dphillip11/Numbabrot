while True:
    try:
        n = int(input("Height:"))
        if 0 < n < 9:
            break
        else:
            print("height should be from 1 to 8")
    except ValueError:
        print("give an integer value for the height")


# for i in range(1, n + 1):
#     print(" " * (n - i), end="")
#     print("#" * i, end="")
#     print(" ", end="")
#     print("#" * i)

for i in range(1, n + 1):
    print(" " * (n - i) + "#" * i + "  " + "#" * i)