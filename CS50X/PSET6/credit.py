
while True:
    try:
        numberString = input("Number: ")
        break
    except ValueError:
        print("enter card number")

numberList = []

for n in numberString:
    numberList += [int(n)]

Length = len(numberList)

i = Length - 2
while i >= 0:
    numberList[i] *= 2
    if numberList[i] > 9:
        numberList[i] -= 9
    i -= 2

checksum = sum(numberList) % 10

if checksum != 0:
    print("INVALID")
elif Length == 15 and numberString[0] == "3" and (numberString[1] == "4" or numberString[1] == "7"):
    print("AMEX")
elif Length == 16 and numberString[0] == "5" and numberString[1] in ["1", "2", "3", "4", "5"]:
    print("MASTERCARD")
elif (Length == 13 or Length == 16) and numberString[0] == "4":
    print("VISA")
else:
    print("INVALID")
