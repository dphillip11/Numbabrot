Text = input("Text: ")

length = len(Text)

sentences = 0
letters = 0
words = 1

# count features that indicate words, sentences and letters
for character in Text:
    if character.isalpha():
        letters += 1
    if character == " ":
        words += 1
    if character in ["!", ".", "?"]:
        sentences += 1

# calculate average letters and sentences per 100 words
L = letters * 100 / words
S = sentences * 100 / words

# calculate CLI
CLI = round(0.0588 * L - 0.296 * S - 15.8)

# print conditions
if CLI < 1:
    print("Before Grade 1")
elif CLI >= 16:
    print("Grade 16+")
else:
    print(f"Grade {CLI}")
