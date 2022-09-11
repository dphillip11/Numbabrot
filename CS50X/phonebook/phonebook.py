import sys

n = int(sys.stdin.readline())

i = 0

phonebook = {}

while i < n:
    line = sys.stdin.readline()
    name, number = line.split()
    phonebook[name] = number
    i = i + 1

for line in sys.stdin:
    checkName = line.rstrip()
    if checkName in phonebook:
        print(f"{checkName}={phonebook[checkName]}")
    else:
        print("Not found")